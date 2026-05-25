#include "PositionEstimator.hpp"
#include <array>
#include "globals.hpp"
#include <iostream>
#include "cmath"
#include "../include/util/Util.hpp"

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

    spatialData.x += sin(spatialData.angle) * distance;
    spatialData.y += cos(spatialData.angle) * distance;
       
}






void PositionEstimator::updateAngleEstimation() {
    auto enc = sensors.getEncoderReadings();
    float leftDistance  = (enc[0] / (2 * PI)) * wheelCircumference;
    float rightDistance = (enc[1] / (2 * PI)) * wheelCircumference;

    float angle = (rightDistance - leftDistance) / distanceBetweenWheels;
    spatialData.angle = angle;
    spatialData.angle = normalizeAngle(spatialData.angle);
}



