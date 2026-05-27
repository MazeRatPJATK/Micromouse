#include "../include/MotionController.hpp"
#include "SpatialData.hpp"
#include "../include/globals.hpp"

#include "iostream"

MotionController::MotionController(IMotors& motors): motors(motors){}

void MotionController::setTargetVelocity(float velocity){
    targetVelocity = velocity;
}

void MotionController::setTargetAngle(float angle){
    targetAngle = angle;
}

void MotionController::adjustVelocity(){
    motors.powerEngines(targetVelocity, targetVelocity); //TODO: actually make the robot try and reach the target velocity
    //TODO velocity adjusting
}

void MotionController::adjustAngle(){

    rotating = true;
    float kp = 1;
    float current = spatialData.angle;
    float error = targetAngle - current;

    // std::cout << "***********************" << std::endl;
    std::cout << "Target angle: " << targetAngle << std::endl;
    std::cout << "Current angle: " << current << std::endl;

    float speed = kp * error;
    if(speed < 1){speed = 1;}

    if(targetAngle - current < 0.01){rotating = false; return;} //instead of 0.1 there should be angleTolerance in the future
    motors.powerEngines(-speed,speed);
}

void MotionController::step(){
        float currentAngle = spatialData.angle;

        adjustVelocity();
        adjustAngle();  


}