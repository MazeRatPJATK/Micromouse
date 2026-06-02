#include <webots/Robot.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
#include <array>
<<<<<<< Updated upstream
#include "WebotsSensors.cpp"
#include "WebotsMotors.cpp"
=======

//our own
#include "../include/WebotsSpecific/WebotsMotors.hpp"
#include "../include/WebotsSpecific/WebotsSensors.hpp"
#include "../include/Algorithms/Controller.hpp"
#include "../include/MotionController.hpp"
#include "../include/globals.hpp"
>>>>>>> Stashed changes

using namespace webots;

int main(int argc, char **argv) {


  #ifdef USE_WEBOTS
    Robot *robot = new Robot();
    int timeStep = (int)robot->getBasicTimeStep();
    WebotsSensors sensors = WebotsSensors(robot);
    WebotsMotors motors = WebotsMotors(robot);

  #else
    //  
    //hardware implementaiton
  #endif
    
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    motors.powerEngines(3.14f,3.14f);
    std::array<int16_t,4> readings = {0,0,0,0};
    readings = sensors.getDistanceReadings();
  while (robot->step(timeStep) != -1) {
    readings = sensors.getDistanceReadings();
=======
  MotionController  motionController = MotionController(motors);
  Controller controller = Controller(sensors, motionController);

  #ifdef USE_WEBOTS
      while(robot->step(8) != -1){
=======
  MotionController  motionController = MotionController(motors, sensors);
  Controller controller = Controller(sensors, motionController);

  #ifdef USE_WEBOTS
      while(robot->step(timeStep) != -1){
>>>>>>> Stashed changes

  #else
    //hardware implementaiton
    while(true){ //TODO: irl timestep
  #endif
    controller.step();  
  }

  
>>>>>>> Stashed changes


    std::cout << "Sensor1 Value: " << readings[0] << std::endl;
    std::cout << "Sensor2 Value: " << readings[1] << std::endl;
    std::cout << "Sensor3 Value: " << readings[2] << std::endl;
    std::cout << "Sensor4 Value: " << readings[3] << std::endl << std::endl;
    std::cout << "============ " << std::endl;

    if(readings[0] < 800 && readings [1] < 800 && readings[2] > 900 && readings[3] > 900){
      motors.powerEngines(4.14f,3.14f);
    }
    else{
          motors.powerEngines(3.14f,3.14f);
    }


    
  };

  delete robot;
  return 0;
}