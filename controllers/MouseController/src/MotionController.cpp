#include "../include/MotionController.hpp"
#include "../include/globals.hpp"

#include "iostream"

MotionController::MotionController(IMotors& motors, ISensors& sensors): motors(motors), sensors(sensors){}

void MotionController::setTargetVelocity(float velocity){
    targetVelocity = velocity;
}

void MotionController::setTargetAngle(float angle){
    targetAngle = angle;

    // if (abs(targetAngle) < 0.01f) {
    //     targetAngle = 0.0f;
    // }
    // else if (abs(targetAngle - 1.57f) < 0.01f) {
    //     if (targetAngle < 0.0f) {
    //         targetAngle = -1.57f;
    //     }
    //     else {
    //         targetAngle = 1.57f;
    //     }
    // }
    // else if (abs(targetAngle - 3.13f) < 0.01f) {
    //     if (targetAngle < 0.0f) {
    //         targetAngle = -3.13f;
    //     }
    //     else {
    //         targetAngle = 3.13f;
    //     }
    // }
}

void MotionController::calculateCurrentVelocity(){
    // std::cout << "Test\n";
    std::array<float,2> encoderReadings = sensors.getEncoderReadings();

    float leftWheelRadians = encoderReadings[0] - previousReadings[0];
    float rightWheelRadians = encoderReadings[1] - previousReadings[1];
    previousReadings[0] = encoderReadings[0];
    previousReadings[1] = encoderReadings[1];
    // std::cout << "Left Wheel Radians: " << leftWheelRadians << "\n";
    // std::cout << "Right Wheel Radians: " << rightWheelRadians << "\n";
    
    float averageRadians = (leftWheelRadians + rightWheelRadians) / 2;
    // std::cout << "Average Radians: " << averageRadians << "\n";

    float currentVelocity = averageRadians / (float(timeStep) / 1000.0f);
    // float currentVelocity = averageDistanceCovered / 0.016;
    if(debugMode[0]) std::cout << "Average Velocity [rad/s]: " << currentVelocity << " rad/s \n";
}

void MotionController::adjustVelocity(){
    if(rotating == false){
        motors.powerEngines(targetVelocity, targetVelocity);

        if (abs(currentVelocity) - targetVelocity > velocityTolerance){
            if (currentVelocity - targetVelocity < -velocityTolerance){
                velocityCorrection -= 0.1f;     
            }
            else if (currentVelocity - targetVelocity > velocityTolerance){
                velocityCorrection += 0.1f;
            }
            
        }
        
        motors.powerEngines(targetVelocity + velocityCorrection, targetVelocity + velocityCorrection); 
    }
    
    if(debugMode[0]) std::cout << "Target Velocity: " << targetVelocity << "\nVelocity Correction: " << velocityCorrection << "\n";
}


void MotionController::adjustAngle() {
    rotating = true;

    float current = spatialData.angle;
    float error = normalizeAngle(targetAngle - current);
    //0.000796344

    if(debugMode[0]) std::cout << "\n.\nTarget Angle " << targetAngle << "\n";
    if(debugMode[0]) std::cout << "Current Angle " << current << "\n";

    constexpr float epsilon = 0.01f;

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
    constexpr float minTurn = 0.02f;

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
        calculateCurrentVelocity();
}