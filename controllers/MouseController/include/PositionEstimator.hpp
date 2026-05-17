#pragma once
#include "./Interfaces/ISensors.hpp"
#include "globals.hpp"
#include "array"

class PositionEstimator{
    private:
        ISensors& sensors;
        std::array<float,2> previousEncoderReadings = {17.0,17.0};
        std::array<float,2> encoderReadings = {17.0,17.0};
    public:
        PositionEstimator(ISensors& sensors);
        void updateAngleEstimation();
        void updateCoordinateEstimation();


};