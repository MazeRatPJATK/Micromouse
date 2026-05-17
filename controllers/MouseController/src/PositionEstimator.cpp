#include "PositionEstimator.hpp"
#include <array>
#include "globals.hpp"
#include <iostream>
#include "cmath"

constexpr double PI = 3.141592;

PositionEstimator::PositionEstimator(ISensors& sensors):sensors(sensors){};

void PositionEstimator::updateCoordinateEstimation(){
    previousEncoderReadings = encoderReadings;
    encoderReadings = sensors.getEncoderReadings();

    float encoderSum = encoderReadings[0]/(2*PI)*wheelCircumference  + (encoderReadings[1]/(2*PI))*wheelCircumference;
    float previousEncoderSum = previousEncoderReadings[0]/(2*PI)*wheelCircumference  + (previousEncoderReadings[1]/(2*PI))*wheelCircumference;


    float distance = 0;
    if(!rotating){
        distance =  (encoderSum - previousEncoderSum)/2;
    }

    spatialData.x += cos(spatialData.angle) * distance;
    spatialData.y += sin(spatialData.angle) * distance;
    
    // std::cout<< "x   :" << spatialData.x << std::endl;
    // std::cout<< "y   :" << spatialData.y << std::endl;
    
}




void PositionEstimator::updateAngleEstimation(){
    std::array<float,2> encoderReadings = sensors.getEncoderReadings();
    
    float angle =   ((encoderReadings[0]/(2*PI))*wheelCircumference - (encoderReadings[1]/(2*PI))*wheelCircumference) / distanceBetweenWheels; //im not sure of this equation
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

