/******************************************************************************
 * LineTracer.h (for SPIKE)
 * PID制御対応
 *****************************************************************************/

#ifndef ETTR_UNIT_LINETRACER_H_
#define ETTR_UNIT_LINETRACER_H_

#include "LineMonitor.h"
#include "Walker.h"

class LineTracer {
public:
    LineTracer(const LineMonitor* lineMonitor, Walker* walker);
    void run();

private:
    const LineMonitor* mLineMonitor;
    Walker* mWalker;
    bool mIsInitialized;

    // PID制御用定数（static constで定義）
    static const float Kp; 
    static const float Ki; 
    static const float Kd; 
    static const int bias;

    // 内部状態保持用
    int   mOldDiff;  // 前回の偏差（D用）
    float mIntegral; // 偏差の累積（I用）

    float calcPropValue(int diffBrightness);
};

#endif