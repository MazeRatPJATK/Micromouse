#include "../include/MotionController.hpp"
#include "../include/globals.hpp"

#include "iostream"

MotionController::MotionController(IMotors& motors, ISensors& sensors): motors(motors), sensors(sensors){}

void MotionController::setTargetVelocity(float velocity){
    targetVelocity = velocity;
}

void MotionController::setTargetAngle(float angle){
    targetAngle = angle;
}

void MotionController::calculateCurrentVelocity(){
    // std::cout << "Test\n";
    std::array<float,2> encoderReadings = sensors.getEncoderReadings();

    float leftWheelRadians = encoderReadings[0] - previousReadings[0];
    float rightWheelRadians = encoderReadings[1] - previousReadings[1];
    previousReadings[0] = encoderReadings[0];
    previousReadings[1] = encoderReadings[1];
    std::cout << "Left Wheel Radians: " << leftWheelRadians << "\n";
    std::cout << "Right Wheel Radians: " << rightWheelRadians << "\n";
    
    float averageRadians = (leftWheelRadians + rightWheelRadians) / 2;
    std::cout << "Average Radians: " << averageRadians << "\n";

    float averageVelocity2 = averageRadians / (float(timeStep) / 1000.0f);
    // float averageVelocity = averageDistanceCovered / 0.016;
    std::cout << "Average Velocity [rad/s]: " << averageVelocity2 << " rad/s \n";
}

void MotionController::adjustVelocity(){
    if(rotating == false){
        motors.powerEngines(targetVelocity, targetVelocity); //TODO: actually make the robot try and reach the target velocity

    }

    // if (currentVelocity != targetVelocity) {
    //     motors.powerEngines(targetVelocity, targetVelocity);
    // }
    
    std::cout << "Target Velocity: " << targetVelocity << "\n";
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
    std::cout << "****************************************\n";
    // std::cout << "target: " << targetAngle << std::endl;
    
    adjustVelocity();
    calculateCurrentVelocity();
    adjustAngle(); 
}