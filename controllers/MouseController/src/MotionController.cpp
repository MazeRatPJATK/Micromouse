#include "../include/MotionController.hpp"
#include "SpatialData.hpp"
#include "../include/globals.hpp"
#include <iostream>
#include "../include/util/Util.hpp"




MotionController::MotionController(IMotors& motors): motors(motors){}

void MotionController::setTargetVelocity(float velocity){
    targetVelocity = velocity;
}

void MotionController::setTargetAngle(float angle){
    targetAngle = normalizeAngle(angle);
}

void MotionController::adjustVelocity(){
    motors.powerEngines(targetVelocity,targetVelocity); //TODO: actually make the robot try and reach the target velocity
    //TODO velocity adjusting
}

void MotionController::adjustAngle(){

    rotating = true;
    float current = spatialData.angle;
   
    if((targetAngle > current) && ((targetAngle - current) > 0.01)){
        motors.powerEngines(1,-1);
    } 
    else if((current > targetAngle) && ((current - targetAngle) > 0.01)){
        motors.powerEngines(-1,1);       
    }
    else{
        rotating = false;
    }
    return;
    
}

void MotionController::step(){
        adjustVelocity();
        adjustAngle();  


}