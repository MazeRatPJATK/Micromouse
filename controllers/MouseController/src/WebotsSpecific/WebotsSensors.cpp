#include "../include/WebotsSpecific/WebotsSensors.hpp"

WebotsSensors::WebotsSensors(webots::Robot* robot) {
    distanceSensors[0] = robot->getDistanceSensor("s1");
    distanceSensors[1] = robot->getDistanceSensor("s2");
    distanceSensors[2] = robot->getDistanceSensor("s3");
    distanceSensors[3] = robot->getDistanceSensor("s4");

    distanceSensors[0]->enable(32);
    distanceSensors[1]->enable(32);
    distanceSensors[2]->enable(32);
    distanceSensors[3]->enable(32);


    positionSensors[0] = robot->getPositionSensor("encoder1");
    positionSensors[1] = robot->getPositionSensor("encoder2");
    positionSensors[0]->enable(32);
    positionSensors[1]->enable(32);
}

std::array<int16_t, 4> WebotsSensors::getDistanceReadings() const {
    return {
        static_cast<int16_t>(distanceSensors[0]->getValue()),
        static_cast<int16_t>(distanceSensors[1]->getValue()),
        static_cast<int16_t>(distanceSensors[2]->getValue()),
        static_cast<int16_t>(distanceSensors[3]->getValue())
    };
}

IMUData WebotsSensors::getIMUReadings() const {
    return IMUData();
}

std::array<float, 2>  WebotsSensors::getEncoderReadings() const {
    return {
        static_cast<float>(positionSensors[0]->getValue()),
        static_cast<float>(positionSensors[1]->getValue())
    };
}