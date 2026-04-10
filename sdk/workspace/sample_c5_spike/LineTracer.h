#ifndef LINETRACER_H
#define LINETRACER_H

#include "spikeapi.h"

typedef struct {
    float64_t Kp;
    float64_t Ki;
    float64_t Kd;
    int16_t target_lux;
} LineTracer;

void LineTracer_init(LineTracer* self, float64_t p, float64_t i, float64_t d, int16_t target);
float64_t LineTracer_calculate_steering(LineTracer* self, int16_t current_lux);

#endif /* LINETRACER_H */