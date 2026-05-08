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
    if(speed < 2){speed = 2;}

    if(targetAngle - current < 0.01){return;} //instead of 0.1 there should be angleTolerance in the future
    motors.powerEngines(-speed,speed);
}

void MotionController::step(){
    adjustVelocity();
    adjustAngle();

}