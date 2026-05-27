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
      mapper(map,motionController,sensors),
      solver(),
      positionEstimator(sensors)

{
}


void Controller::step(){

      
   

    positionEstimator.updateAngleEstimation();
    positionEstimator.updateCoordinateEstimation();

    mapper.step();
    motionController.step();
 
    
    return;
}