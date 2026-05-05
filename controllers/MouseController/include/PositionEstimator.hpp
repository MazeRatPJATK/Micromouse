#pragma once
#include "./Interfaces/ISensors.hpp"
#include "globals.hpp"

class PositionEstimator{
    private:
        ISensors& sensors;
    public:
        PositionEstimator(ISensors& sensors);
        void updateAngleEstimation();

};