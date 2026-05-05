#pragma once
#include <cstdint>
#include "Map.hpp"
//this classes responsibility is to map explore the labytinth and put the data into the Map data structure
//this class also decides when to go back to to start square






class Mapping{
private:
        Map map;

public:
        Mapping(Map& map);
        void step();


};


