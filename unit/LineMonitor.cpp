#include "LineMonitor.h"

const int8_t LineMonitor::INITIAL_THRESHOLD_BLACK = 0;
const int8_t LineMonitor::INITIAL_THRESHOLD_WHITE = 100;

LineMonitor::LineMonitor(const spikeapi::ColorSensor& colorSensor)
    : mColorSensor(colorSensor),
      mThreshold((INITIAL_THRESHOLD_BLACK + INITIAL_THRESHOLD_WHITE)/2) {
}

int LineMonitor::calDiffReflection() const {
    int diff = mColorSensor.getReflection() - (int)mThreshold;
    return diff;
}

void LineMonitor::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}