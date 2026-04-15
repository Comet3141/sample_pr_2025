/******************************************************************************
 *  ScenarioTracer.h (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Class ScenarioTracer
 *  Author: Kenya Yabe
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_APP_SCENARIOTRACER_H_
#define ETTR_APP_SCENARIOTRACER_H_

#include "Walker.h"
#include "SimpleTimer.h"
#include "Scenario.h"

class ScenarioTracer {
public:
    ScenarioTracer(Walker* walker,
                   Scenario* scenario,
                   SimpleTimer* timer);

    void run();

private:
    enum State {
        UNDEFINED,
        INITIAL,
        WALKING
    };

    Walker* mWalker;
    Scenario* mScenario;
    SimpleTimer* mSimpleTimer;
    State mState;

    void initAction();
    void setCommand(SceneCommands command);
    void modeChangeAction();
    void execUndefined();
    void execInitial();
    void execWalking();
};

#endif  // ETTR_APP_SCENARIOTRACER_H_
