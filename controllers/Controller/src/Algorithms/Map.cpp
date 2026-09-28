
#include "../../include/Algorithms/Map.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

constexpr float GRID_CELL_SIZE = 18.0f;

void Map::putWall(int x, int y, Direction dir, WallState state) {
    if (state == UNKNOWN){
        return;
    }
    else if (x < 0 || x > 12 || y < 0 || y > 12) {
        return;
    }

    uint8_t& tile = maze[x][y];
    uint8_t presentBit, absentBit;

    switch (dir) {
        case NORTH: presentBit = 0b10000000; absentBit = 0b01000000; break;
        case EAST:  presentBit = 0b00100000; absentBit = 0b00010000; break;
        case SOUTH: presentBit = 0b00001000; absentBit = 0b00000100; break;
        case WEST:  presentBit = 0b00000010; absentBit = 0b00000001; break;
    }

    tile &= ~(presentBit | absentBit);
    tile |= (state == PRESENT) ? presentBit : absentBit;
}

void Map::putWalls(int x, int y, WallState north, WallState east, WallState south, WallState west) {
    x += 0;
    y += 0;

    putWall(x,y,NORTH,north);
    putWall(x,y,EAST,east);
    putWall(x,y,SOUTH,south);
    putWall(x,y,WEST,west);

    if (y < 12)         putWall(x,   y+1, SOUTH, north); 
    if (x < 12)         putWall(x+1, y,   WEST,  east);
    if (y > 0)          putWall(x,   y-1, NORTH, south);
    if (x > 0)          putWall(x-1, y,   EAST,  west);

    printMaze();
}


const std::array<WallState, 4> Map::getWallState(int x, int y) const {
    x += 0;
    y += 0;
    Tile t = maze[x][y];
    std::array<WallState, 4> state = {};

    if      (t & 0b10000000) state[0] = PRESENT;
    else if (t & 0b01000000) state[0] = ABSENT;
    else                     state[0] = UNKNOWN;

    if      (t & 0b00100000) state[1] = PRESENT;
    else if (t & 0b00010000) state[1] = ABSENT;
    else                     state[1] = UNKNOWN;

    if      (t & 0b00001000) state[2] = PRESENT;
    else if (t & 0b00000100) state[2] = ABSENT;
    else                     state[2] = UNKNOWN;

    if      (t & 0b00000010) state[3] = PRESENT;
    else if (t & 0b00000001) state[3] = ABSENT;
    else                     state[3] = UNKNOWN;

    return state;
}

//Set the outer maze walls to [PRESENT].
void Map::putOuterWalls() {
    // Iterate rows (y) from high to low (north is up)
    for (int y = 12; y >= 0; y--) {
        //Top walls
        if (y == 12) {
            for (int x = 0; x < 13; x++) {
                putWall(x, y, NORTH, PRESENT);
            }
        }
        
        //Outer side walls of the row
        putWall(0, y, WEST, PRESENT);
        putWall(12, y, EAST, PRESENT);

        //Bottom walls
        if (y == 0) {
            for (int x = 0; x < 13; x++) {
                putWall(x, y, SOUTH, PRESENT);
            }
        }
    }

    // bottom row

    //Debug statement:
    // if (!robotNotFound) {
    // }
    
}

void Map::printMaze() const {
    #ifdef USE_WEBOTS
    if (displayMap) {
        bool robotNotFound = true;
        // iterate y from high to low so north is up
        for (int y = 12; y >= 0; y--) {
            // top walls row
            for (int x = 0; x < 13; x++) {
                const auto walls = getWallState(x - 0, y - 0);
                WallState north = walls[0];
                std::cout << "+";
                if      (north == PRESENT) std::cout << "———";
                else if (north == ABSENT)  std::cout << "   ";
                else                       std::cout << "···"; // unknown
            }
            std::cout << "+\n";
    
            // side walls + cell row
            for (int x = 0; x < 13; x++) {
                const auto walls = getWallState(x - 0, y - 0);
                WallState west = walls[3];
                if      (west == PRESENT) std::cout << "|";
                else if (west == ABSENT)  std::cout << " ";
                else                      std::cout << "?";
    
                //Print "X" in the cell that the MazeBot occupies.
                if (std::round((spatialData.x )/GRID_CELL_SIZE) == x && std::round((spatialData.y )/GRID_CELL_SIZE) == y) {
                    std::cout << " X "; // cell interior
                    // robotNotFound = false; //debug variable
                }
                else if (targetX_debug == x && targetY_debug == y) {
                    std::cout << " T "; // cell interior
                }
                else {
                    std::cout << "   "; // cell interior
                    // std::cout << "" << x << " " << y; // cell interior for debug
                }
            }
            // rightmost east wall
            const auto rightWalls = getWallState(13 - 1, y - 0);
            WallState east = rightWalls[1];
            std::cout << (east == PRESENT ? "|" : " ") << "\n";
        }
    
        // bottom row
        for (int x = 0; x < 13; x++) {
            const auto walls = getWallState(x - 0, 0);
            WallState south = walls[2];
            std::cout << "+";
            if      (south == PRESENT) std::cout << "———";
            else if (south == ABSENT)  std::cout << "   ";
            else                       std::cout << "···";
        }

        std::cout << "+\n";
    
        //Debug checkpoint
        if (debugMode[1]) {
            std::cout << "Current position (x, y): " << std::round((spatialData.x)/GRID_CELL_SIZE) << ", " << std::round((spatialData.y)/GRID_CELL_SIZE) << std::endl;
            if (!robotNotFound) {
                std::cout << "Robot was found.\n";
            }
        } 
        else if (debugMode[2]) {
            std::cout << "[Current command targets] X: " << targetX_debug << " Y: " << targetY_debug << " Angle: " << targetAngle_debug << "\n";
        }
        else {
            std::cout << ".\n";
        }
    }
    #endif
}