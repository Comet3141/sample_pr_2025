/******************************************************************************
 *  Scene.h  (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Struct Scene
 *  Author: Kenya Yabe
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_APP_SCENE_H_
#define ETTR_APP_SCENE_H_

enum SceneCommands {
    GO_STRAIGHT = 0,
    TURN_LEFT,
    TURN_RIGHT
};

struct Scene {
    SceneCommands command;
    int           time;
    Scene*        next;
};

#endif  // ETTR_APP_SCENE_H_
