#pragma once
#include <array>



class IMotors{
private:

public:
        float leftPower;
        float rightPower;
        virtual ~IMotors() = default;
        virtual void powerEngines(float left, float right) = 0;
        virtual std::array<float, 2> getPower() const = 0;


};


