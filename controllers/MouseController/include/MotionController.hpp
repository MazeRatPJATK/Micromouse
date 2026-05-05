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
        float targetAngle;
        float targetVelocity;
        void adjustAngle();
        void adjustVelocity();
        IMotors& motors;

};