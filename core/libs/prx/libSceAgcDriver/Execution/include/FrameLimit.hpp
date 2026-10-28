#ifndef CORE_LIBS_PRX_LIBSCEAGCDRIVER_EXECUTION_INCLUDE_FRAMELIMIT_HPP
#define CORE_LIBS_PRX_LIBSCEAGCDRIVER_EXECUTION_INCLUDE_FRAMELIMIT_HPP

#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace AgcDriver {

class FramePacer {
public:
    using Nanos = std::int64_t;

    explicit FramePacer(std::uint64_t milliFramesPerSecond) : divisor(milliFramesPerSecond) {
        if (divisor == 0) throw std::invalid_argument("FramePacer: the frame rate must be positive");
        whole = static_cast<Nanos>(MilliNanosPerSecond / divisor);
        part = static_cast<Nanos>(MilliNanosPerSecond % divisor);
    }

    Nanos Admit(Nanos now) {
        if (!started) {
            started = true;
            next = now;
            carry = 0;
        }
        const Nanos wait = std::max<Nanos>(next - now, 0);
        next = std::max(next + step(), now + wait);
        return wait;
    }

    void Reset() { started = false; }

    template <class TClock, class TSleep>
    bool Pace(TClock&& clock, TSleep&& sleep, Nanos longestSleep) {
        const Nanos now = clock();
        const Nanos deadline = now + Admit(now);
        const Nanos slice = std::max<Nanos>(longestSleep, 1);
        for (Nanos remaining = deadline - now; remaining > 0; remaining = deadline - clock()) {
            if (!sleep(std::min(remaining, slice))) return false;
        }
        return true;
    }

private:
    static constexpr std::uint64_t MilliNanosPerSecond = 1'000'000'000'000ull;

    Nanos step() {
        Nanos length = whole;
        carry += part;
        if (static_cast<std::uint64_t>(carry) >= divisor) {
            carry -= static_cast<Nanos>(divisor);
            ++length;
        }
        return length;
    }

    std::uint64_t divisor;
    Nanos whole = 0;
    Nanos part = 0;
    Nanos carry = 0;
    Nanos next = 0;
    bool started = false;
};

}

#endif
