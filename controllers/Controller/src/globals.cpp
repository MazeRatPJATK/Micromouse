#include "globals.hpp"

SpatialData spatialData = {0.0f, 0.0f, 0.0f, 0.0f};
float wheelCircumference = 13.50884f;
float distanceBetweenWheels = 9.2f; //this is effecitve wheelbase; acutal is 8.4 and before testing it was 9.2
int timeStep = 16;
bool rotating = false;

//Debug config [OPTIONS]
bool displayMap = true; //Set to true to display the maze map in the console.
bool debugMode[4] = {false, false, false, false}; //[0]: Speed, angle and command execution debug. [1]: Map and maze position debug. [2]: Target position debug. [3]: Sensor debug.

//Debug variables [DO NOT CHANGE]
float targetX_debug;
float targetY_debug;
float targetAngle_debug;