#include "PositionEstimator.hpp"
#include <array>

PositionEstimator::PositionEstimator(ISensors& sensors):sensors(sensors){};

void PositionEstimator::updateAngleEstimation(){
    std::array<float,2> encoderReadings = sensors.getEncoderReadings();
    spatialData.angle = 1;

}