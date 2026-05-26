#include "../include/MotionController.hpp"
#include "SpatialData.hpp"
#include "../include/globals.hpp"
#include "../include/util/Util.hpp"

constexpr float PI = 3.1415f;


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

    float d = normalizeAngle(targetAngle - current);
    
   
    if(d >= 0.005){
        motors.powerEngines(1,-1);
    }
    else if(d <= -0.005){
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