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
      sensors(sensors),
      mapper(map),
      solver(),
      motionController(motionController),
      positionEstimator(sensors)

{
}


void Controller::step(){

    positionEstimator.updateAngleEstimation();

    motionController.setTargetAngle(3.14);
    motionController.step();
    return;
}