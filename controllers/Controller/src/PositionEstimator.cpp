#include "PositionEstimator.hpp"
#include <array>
#include "globals.hpp"
#include <cmath>
#include "../include/util/Util.hpp"

constexpr double PI = 3.141592;
constexpr float GRID_CELL_SIZE = 18.0f;

PositionEstimator::PositionEstimator(ISensors& sensors):sensors(sensors){};

void PositionEstimator::updateCoordinateEstimation(){   
    updatePositionEstimationBasedOnEncoders(); 
    correctPositionEstimationBasedOnSensors();
}

void PositionEstimator::updatePositionEstimationBasedOnEncoders(){
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

void PositionEstimator::correctPositionEstimationBasedOnSensors(){
    constexpr float WALL_DETECTION_THRESHOLD_MM = 650.0f;
    constexpr float epsilon = 2.5f;


    std::array<float,4> readings = sensors.getDistanceReadings();
    float rightForwardReading = readings[0];
    float leftForwardReading = readings[3];
    float rightAngledReading = readings[1];
    float leftAngledReading = readings[2];

    bool wallsOnBothSidesPresent = leftAngledReading < WALL_DETECTION_THRESHOLD_MM &&  rightAngledReading < WALL_DETECTION_THRESHOLD_MM;
    bool wallInFrontPresent = leftForwardReading < WALL_DETECTION_THRESHOLD_MM &&  rightForwardReading < WALL_DETECTION_THRESHOLD_MM;

    std::array<int,2> currentGridCoordinates = {
        static_cast<int>(std::round(spatialData.x / GRID_CELL_SIZE)),
        static_cast<int>(std::round(spatialData.y / GRID_CELL_SIZE))
    };

    if(wallsOnBothSidesPresent && !wallInFrontPresent){
        if((leftAngledReading - rightAngledReading < epsilon) || (rightAngledReading - leftAngledReading < epsilon)){
           if(snapToRightAngle(sin(spatialData.angle)) != 0) spatialData.y = currentGridCoordinates[1] * GRID_CELL_SIZE;
           if(snapToRightAngle(cos(spatialData.angle)) != 0){spatialData.x = currentGridCoordinates[0] * GRID_CELL_SIZE;}
        };

    }
}

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

    constexpr float WALL_DETECTION_THRESHOLD_MM = 650.0f;
    constexpr float angled_epsilon = 2.5f;
    constexpr float forward_epsilon = 2.5f;


    std::array<float,4> readings = sensors.getDistanceReadings();
    float rightForwardReading = readings[0];
    float leftForwardReading = readings[3];
    float rightAngledReading = readings[1];
    float leftAngledReading = readings[2];

  

    if(rotating)return;
    bool wallsOnBothSidesPresent = leftAngledReading < WALL_DETECTION_THRESHOLD_MM &&  rightAngledReading < WALL_DETECTION_THRESHOLD_MM;
    bool wallInFrontPresent = leftForwardReading < WALL_DETECTION_THRESHOLD_MM &&  rightForwardReading < WALL_DETECTION_THRESHOLD_MM;



    if(wallsOnBothSidesPresent && !wallInFrontPresent){
        if(leftAngledReading - rightAngledReading > angled_epsilon){
            spatialData.angle  = spatialData.angle  + 0.005;
        }
        if(rightAngledReading - leftAngledReading > angled_epsilon){
            spatialData.angle  = spatialData.angle  - 0.005;
        }
    }
    else if (wallInFrontPresent && !wallsOnBothSidesPresent){
        if (fabs(leftForwardReading - rightForwardReading) > forward_epsilon){
            if(leftForwardReading > rightForwardReading){
                spatialData.angle  = spatialData.angle  - 0.005;
            }
            else if (rightForwardReading > leftForwardReading){
                spatialData.angle  = spatialData.angle  + 0.005;
            }
        }
    }
    else if(rightAngledReading < (475)  && !wallInFrontPresent){
        spatialData.angle  = spatialData.angle  + 0.005;
    }
    else if(leftAngledReading < (475)  && !wallInFrontPresent ){
        spatialData.angle  = spatialData.angle  - 0.005;   
    }
};

