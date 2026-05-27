#include "../../include/Algorithms/Mapping.hpp"
#include "./../include/Algorithms/Map.hpp"
#include "../../include/globals.hpp"
#include <array>
#include "cmath"


#include "iostream"


constexpr float GRID_CELL_SIZE = 18.0f;
constexpr float QUADRANT_ANGLE_RAD = 1.56f; // ~90 degrees in radians
constexpr float WALL_DETECTION_THRESHOLD_MM = 900.0f;


bool flag = false;
void Mapping::step(){
    motionController.setTargetVelocity(4);
    
    // if(flag == false){
    //     motionController.setTargetAngle(1.59);
    // }
    // if(spatialData.angle > 1.57 ){
    //     flag = true;
    //     motionController.setTargetAngle(0);
    // }







    if(spatialData.y > 36   && spatialData.y < 38 && spatialData.x >= -1 ){
         motionController.setTargetAngle(-1.57);
    } 
    else if(spatialData.y > 34   && spatialData.y < 38 && spatialData.x < -17.5 && spatialData.x > -19){
         motionController.setTargetAngle(0);
         
    } 
    updateMap();
    // rightHandAlgorithm();
}

void Mapping::rightHandAlgorithm(){
   std::array<float, 4> readings = sensors.getDistanceReadings();

   float rightForwardReading = readings[0];
   float leftForwardReading = readings[3];
   float rightAngledReading = readings[1];
   float leftAngledReading = readings[2];


   if(rightForwardReading > 990 && leftForwardReading > 990){motionController.setTargetVelocity(2);}
//    else if(){}


}


void Mapping::updateMap(){

    std::array<int,2> currentGridCoordinates = {
        static_cast<int>(std::round((spatialData.x )/GRID_CELL_SIZE)),
        static_cast<int>(std::round((spatialData.y )/GRID_CELL_SIZE))
    };

    float distanceFromCenterX = currentGridCoordinates[0]*18 - spatialData.x;
    float distanceFromCenterY = currentGridCoordinates[1]*18 - spatialData.y;


    bool closeToEdge = (distanceFromCenterX < 0.0f) || (distanceFromCenterY <  0.0f);
    
    bool movedToNewCell = (previousGridCoordinates != currentGridCoordinates);
    bool turned90Deg    = (std::abs(spatialData.angle - previousAngle) > QUADRANT_ANGLE_RAD);

    bool triggerForwardMapping = movedToNewCell && closeToEdge; 
    bool triggerTurnMapping    = turned90Deg && closeToEdge;
    
    if (triggerForwardMapping || triggerTurnMapping) {
        mapForwardCell(currentGridCoordinates);
        previousAngle = spatialData.angle;
        previousGridCoordinates = currentGridCoordinates;
    }

    
}

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

        

        std::cout << "Angle: " << spatialData.angle << "\n"
                  << "Updating walls at X: " << forwardSquareX << " Y: " << forwardSquareY << "\n"
                  << "N/E/S/W: " << (char)worldWalls[0] << (char)worldWalls[1] 
                                 << (char)worldWalls[2] << (char)worldWalls[3] << std::endl;
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
