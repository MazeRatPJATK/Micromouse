#pragma once
#include <cstdint>
#include "Map.hpp"
#include "../MotionController.hpp"
#include "./Interfaces/ISensors.hpp"
//this classes responsibility is to map explore the labytinth and put the data into the Map data structure
//this class also decides when to go back to to start square






class Mapping{
private:
        Map map;
        MotionController& motionController;
        ISensors& sensors;
        std::array<int, 2> previousGridCoordinates = {0,0};
        float previousAngle = 0.0f;

        void updateMap();
        void rotateWallsToWorldFrame(std::array<WallState,4>& walls);
        std::array<WallState, 4> getLocalWalls(const std::array<WallState, 4>& worldWalls);

        void mapForwardCell(const std::array<int,2>& currentCell);
        std::array<int,2> translateToGridCoordinate(float x, float y);

        void rightHandAlgorithm();

public:
        Mapping(Map& map, MotionController& motionController,ISensors& sensors);
        void step();


};


