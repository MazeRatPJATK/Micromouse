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






// void PositionEstimator::updateAngleEstimation() {
//     auto enc = sensors.getEncoderReadings();
//     float leftDistance  = (enc[0] / (2 * PI)) * wheelCircumference;
//     float rightDistance = (enc[1] / (2 * PI)) * wheelCircumference;

//     float angle = (rightDistance - leftDistance) / distanceBetweenWheels;
//     spatialData.angle = angle;
//     spatialData.angle = normalizeAngle(spatialData.angle);
// }



void PositionEstimator::updateAngleEstimation() {
    updateAngleEstimationBasedOnEncoders();
    correctAngleEstimationBasedOnDistanceSensors();
}

void PositionEstimator::updateAngleEstimationBasedOnEncoders() {
    auto enc = sensors.getEncoderReadings();

    double leftDistance  = (enc[0] / (2 * PI)) * wheelCircumference;
    double rightDistance = (enc[1] / (2 * PI)) * wheelCircumference;

    double deltaLeft  = leftDistance  - prevLeftDistance;
    double deltaRight = rightDistance - prevRightDistance;

    prevLeftDistance  = leftDistance;
    prevRightDistance = rightDistance;

    double deltaAngle = (deltaRight - deltaLeft) / distanceBetweenWheels;

    spatialData.angle = normalizeAngle(spatialData.angle + deltaAngle);
}

void PositionEstimator::correctAngleEstimationBasedOnDistanceSensors() {
    constexpr float WALL_DETECTION_THRESHOLD_MM = 750.0f;
    constexpr float epsilon = 12.5f;


    std::array<float,4> readings = sensors.getDistanceReadings();
    float rightForwardReading = readings[0];
    float leftForwardReading = readings[3];
    float rightAngledReading = readings[1];
    float leftAngledReading = readings[2];

    if(rotating)return;
    bool wallsOnBothSidesPresent = leftAngledReading < WALL_DETECTION_THRESHOLD_MM &&  rightAngledReading < WALL_DETECTION_THRESHOLD_MM;
    bool wallInFrontPresent = leftForwardReading < WALL_DETECTION_THRESHOLD_MM &&  rightForwardReading < WALL_DETECTION_THRESHOLD_MM;



    if(wallInFrontPresent && !wallInFrontPresent){
        if(leftAngledReading - rightAngledReading > epsilon){
            spatialData.angle  = spatialData.angle  + 0.02;
        }
        if(rightAngledReading - leftAngledReading > epsilon){
            spatialData.angle  = spatialData.angle  - 0.02;
        }
        return;
    }

    if(rightAngledReading < (530)  && !wallInFrontPresent){
        spatialData.angle  = spatialData.angle  + 0.02;
        return;
    }

    if(leftAngledReading < (530)  && !wallInFrontPresent ){
        spatialData.angle  = spatialData.angle  - 0.02;
        
    }


}