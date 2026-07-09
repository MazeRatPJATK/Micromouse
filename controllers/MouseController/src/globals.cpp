#include "globals.hpp"

SpatialData spatialData = {0.0f, 0.0f, 0.0f, 0.0f};
float wheelCircumference = 13.50884f;
float distanceBetweenWheels = 9.2f; //this is effecitve wheelbase; acutal is 8.4 and before testing it was 9.2
int timeStep = 16;
bool rotating = false;
bool debugMode = false;
