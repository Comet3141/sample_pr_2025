/******************************************************************************
 * RandomWalker.h (for SPIKE )
 *****************************************************************************/

#ifndef ETTR_APP_RANDOMWALKER_H_
#define ETTR_APP_RANDOMWALKER_H_

#include "Starter.h"
#include "SimpleTimer.h"
#include "Clock.h"
#include "LineTracer.h"
#include "ScenarioTracer.h"

class RandomWalker {
public:
    // 第5引数に clock を追加
    RandomWalker(LineTracer* lineTracer,
                 ScenarioTracer* scenarioTracer,
                 const Starter* starter,
                 SimpleTimer* simpleTimer,
                 const spikeapi::Clock& clock);

    void run();

private:
    enum State {
        UNDEFINED,
        WAITING_FOR_START,
        LINE_TRACING,
        SCENARIO_TRACING
    };

    static const int MIN_TIME;
    static const int MAX_TIME;

    LineTracer* mLineTracer;
    ScenarioTracer* mScenarioTracer;
    const Starter* mStarter;
    SimpleTimer* mSimpleTimer;
    State mState;

    int getRandomTime();
    void modeChangeAction();
    void execUndefined();
    void execWaitingForStart();
    void execLineTracing();
    void execScenarioTracing();
};

#endif  // ETTR_APP_RANDOMWALKER_H_