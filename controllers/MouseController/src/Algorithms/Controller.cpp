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

    // we re using set target Angle and velocity here only for debbuging purposes. you should not use it here
    motionController.setTargetAngle(3.14159);
    motionController.setTargetVelocity(2);
    motionController.step();
    return;
}