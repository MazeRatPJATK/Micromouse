#pragma once
#include "./Interfaces/IMotors.hpp"
#include "SpatialData.hpp"



class MotionController{
    public:
        MotionController(IMotors& motors);
        void setTargetAngle(float angle);
        void setTargetVelocity(float velocity);
        void step();
        void PID();

    private:
        float angleTolerance = 1.0f;
        float targetAngle = 0.0f;
        float previousError = 0.0f;
        float targetVelocity = 0.0f;
        void adjustAngle();
        void adjustVelocity();
        IMotors& motors;

};