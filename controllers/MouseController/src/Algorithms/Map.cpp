
#include "../../include/Algorithms/Map.hpp"
#include <iostream>

void Map::putWall(int x, int y, Direction dir, WallState state) {
    if (state == UNKNOWN) return;

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
    x += 6;
    y += 6;

    putWall(x,y,NORTH,north);
    putWall(x,y,EAST,east);
    putWall(x,y,SOUTH,south);
    putWall(x,y,WEST,west);

    if (y > 0)          putWall(x,   y+1, SOUTH, north); 
    if (x < 15)         putWall(x+1, y,   WEST,  east);
    if (y < 15)         putWall(x,   y-1, NORTH, south);
    if (x > 0)          putWall(x-1, y,   EAST,  west);

    // printMaze();
}


const std::array<WallState, 4> Map::getWallState(int x, int y) const {
    x += 6;
    y += 6;
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



void Map::printMaze() const {
    // iterate y from high to low so north is up
    for (int y = 15; y >= 0; y--) {
        // top walls row
        for (int x = 0; x < 16; x++) {
            const auto walls = getWallState(x - 6, y - 6);
            WallState north = walls[0];
            std::cout << "+";
            if      (north == PRESENT) std::cout << "———";
            else if (north == ABSENT)  std::cout << "   ";
            else                       std::cout << "···"; // unknown
        }
        std::cout << "+\n";

        // side walls + cell row
        for (int x = 0; x < 16; x++) {
            const auto walls = getWallState(x - 6, y - 6);
            WallState west = walls[3];
            if      (west == PRESENT) std::cout << "|";
            else if (west == ABSENT)  std::cout << " ";
            else                      std::cout << "?";
            std::cout << "   "; // cell interior
        }
        // rightmost east wall
        const auto rightWalls = getWallState(15 - 6, y - 6);
        WallState east = rightWalls[1];
        std::cout << (east == PRESENT ? "|" : " ") << "\n";
    }

    // bottom row
    for (int x = 0; x < 16; x++) {
        const auto walls = getWallState(x - 6, 0 - 6);
        WallState south = walls[2];
        std::cout << "+";
        if      (south == PRESENT) std::cout << "---";
        else if (south == ABSENT)  std::cout << "   ";
        else                       std::cout << "···";
    }
    std::cout << "+\n";
}