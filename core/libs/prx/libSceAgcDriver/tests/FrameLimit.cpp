#include "prx/libSceAgcDriver/Execution/include/FrameLimit.hpp"
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>

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
        zeroLimitTests();
        std::puts("frame limit tests passed");
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "%s\n", error.what());
        return 1;
    }
}
