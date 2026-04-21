#include "../include/Interfaces/IMotors.hpp"
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

class WebotsMotors : public IMotors {
public:
    WebotsMotors(webots::Robot* robot) {

        leftMotor = robot->getMotor("motor1");
        rightMotor = robot->getMotor("motor2");

        leftMotor->setPosition(INFINITY);
        rightMotor->setPosition(INFINITY);
        leftMotor->setVelocity(0.0);
        rightMotor->setVelocity(0.0);
        
    }

    void  powerEngines (float left, float right) override{
        leftMotor->setVelocity(left); 
        rightMotor->setVelocity(right);

    }




private:
    webots::Motor *leftMotor ;
    webots::Motor *rightMotor;
};