#pragma once
#include <functional>

class Timer {
public:
    float mTicksPerSecond;
    int mTicks;
    float mAlpha;
    float mTimeScale;
    float mPassedTime;
    float mFrameStepAlignmentRemainder;
    float mLastTimeSeconds;
    float mLastTimestep;
    int64_t mLastMs;
    int64_t mLastMsSysTime;
    float mAdjustTime;
    int mSteppingTick;
    std::function<int64_t __cdecl(void)> mGetTimeMSCallback;

    void RestartCurrentTick() {
        mPassedTime = 0.0f;
        mFrameStepAlignmentRemainder = 0.0f;
        mLastTimestep = 0.0f;

        // Resync to current system time
        mLastMs = mGetTimeMSCallback();
        mLastMsSysTime = mLastMs;
        mLastTimeSeconds = static_cast<float>(mLastMs) / 1000.0f;

        // Alpha can be reset so interpolation starts fresh
        mAlpha = 0.0f;
    }

    float ComputeAlpha() const
    {
        int64_t currentMs = mGetTimeMSCallback();
        float deltaSeconds = static_cast<float>(currentMs - mLastMs) / 1000.0f;
        deltaSeconds *= mTimeScale;
        float tickDelta = deltaSeconds * mTicksPerSecond;
        return tickDelta;
    }
};