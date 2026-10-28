#include "prx/libSceAgcDriver/Execution/include/FrameLimit.hpp"
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

using AgcDriver::FramePacer;
using Nanos = FramePacer::Nanos;

void require(bool condition, const std::string& reason) {
    if (!condition) throw std::runtime_error(reason);
}

Nanos exactNanos(std::uint64_t frames, std::uint64_t milliFps) {
    return static_cast<Nanos>(static_cast<unsigned __int128>(frames) * 1'000'000'000'000ull / milliFps);
}

void deadlineArithmeticTests() {
    for (const std::uint64_t milliFps : {30000ull, 59940ull, 60000ull, 119880ull, 144000ull, 100000000ull, 500ull, 7ull * 1000ull + 333ull}) {
        FramePacer pacer(milliFps);
        Nanos now = 0;
        require(pacer.Admit(now) == 0, "the first frame of a run is delayed at " + std::to_string(milliFps));
        for (std::uint64_t frame = 1; frame <= 1'000'000; ++frame) {
            now += pacer.Admit(now);
            require(now == exactNanos(frame, milliFps), "frame " + std::to_string(frame) + " at limit " + std::to_string(milliFps) + " is presented at " + std::to_string(now) + " instead of " + std::to_string(exactNanos(frame, milliFps)));
        }
    }
}

void overshootDoesNotAccumulateTests() {
    constexpr std::uint64_t milliFps = 59940;
    FramePacer pacer(milliFps);
    Nanos now = 0;
    std::uint64_t seed = 12345;
    pacer.Admit(now);
    for (std::uint64_t frame = 1; frame <= 100'000; ++frame) {
        seed = seed * 6364136223846793005ull + 1442695040888963407ull;
        const Nanos overshoot = static_cast<Nanos>((seed >> 33) % 2'000'000);
        now += pacer.Admit(now) + overshoot;
        const Nanos late = now - exactNanos(frame, milliFps);
        require(late >= 0 && late < 2'000'000, "a sleep that overshoots by under 2 ms leaves frame " + std::to_string(frame) + " " + std::to_string(late) + " ns after its deadline");
    }
}

void stallDoesNotBurstTests() {
    constexpr std::uint64_t milliFps = 30000;
    const Nanos period = exactNanos(1, milliFps);
    for (const Nanos stall : {Nanos{50'000'000}, Nanos{1'000'000'000}, Nanos{3'600'000'000'000}}) {
        FramePacer pacer(milliFps);
        Nanos now = 0;
        pacer.Admit(now);
        for (int frame = 1; frame <= 10; ++frame) now += pacer.Admit(now);
        now += stall;
        std::vector<Nanos> presents;
        for (int frame = 0; frame < 200; ++frame) {
            now += pacer.Admit(now);
            presents.push_back(now);
            now += 1'000'000;
        }
        for (std::size_t index = 0; index + 2 < presents.size(); ++index) {
            require(presents[index + 2] - presents[index] >= period - 1, "after a stall of " + std::to_string(stall) + " ns three presents fall within " + std::to_string(presents[index + 2] - presents[index]) + " ns at frame " + std::to_string(index));
        }
        require(presents[presents.size() - 1] - presents[2] >= static_cast<Nanos>(presents.size() - 3) * period - 2, "frames after a stall of " + std::to_string(stall) + " ns are not paced at the limit");
    }
}

void lateFrameIsMadeUpTests() {
    constexpr std::uint64_t milliFps = 30000;
    const Nanos period = exactNanos(1, milliFps);
    FramePacer pacer(milliFps);
    Nanos now = 0;
    pacer.Admit(now);
    for (std::uint64_t frame = 1; frame <= 4; ++frame) now += pacer.Admit(now);
    require(now == exactNanos(4, milliFps), "the frames before the late one are off the schedule");
    now += period + period / 2;
    require(pacer.Admit(now) == 0, "a late frame is delayed");
    const Nanos lateAt = now;
    const Nanos wait = pacer.Admit(now);
    require(wait == exactNanos(6, milliFps) - lateAt, "the frame after one late by half a period waits " + std::to_string(wait) + " ns instead of making up the delay");
    now += wait;
    require(now == exactNanos(6, milliFps), "the schedule did not resume after a late frame");
}

void slowGameIsNeverDelayedTests() {
    for (const std::uint64_t milliFps : {30000ull, 59940ull, 144000ull}) {
        FramePacer pacer(milliFps);
        const Nanos period = exactNanos(1, milliFps);
        Nanos now = 5'000'000'000;
        for (int frame = 0; frame < 10'000; ++frame) {
            require(pacer.Admit(now) == 0, "a game slower than the limit " + std::to_string(milliFps) + " is delayed at frame " + std::to_string(frame));
            now += period + period / 1000 + 1;
        }
    }
}

void resetTests() {
    FramePacer pacer(30000);
    pacer.Admit(0);
    require(pacer.Admit(0) == exactNanos(1, 30000), "the second frame at once is not delayed by a period");
    pacer.Reset();
    require(pacer.Admit(0) == 0, "a frame after a reset is delayed");
    require(pacer.Admit(0) == exactNanos(1, 30000), "the schedule does not restart after a reset");
}

void zeroLimitTests() {
    bool refused = false;
    try {
        FramePacer pacer(0);
    } catch (const std::invalid_argument&) {
        refused = true;
    }
    require(refused, "a pacer for 0 frames per second was constructed");
}

}

int main() {
    try {
        deadlineArithmeticTests();
        overshootDoesNotAccumulateTests();
        stallDoesNotBurstTests();
        lateFrameIsMadeUpTests();
        slowGameIsNeverDelayedTests();
        zeroLimitTests();
        resetTests();
        std::puts("frame limit tests passed");
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "%s\n", error.what());
        return 1;
    }
}
