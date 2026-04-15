/******************************************************************************
 * RandomWalker.cpp (for SPIKE )
 *****************************************************************************/

#include <stdlib.h>
#include "Clock.h"
#include "RandomWalker.h"

const int RandomWalker::MIN_TIME = 5000 * 1000;
const int RandomWalker::MAX_TIME = 15000 * 1000;

RandomWalker::RandomWalker(LineTracer* lineTracer,
                           ScenarioTracer* scenarioTracer,
                           const Starter* starter,
                           SimpleTimer* simpleTimer,
                           const spikeapi::Clock& clock)
    : mLineTracer(lineTracer),
      mScenarioTracer(scenarioTracer),
      mStarter(starter),
      mSimpleTimer(simpleTimer),
      mState(UNDEFINED) {
    
    // 外部から渡された安全な clock を使用して乱数を初期化
    srand(clock.now()); 
}

void RandomWalker::run() {
    switch (mState) {
    case UNDEFINED: execUndefined(); break;
    case WAITING_FOR_START: execWaitingForStart(); break;
    case LINE_TRACING: execLineTracing(); break;
    case SCENARIO_TRACING: execScenarioTracing(); break;
    default: break;
    }
}

int RandomWalker::getRandomTime() {
    return MIN_TIME +
        static_cast<int>(static_cast<double>(rand()) *
                         (MAX_TIME - MIN_TIME + 1.0) / (1.0 + RAND_MAX));
}

void RandomWalker::modeChangeAction() {
    mSimpleTimer->setTime(getRandomTime());
    mSimpleTimer->start();
}

void RandomWalker::execUndefined() {
    mState = WAITING_FOR_START;
}

void RandomWalker::execWaitingForStart() {
    if (mStarter->isPushed()) {
        mState = LINE_TRACING;
        modeChangeAction();
    }
}

void RandomWalker::execLineTracing() {
    mLineTracer->run();
    if (mSimpleTimer->isTimedOut()) {
        mSimpleTimer->stop();
        mState = SCENARIO_TRACING;
        modeChangeAction();
    }
}

void RandomWalker::execScenarioTracing() {
    mScenarioTracer->run();
    if (mSimpleTimer->isTimedOut()) {
        mSimpleTimer->stop();
        mState = LINE_TRACING;
        modeChangeAction();
    }
}