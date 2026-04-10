#include "LineTracer.h"

void LineTracer_init(LineTracer* self, float64_t p, float64_t i, float64_t d, int16_t target) {
    self->Kp = p;
    self->Ki = i;
    self->Kd = d;
    self->target_lux = target;
}

float64_t LineTracer_calculate_steering(LineTracer* self, int16_t current_lux) {
    static float64_t diff[2] = {0, 0};
    static float64_t integral = 0;
    
    float64_t error = (float64_t)(self->target_lux - current_lux);

    diff[0] = diff[1];
    diff[1] = error;
    integral += (diff[0] + diff[1]) / 2.0;

    float64_t p_term = self->Kp * diff[1];
    float64_t i_term = self->Ki * integral;
    float64_t d_term = self->Kd * (diff[1] - diff[0]);

    return p_term + i_term + d_term;
}