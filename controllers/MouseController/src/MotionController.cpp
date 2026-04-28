#include "../include/MotionController.hpp"
#include "SpatialData.hpp"
#include "../include/globals.hpp"

MotionController::MotionController(IMotors& motors): motors(motors){}

void MotionController::setTargetVelocity(float velocity){
    targetVelocity = velocity;
}

void MotionController::setTargetAngle(float angle){
    targetAngle = angle;
}

void MotionController::adjustVelocity(){
    motors.powerEngines(targetVelocity,targetVelocity);

    //TODO velocity adjusting
}

void MotionController::adjustAngle(){
    motors.powerEngines(1,-1);
    //TODO: angle adjusting to the target
}

void MotionController::step(){
    adjustVelocity();
    adjustAngle();

}