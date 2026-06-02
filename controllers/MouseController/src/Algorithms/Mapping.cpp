#include "../../include/Algorithms/Mapping.hpp"
#include "./../include/Algorithms/Map.hpp"
#include "../../include/globals.hpp"
#include <array>
#include "cmath"

#include "iostream"

void Mapping::step(){
    // std::cout << "*************************" << std::endl;
    std::cout << "Position [X]: " << spatialData.x << std::endl;
    std::cout << "Position [Y]: " << spatialData.y << std::endl;
    motionController.setTargetVelocity(2);
    if(spatialData.x > 50   && spatialData.x < 53){
         motionController.setTargetAngle(3.14);
    } 
    else{
        // motionController.setTargetAngle(0);
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

//    std::cout << "forward: " << leftForwardReading << std::endl;
//    std::cout << "leftAngled: " << leftAngledReading << std::endl;
//    std::cout << "rightAngled: " << rightAngledReading << std::endl;

<<<<<<< Updated upstream
=======
void Mapping::mapForwardCell(const std::array<int,2>& currentCell){

        std::array<float, 4> readings = sensors.getDistanceReadings();
        float rightForwardReading = readings[0];
        float leftForwardReading = readings[3];
        float rightAngledReading = readings[1];
        float leftAngledReading = readings[2];

        std::array<WallState,4> localWalls = {UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN};

        localWalls[3] = (leftAngledReading < WALL_DETECTION_THRESHOLD_MM)  ? PRESENT : ABSENT;
        localWalls[1] = (rightAngledReading < WALL_DETECTION_THRESHOLD_MM) ? PRESENT : ABSENT;

        if(leftForwardReading < WALL_DETECTION_THRESHOLD_MM){ 
            localWalls[2] = PRESENT ;
            localWalls[3] = UNKNOWN; 
            localWalls[1] = UNKNOWN;}
        else{
            localWalls[2] = ABSENT;
        }

        std::array<WallState, 4> worldWalls = localWalls; // start with copy
        rotateWallsToWorldFrame(worldWalls);

        int forwardSquareX = currentCell[0] + static_cast<int>(std::round(sin(spatialData.angle)));
        int forwardSquareY = currentCell[1] + static_cast<int>(std::round(cos(spatialData.angle)));
        map.putWalls(forwardSquareX ,forwardSquareY, worldWalls[0], worldWalls[1],worldWalls[2], worldWalls[3] );

        

        // std::cout << "Angle: " << spatialData.angle << "\n"
        //           << "Updating walls at X: " << forwardSquareX << " Y: " << forwardSquareY << "\n"
        //           << "N/E/S/W: " << (char)worldWalls[0] << (char)worldWalls[1] 
        //                          << (char)worldWalls[2] << (char)worldWalls[3] << std::endl;
}

void Mapping::rotateWallsToWorldFrame(std::array<WallState, 4>& walls) {
    float angle = spatialData.angle;
    int steps = 0;
    
    if (angle >= 4.70)      { steps = 3; } // ~270 deg
    else if (angle >= 3.13) { steps = 2; } // ~180 deg
    else if (angle >= 1.56) { steps = 1; } // ~90 deg

    if (steps == 0) return; 

    std::array<WallState, 4> originalWalls = walls;
    for (int i = 0; i < 4; i++) {
        walls[(i + steps) % 4] = originalWalls[i];
    }
>>>>>>> Stashed changes
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
