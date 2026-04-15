#ifndef ETTR_UNIT_LINEMONITOR_H_
#define ETTR_UNIT_LINEMONITOR_H_

#include "ColorSensor.h"

class LineMonitor {
public:
    explicit LineMonitor(const spikeapi::ColorSensor& colorSensor);
    int calDiffReflection() const;
    void setThreshold(int8_t threshold);

private:
    const spikeapi::ColorSensor& mColorSensor;
    int8_t mThreshold;

    static const int8_t INITIAL_THRESHOLD_BLACK;
    static const int8_t INITIAL_THRESHOLD_WHITE;
};

#endif