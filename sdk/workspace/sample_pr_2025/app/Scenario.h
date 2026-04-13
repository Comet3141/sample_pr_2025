/******************************************************************************
 *  Scenario.h  (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Class Scenario
 *  Author: Kenya Yabe
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_APP_SCENARIO_H_
#define ETTR_APP_SCENARIO_H_

#include "spikeapi.h"
#include "Scene.h"

class Scenario {
public:
    explicit Scenario(Scene* scene);

    void add(Scene* scene);
    Scene* top() const;
    Scene* current() const;
    Scene* next();
    SceneCommands currentSceneCommand() const;
    uint32_t currentSceneTime() const;

private:
    Scene* mTopScene;
    Scene* mCurrentScene;
};

#endif  // ETTR_APP_SCENARIO_H_
