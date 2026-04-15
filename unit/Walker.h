/******************************************************************************
 *  Walker.cpp (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Class Walker
 *  Author: Kazuhiro.Kawachi
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_UNIT_WALKER_H_
#define ETTR_UNIT_WALKER_H_

#include "Motor.h"

class Walker {
public:
    static const int RIGHT_TURN = -30;  //���^�[�����̐���l
    static const int LEFT_TURN = 30;    //�E�^�[�����̐���l
  
    Walker(spikeapi::Motor& leftWheel,
                    spikeapi::Motor& rightWheel);

    void init();
    void run();
    void setCommand(float turn);

private:
    spikeapi::Motor& mLeftWheel;
    spikeapi::Motor& mRightWheel;
    int mTurn;

    const int8_t pwm =95;
 
};

#endif  // ETTR_UNIT_WALKER_H_
