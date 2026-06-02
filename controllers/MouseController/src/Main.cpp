//webots
#include <webots/Robot.hpp>
#include <webots/DistanceSensor.hpp>

//std
#include <iostream>
#include <array>

//our own
#include "../include/WebotsSpecific/WebotsMotors.hpp"
#include "../include/WebotsSpecific/WebotsSensors.hpp"
#include "../include/Algorithms/Controller.hpp"
#include "../include/MotionController.hpp"

using namespace webots;

int main(int argc, char **argv) {


  #ifdef USE_WEBOTS
    Robot *robot = new Robot();
    WebotsSensors sensors = WebotsSensors(robot);
    WebotsMotors motors = WebotsMotors(robot);

  #else
    //  
    //hardware implementaiton
  #endif
    
  MotionController  motionController = MotionController(motors, sensors);
  Controller controller = Controller(sensors, motionController);

  #ifdef USE_WEBOTS
      while(robot->step(16) != -1){

  #else
    //hardware implementaiton
    while(true){ //TODO: irl timestep
  #endif
    controller.step();  
  }

  



  delete robot;
  return 0;
}