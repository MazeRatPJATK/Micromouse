//this is the data structure for describing the labyrinth
//exploration methods and robot control do not belong here
#pragma once
#include <cstdint>
#include <array>
#include "../globals.hpp"


//north east south west
// 00 - unknown, 01 - no wall,  10 - wall present, 11 -unsed (for now) (maybe unexplored tile?)
typedef uint8_t Tile;

enum WallState{
    PRESENT = 'p',
    ABSENT = 'a',
    UNKNOWN = 'u'
};

enum Direction{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Map{
    private:
        //bottom left of finish area
        uint8_t x1;
        uint8_t y1;

    //upper right of finish area
        uint8_t x2;
        uint8_t y2;

        std::array<std::array<Tile,13>,13> maze = {{0}};

        void putWall(int x, int y, Direction dir, WallState state) ;
        void printMaze() const;
    public:
        std::array<int,2>  translateCoordinates(int x, int y);
        void putWalls(int x, int y, WallState north, WallState east, WallState south, WallState west);
        void putOuterWalls();
        const std::array<WallState,4> getWallState(int x, int y) const;
        

};
