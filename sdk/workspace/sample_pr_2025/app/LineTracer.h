/******************************************************************************
 *  LineTracer.h (for SPIKE )
 *  Created on: 2025/01/05
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_APP_LINETRACER_H_
#define ETTR_APP_LINETRACER_H_

#include "LineMonitor.h"
#include "Walker.h"

class LineTracer {
public:
	static const float Kp;
	static const int   bias;
	
	LineTracer(const LineMonitor* lineMonitor,
               Walker* walker);

    void run();

private:
    const LineMonitor* mLineMonitor;
    Walker* mWalker;
    bool mIsInitialized;

    float calcPropValue(int diffReflection);
};

#endif  // ETTR_APP_LINETRACER_H_
