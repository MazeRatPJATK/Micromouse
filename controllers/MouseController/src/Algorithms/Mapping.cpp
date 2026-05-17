#include "../../include/Algorithms/Mapping.hpp"
#include "./../include/Algorithms/Map.hpp"
#include "../../include/globals.hpp"
#include <array>
#include "cmath"

#include "iostream"

void Mapping::step(){
    motionController.setTargetVelocity(2);
    if(spatialData.x > 71   && spatialData.x < 73){
         motionController.setTargetAngle(3.14);
    } 
    else{
        motionController.setTargetAngle(0);
    }
    updateMap();
    rightHandAlgorithm();
}

void Mapping::rightHandAlgorithm(){
   std::array<float, 4> readings = sensors.getDistanceReadings();

   float rightForwardReading = readings[0];
   float leftForwardReading = readings[3];
   float rightAngledReading = readings[1];
   float leftAngledReading = readings[2];

//    std::cout << "leftForward: " << leftForwardReading << std::endl;
//    std::cout << "leftAngled: " << leftAngledReading << std::endl;
//    std::cout << "rightAngled: " << rightAngledReading << std::endl;

   if(rightForwardReading > 990 && leftForwardReading > 990){motionController.setTargetVelocity(2);}
//    else if(){}


}


void Mapping::updateMap(){

    std::array<float, 4> readings = sensors.getDistanceReadings();
    float rightForwardReading = readings[0];
    float leftForwardReading = readings[3];
    float rightAngledReading = readings[1];
    float leftAngledReading = readings[2];

    std::array<int,2> currentGridCoordinates = {
        static_cast<int>((spatialData.x )/18),
        static_cast<int>((spatialData.y )/18)
    };

    if(previousGridCoordinates != currentGridCoordinates){
        WallState back = ABSENT;
        WallState left = ABSENT;
        WallState right = ABSENT;
        if(leftAngledReading < 900){ left = PRESENT;};
        if(rightAngledReading < 900){ right = PRESENT;};
        if(leftForwardReading < 900){ back = PRESENT;left = UNKNOWN; right = UNKNOWN;}


        // map.putWalls((x+1)*cos(spatialData.angle),(y+1)*sin(spatialData.angle),lef)
    }
    previousGridCoordinates  = currentGridCoordinates;

   std::cout << "forward: " << leftForwardReading << std::endl;
   std::cout << "leftAngled: " << leftAngledReading << std::endl;
   std::cout << "rightAngled: " << rightAngledReading << std::endl;

}

Mapping::Mapping(Map& map, MotionController& motionController, ISensors& sensors)
    :map(map),
     motionController(motionController),
     sensors(sensors){

}

std::array<int,2> Mapping::translateToGridCoordinate(float x, float y){
    return {
        static_cast<int>(x/18),
        static_cast<int>(y/18)
    };

};
