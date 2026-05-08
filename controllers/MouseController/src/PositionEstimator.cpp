#include "PositionEstimator.hpp"
#include <array>
#include "globals.hpp"
#include <iostream>

constexpr double PI = 3.141592;

PositionEstimator::PositionEstimator(ISensors& sensors):sensors(sensors){};

void PositionEstimator::updateAngleEstimation(){
    std::array<float,2> encoderReadings = sensors.getEncoderReadings();
    
    float angle =   ((encoderReadings[0]/(2*PI))*wheelCircumference - (encoderReadings[1]/(2*PI))*wheelCircumference) / distanceBetweenWheels; //im not sure of this equation
    std::cout << angle << std::endl;
    if(angle > (2*PI)){
        int n = (int)(angle / (2*PI));
        angle = angle + ((2*PI)*n);
    }

    if( angle < -(2*PI)){
        int n = (int)(angle / (2*PI));
        angle = angle - ((2*PI)*n);
    }
    spatialData.angle = angle;
   
    // std::cout << angle << std::endl;
}