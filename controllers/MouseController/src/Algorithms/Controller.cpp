//std 
#include <iostream>
#include <array>

//webots
#include <webots/Robot.hpp>
#include <webots/DistanceSensor.hpp>

//our own
#include "../include/Algorithms/Controller.hpp"
#include "../include/Interfaces/IMotors.hpp"
#include "../include/Interfaces/ISensors.hpp"



Controller::Controller(ISensors& sensors, MotionController& motionController)
    : map(),
      motionController(motionController),
      sensors(sensors),
      mapper(map, motionController, sensors, [this](Command cmd) {
          enqueCommand(cmd);
      }),

      solver(),
      positionEstimator(sensors)

{
    controllerState = ControllerState::IDLE;
}


void Controller::step(){

      
   

    positionEstimator.updateAngleEstimation();
    positionEstimator.updateCoordinateEstimation();

    mapper.step();
    applyCommands();
    motionController.step();
 
    
    return;
}

void Controller::applyCommands(){
    
    if(commandQueue.empty()){
    controllerState = ControllerState::IDLE;
     return;
    }


    Command& cmd = commandQueue.front();


    switch (controllerState)
    {
        case ControllerState::IDLE:
            initNewCommand(cmd);
            controllerState = ControllerState::EXECUTING_COMMAND;
            break;
        case ControllerState::EXECUTING_COMMAND:
            if(hasFinishedCommand(cmd)){
            if (cmd.onComplete) {
                  cmd.onComplete(); 
            }
            commandQueue.pop();
            controllerState = ControllerState::IDLE;
            }
            break;
   
    }

    return;
}

void Controller::initNewCommand(Command& cmd){
    motionController.setTargetAngle(cmd.targetAngle);
    motionController.setTargetVelocity(cmd.targetVelocity);   
}

bool Controller::hasFinishedCommand(Command& cmd){
    float epsilon = 0.8f;
    float angleEpsilon = 0.05f;
    bool x_ok = std::fabs(spatialData.x - cmd.targetX) < epsilon;
    bool y_ok = std::fabs(spatialData.y - cmd.targetY) < epsilon;
    bool angle_ok = std::fabs(spatialData.angle - cmd.targetAngle) < angleEpsilon;

    if (x_ok && y_ok && angle_ok) std::cout << "finished cmd" << std::endl;
    // std::cout << x_ok << y_ok << angle_ok << std::endl;
    std::cout << "y: " << spatialData.y << " x: " << spatialData.x << std::endl;
        // std::cout << "angle: " << spatialData.angle << std::endl;


    return x_ok && y_ok && angle_ok;
}

void Controller::enqueCommand(Command cmd){
    commandQueue.push(cmd);

}