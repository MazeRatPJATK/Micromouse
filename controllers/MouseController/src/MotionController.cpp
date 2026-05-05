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

    float kp = 1;
    float current = spatialData.angle;
    float error = targetAngle - current;

    float speed = kp * error;

    if(targetAngle - current < 1){return;} //angleTolerance instead of 1
   motors.powerEngines(-speed,speed);
}

void MotionController::step(){
    adjustVelocity();
    adjustAngle();

}