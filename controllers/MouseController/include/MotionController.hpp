#pragma once
#include "./Interfaces/ISensors.hpp"
#include "./Interfaces/IMotors.hpp"
#include "./util/Util.hpp"
#include "SpatialData.hpp"



class MotionController{
    public:
        MotionController(IMotors& motors, ISensors& sensors);
        void setTargetAngle(float angle);
        void setTargetVelocity(float velocity);
        void step();
        void PID();

    private:
        float angleTolerance = 0.1f;
        float velocityTolerance = 0.1f;
        float targetAngle = 0.0f;
        float previousError = 0.0f;
        float targetVelocity = 0.0f;
        float currentVelocity = 0.0f;
        float velocityCorrection = 0.0f;
        float previousReadings[2] = {0.0f, 0.0f};
        void adjustAngle();
        void calculateCurrentVelocity();
        void adjustVelocity();
        ISensors& sensors;
        IMotors& motors;

};