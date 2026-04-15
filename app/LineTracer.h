#ifndef ETTR_APP_LINETRACER_H_
#define ETTR_APP_LINETRACER_H_

#include "LineMonitor.h"
#include "Walker.h"

class LineTracer {
public:
    LineTracer(const LineMonitor* lineMonitor, Walker* walker);
    void run();
    float calcPropValue(int diffBrightness);

private:
    const LineMonitor* mLineMonitor;
    Walker* mWalker;
    bool mIsInitialized;
    int mOldDiff;
    float mIntegral;

    static const float Kp;
    static const float Ki;
    static const float Kd;
    static const int bias;
};

#endif