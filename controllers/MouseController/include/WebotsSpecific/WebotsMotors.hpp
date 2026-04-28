
#pragma once

#include "../Interfaces/IMotors.hpp"
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

class WebotsMotors : public IMotors {
public:
    WebotsMotors(webots::Robot* robot);
    void powerEngines(float left, float right) override;

private:
    webots::Motor* leftMotor;
    webots::Motor* rightMotor;
};