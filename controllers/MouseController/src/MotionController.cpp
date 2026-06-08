#include "../include/MotionController.hpp"
#include "SpatialData.hpp"
#include "../include/globals.hpp"
#include "../include/util/Util.hpp"
#include <iostream>

constexpr float PI = 3.1415f;


MotionController::MotionController(IMotors& motors): motors(motors){}

void MotionController::setTargetVelocity(float velocity){
    targetVelocity = velocity;
}

void MotionController::setTargetAngle(float angle){
    targetAngle = normalizeAngle(angle);
}

void MotionController::adjustVelocity(){
    if(rotating == false){
        motors.powerEngines(targetVelocity,targetVelocity); //TODO: actually make the robot try and reach the target velocity

    }
    //TODO velocity adjusting
}





void MotionController::adjustAngle() {

    rotating = true;

    float current = spatialData.angle;

    float error = normalizeAngle(targetAngle - current);

    
    constexpr float epsilon = 0.02f;

    if (std::abs(error) < epsilon) {
        motors.powerEngines(0, 0);
        rotating = false;

        previousError = error;

        return;
    }

    // --- PD controller ---

    constexpr float kp = 6.0f;
    constexpr float kd = 0.5f;


    float derivative = (error - previousError) / (0.016f);

    float turn = kp * error + kd * derivative ;

  
    constexpr float maxTurn = 3.0f;
    constexpr float minTurn = 0.2f;

    if (turn > maxTurn)
        turn = maxTurn;

   
    if (turn < -maxTurn)
        turn = -maxTurn;

    if (turn > 0 && turn < minTurn)   turn = minTurn;
    if (turn < 0 && turn > -minTurn)  turn = -minTurn;



    motors.powerEngines(turn, -turn);

    previousError = error;
}


void MotionController::step(){
        adjustAngle(); 
        adjustVelocity();
}