#include "../../include/Algorithms/Mapping.hpp"
#include "./../include/Algorithms/Map.hpp"
#include "../../include/globals.hpp"
#include <array>
#include "cmath"
#include "../../include/util/Util.hpp"

#include "iostream"


constexpr float GRID_CELL_SIZE = 18.0f;
constexpr float QUADRANT_ANGLE_RAD = 1.57f; // ~90 degrees in radians
constexpr float WALL_DETECTION_THRESHOLD_MM = 900.0f;


bool first = true;
bool exploreStartingTile = true;
void Mapping::step(){
    // motionController.setTargetVelocity(4);
    
    // std::cout << "X: " << spatialData.x << "\n"
            //   << "Y: " << spatialData.y << std::endl;
    // if(spatialData.y > 36   && spatialData.y < 38 && spatialData.x >= -1 ){
        //  motionController.setTargetAngle(-1.57);
    // } 
    // else if(spatialData.y > 34   && spatialData.y < 38 && spatialData.x < -17.5 && spatialData.x > -19){
        //  motionController.setTargetAngle(0);
        //  
    // } 
    // else if(spatialData.y > 89   && spatialData.y < 90 && spatialData.x < -17.5 && spatialData.x > -19){
        //  motionController.setTargetAngle(1.57);
        //  
    // } 
    // else if(spatialData.y > 88   && spatialData.y < 89 && spatialData.x > 17.5 && spatialData.x < 18){
        //  motionController.setTargetAngle(0);
        //  
    // } 
    // else if(spatialData.y > 88   && spatialData.y < 89 && spatialData.x > 17.5 && spatialData.x < 18){
        //  motionController.setTargetAngle(0);
        //  
    // } 


    if(exploreStartingTile){  
    enqueCommandCallback({2,1.57,0,0,nullptr});
    enqueCommandCallback({2,3.14,0,0,nullptr});
    enqueCommandCallback({2,-1.57,0,0,nullptr});
    enqueCommandCallback({4, 0, 0, 0, [this]() { this->rightHandAlgorithm(); }}); 
    exploreStartingTile = false;
    }


    updateMap();

}

void Mapping::rightHandAlgorithm(){
    std::array<int,2> currentGridCoordinates = {
        static_cast<int>(std::round((spatialData.x) / GRID_CELL_SIZE)),
        static_cast<int>(std::round((spatialData.y) / GRID_CELL_SIZE))
    };

    std::array<WallState, 4> walls = map.getWallState(
        currentGridCoordinates[0], currentGridCoordinates[1]
    );
    walls = getLocalWalls(walls);

    bool wallInFront = (walls[0] == PRESENT);
    bool wallOnRight = (walls[1] == PRESENT);
    bool wallOnLeft  = (walls[3] == PRESENT);
    // std::cout << "f/r/l: "  << (char)walls[0] << (char)walls[1] << (char)walls[3] << std::endl;


    if(!wallOnRight){
        float targetAngle = snapToRightAngle(spatialData.angle) + 1.57f;
        enqueCommandCallback({
    2,
    targetAngle,
    0,
    0,
    [this, targetAngle]()
    {
        auto [x, y] = getNextCellTarget();

        enqueCommandCallback({
            2,
            targetAngle,
            x,
            y,
            [this]() { this->rightHandAlgorithm(); }
        });
    }
    });
    }

    else{
                auto [x, y] = getNextCellTarget();

               enqueCommandCallback({2, spatialData.angle, x, y, [this]() { this->rightHandAlgorithm(); }});
    } 


}


std::pair<float, float> Mapping::getNextCellTarget() {
    float angle = spatialData.angle;
    float x = spatialData.x;
    float y = spatialData.y;

        std::array<int,2> currentCell = {
        static_cast<int>(std::round((spatialData.x )/GRID_CELL_SIZE)),
        static_cast<int>(std::round((spatialData.y )/GRID_CELL_SIZE))
    };

    int forwardSquareX = currentCell[0] + static_cast<int>(std::round(sin(spatialData.angle)));
    int forwardSquareY = currentCell[1] + static_cast<int>(std::round(cos(spatialData.angle)));

    return {forwardSquareX*GRID_CELL_SIZE, forwardSquareY*GRID_CELL_SIZE};
}
 
