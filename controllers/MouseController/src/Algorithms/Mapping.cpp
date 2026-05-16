#include "../../include/Algorithms/Mapping.hpp"
#include "./../include/Algorithms/Map.hpp"
#include "../../include/globals.hpp"

void Mapping::step(){
    motionController.setTargetVelocity(2);
    if(spatialData.x > 71   && spatialData.x < 73){
         motionController.setTargetAngle(1.57);
    } 
    else{
        motionController.setTargetAngle(0);
    }
}

Mapping::Mapping(Map& map, MotionController& motionController):map(map), motionController(motionController){

}