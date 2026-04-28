
#include "../../include/Algorithms/Map.hpp"

void Map::putWalls(int x, int y, WallState north, WallState east, WallState south, WallState west){

    // 00 - unknown, 01 - no wall,  10 - wall present, 11 -unsed (for now) (maybe unexplored tile?)

    uint8_t tile  = maze[x][y];
    if(north == PRESENT){
        tile = tile || 0b10000000;
    }
    else if (north == ABSENT){
        tile = tile || 0b01000000;
    }

    if(east == PRESENT){
        tile = tile || 0b00100000;
    }
    else if (east == ABSENT){
        tile = tile || 0b00010000;
    }

    if(south== PRESENT){
        tile = tile || 0b00001000;
    }
    else if (south == ABSENT){
        tile =  tile || 0b00000100;
    }

    if(west == PRESENT){
        tile = tile || 0b00000010;
    }
    else if (west == ABSENT){
        tile = tile || 0b000000001;
    }

    maze[x][y] = tile;
}

