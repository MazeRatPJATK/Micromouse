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


    float distance = 0.0F;
    if(!rotating){
        distance =  (encoderSum - previousEncoderSum)/2;
    }

    if (std::isnan(spatialData.x)) {
        spatialData.x = 0.0;
    }

    if (std::isnan(spatialData.y)) {
        spatialData.y = 0.0;
    }

    spatialData.x += cos(spatialData.angle) * distance;
    spatialData.y += sin(spatialData.angle) * distance;
    
    // std::cout << "Encoder Sum: " << encoderSum << std::endl;
    // std::cout << "Previous Encoder Sum: " << previousEncoderSum << std::endl;
    std::cout << "Distance: " << distance << std::endl;
    // std::cout << "SD.Angle: " << spatialData.angle << std::endl;
    // std::cout << "Cosinus [SD.Angle]: " << cos(spatialData.angle) << std::endl;
    // std::cout << "Sinus [SD.Angle]: " << sin(spatialData.angle) << std::endl;
    // std::cout<< "x :" << spatialData.x << std::endl;
    // std::cout<< "y :" << spatialData.y << std::endl;
    
}




void PositionEstimator::updateAngleEstimation(){
    std::array<float,2> encoderReadings = sensors.getEncoderReadings();
    
    float angle = ((encoderReadings[0]/(2*PI))*wheelCircumference - (encoderReadings[1]/(2*PI))*wheelCircumference) / distanceBetweenWheels; //im not sure of this equation
    if(angle > (2*PI)){
        int n = (int)(angle / (2*PI));
        angle = angle + ((2*PI)*n);
    }

    if( angle < -(2*PI)){
        int n = (int)(angle / (2*PI));
        angle = angle - ((2*PI)*n);
    }
    spatialData.angle = angle;

    // std::cout << "Angle: " << angle << std::endl;
    std::cout<< "Left Encoder :" << encoderReadings[0] << std::endl;
    std::cout<< "Right Encoder :" << encoderReadings[1] << std::endl;
}