void Mapping::updateMap(){
    std::array<int,2> currentGridCoordinates = {
        static_cast<int>(std::round((spatialData.x )/GRID_CELL_SIZE)),
        static_cast<int>(std::round((spatialData.y )/GRID_CELL_SIZE))
    };

    float distanceFromCenterX = currentGridCoordinates[0]*18 - spatialData.x;
    float distanceFromCenterY = currentGridCoordinates[1]*18 - spatialData.y;


    bool closeToEdge = false;
 
    float snappedAngle = snapToRightAngle(spatialData.angle);

    const float eps = 0.001f;
    if (std::abs(snappedAngle) < eps ||  std::abs(std::abs(snappedAngle) - M_PI) < eps){  
        closeToEdge = ((distanceFromCenterY <  1.0f) && (distanceFromCenterY >  -1.0f));
    }
    else if (std::abs(std::abs(snappedAngle) - M_PI / 2.0f) < eps){   
         closeToEdge = ((distanceFromCenterX > -1.0f)  && (distanceFromCenterX < 1.0f));
    }   




    bool movedToNewCell = (previousGridCoordinates != currentGridCoordinates);
    bool turned90Deg    = (std::abs(spatialData.angle - previousAngle) > (QUADRANT_ANGLE_RAD - 0.1f));

    bool triggerForwardMapping = movedToNewCell && closeToEdge; 
    bool triggerTurnMapping    = turned90Deg && closeToEdge;
    
    // if(first){
    //     mapForwardCell(currentGridCoordinates);
    //     first = false;
    // }


    if ( triggerTurnMapping) {

        mapForwardCell(currentGridCoordinates);
        previousAngle = snapToRightAngle(spatialData.angle);
    }
    else if(triggerForwardMapping){

        mapForwardCell(currentGridCoordinates);

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

        std::array<WallState, 4> worldWalls = localWalls; 
        rotateWallsToWorldFrame(worldWalls);

        int forwardSquareX = currentCell[0] + static_cast<int>(std::round(sin(spatialData.angle)));
        int forwardSquareY = currentCell[1] + static_cast<int>(std::round(cos(spatialData.angle)));
        map.putWalls(forwardSquareX ,forwardSquareY, worldWalls[0], worldWalls[1],worldWalls[2], worldWalls[3] );

        

}

void Mapping::rotateWallsToWorldFrame(std::array<WallState, 4>& walls) {
    float angle = snapToRightAngle(spatialData.angle);
    int steps = 0;
    float epsilon = 0.01;
    
    if(angle + M_PI          < epsilon) steps = 2;   
    else if(angle + (M_PI/2) < epsilon) steps = 3;
    else if(angle            < epsilon) steps = 0;
    else if(angle - (M_PI/2) < epsilon) steps = 1;
    else if(angle - M_PI     < epsilon) steps = 2;

    if (steps == 0) return; 

    std::array<WallState, 4> originalWalls = walls;
    for (int i = 0; i < 4; i++) {
        walls[(i + steps) % 4] = originalWalls[i];
    }
}

std::array<WallState, 4> Mapping::getLocalWalls(const std::array<WallState, 4>& worldWalls) {
    float angle = snapToRightAngle(spatialData.angle);
    int steps = 0;
    float epsilon = 0.01;

    if      (angle + M_PI      < epsilon) steps = 2;
    else if (angle + (M_PI/2)  < epsilon) steps = 3;
    else if (angle             < epsilon) steps = 0;
    else if (angle - (M_PI/2)  < epsilon) steps = 1;
    else if (angle - M_PI      < epsilon) steps = 2;

    if (steps == 0) return worldWalls;

    std::array<WallState, 4> localWalls;
    int reverseSteps = (4 - steps) % 4;

    for (int i = 0; i < 4; i++) {
        localWalls[(i + reverseSteps) % 4] = worldWalls[i];
    }

    return localWalls; 
}

Mapping::Mapping(Map& map, MotionController& motionController, ISensors& sensors, std::function<void(Command)> enqueCommandCallback)
    :map(map),
     motionController(motionController),
     sensors(sensors),
     enqueCommandCallback(enqueCommandCallback){

}

std::array<int,2> Mapping::translateToGridCoordinate(float x, float y){
    return {
        static_cast<int>(x/18),
        static_cast<int>(y/18)
    };

};


