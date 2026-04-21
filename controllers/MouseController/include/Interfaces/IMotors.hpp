#pragma once
#include <webots/Motor.hpp>



class IMotors{
private:
public:
        virtual ~IMotors() = default;
        virtual void powerEngines(float left, float right) = 0;


};


