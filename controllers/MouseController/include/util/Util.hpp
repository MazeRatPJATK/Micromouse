#pragma once
#include <functional>
float normalizeAngle(float a);
float snapToRightAngle(float angle);

struct Command{
    float targetVelocity = 0;
    float targetAngle = 0;
    float targetX = 0;;
    float targetY = 0;

    std::function<void()> onComplete = nullptr;  
};
