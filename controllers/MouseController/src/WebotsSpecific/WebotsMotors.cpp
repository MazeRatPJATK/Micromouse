#include "../include/WebotsSpecific/WebotsMotors.hpp"
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>



WebotsMotors::WebotsMotors(webots::Robot* robot) {

        leftMotor = robot->getMotor("motor1");
        rightMotor = robot->getMotor("motor2");

        leftMotor->setPosition(INFINITY);
        rightMotor->setPosition(INFINITY);
        leftMotor->setVelocity(0.0);
        rightMotor->setVelocity(0.0);
        
}

void WebotsMotors::powerEngines (float left, float right) {
        leftMotor->setVelocity(left); 
        rightMotor->setVelocity(right);
}

std::array<float, 2> WebotsMotors::getPower() const {
    return {leftPower, rightPower};
}