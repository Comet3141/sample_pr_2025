#include "LineTracer.h"
#include "spike/pup/motor.h"
#include "spike/pup/colorsensor.h"

/* センサー・モーターのデバイスポインタを保持する変数 */
static pup_motor_t *motor_left;
static pup_motor_t *motor_right;
static pup_device_t *color_sensor;

/* PID制御用のゲイン (環境に合わせて調整してください) */
static const float Kp = 0.5f;
static const float Ki = 0.01f;
static const float Kd = 0.05f;
static const int16_t target_lux = 50; /* 目標の反射光 (白と黒の中間) */

/* PID制御用の過去データ保持 */
static float diff[2] = {0, 0};
static float integral = 0;

/* アプリケーション初期化時に app.c から呼ばれる関数 */
void LineTracer_Configure(pbio_port_id_t left_motor, pbio_port_id_t right_motor, pbio_port_id_t color_sensor_port) {
    motor_left = pup_motor_get_device(left_motor);
    motor_right = pup_motor_get_device(right_motor);
    color_sensor = pup_color_sensor_get_device(color_sensor_port);
    
    diff[0] = 0.0f;
    diff[1] = 0.0f;
    integral = 0.0f;
}

/* 100ms周期で自動的に実行されるライントレースタスク */
void tracer_task(intptr_t exinf) {
    /* 1. カラーセンサーから反射光を取得 */
    int16_t current_lux = pup_color_sensor_reflection(color_sensor);

    /* 2. PID計算 */
    float error = (float)(target_lux - current_lux);
    
    diff[0] = diff[1];
    diff[1] = error;
    integral += error;

    float p_term = Kp * diff[1];
    float i_term = Ki * integral;
    float d_term = Kd * (diff[1] - diff[0]);

    float steering = p_term + i_term + d_term;

    /* 3. モーターのパワー計算 */
    int base_power = 30; /* 基本の走行パワー（直進速度） */
    int left_power = base_power + (int)steering;
    int right_power = base_power - (int)steering;

    /* パワーを -100 〜 100 の範囲に制限 */
    if (left_power > 100) left_power = 100;
    if (left_power < -100) left_power = -100;
    if (right_power > 100) right_power = 100;
    if (right_power < -100) right_power = -100;

    /* 4. モーターへの出力 */
    pup_motor_set_power(motor_left, left_power);
    pup_motor_set_power(motor_right, right_power);
}