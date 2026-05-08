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
    motionController.setTargetAngle(2);

    motionController.step();
    // motors.powerEngines(3.14f,3.14f);
    // // std::array<int16_t,4> readings = {0,0,0,0};
    // std::array<float,2> distance_readings = {0,0};
    // //readings = sensors.getDistanceReadings();
    // distance_readings = sensors.getEncoderReadings();

    // // std::cout << "encoder0 Value: " << distance_readings[0] << std::endl;
    // std::cout << "Distance covered " << distance_readings[0]/6.28 * 0.05 << std::endl;

    // if(true){
    //     mapper.step();
    // }
    // // else if(){
    // //     solver.step()
    // // }



    return;
}