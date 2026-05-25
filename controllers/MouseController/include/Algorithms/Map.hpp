//this is the data structure for describing the labyrinth
//exploration methods and robot control do not belong here
#pragma once
#include <cstdint>
#include <array>


//north east south west
// 00 - unknown, 01 - no wall,  10 - wall present, 11 -unsed (for now) (maybe unexplored tile?)
typedef uint8_t Tile;

enum WallState{
    PRESENT = 'p',
    ABSENT = 'a',
    UNKNOWN = 'u'
};

class Map{
    private:
        //bottom left of finish area
        uint8_t x1;
        uint8_t y1;

    //upper right of finish area
        uint8_t x2;
        uint8_t y2;

        Tile maze[16][16] = {{0}};
    public:
        std::array<int,2>  translateCoordinates(int x, int y);
        void putWalls(int x, int y, WallState north, WallState east, WallState south, WallState west);
        

};
