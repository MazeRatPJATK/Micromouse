#include "PositionEstimator.hpp"
#include <array>
#include "globals.hpp"
#include <iostream>

constexpr double PI = 3.14;

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
         std::cout << "n: " <<  n << std::endl;
                  std::cout << "angle before: " <<  angle << std::endl;

        angle = angle - ((2*PI)*n);
                 std::cout << "angle after: " <<  angle << std::endl;

    }
    spatialData.angle = angle;
   
    // std::cout << angle << std::endl;
}