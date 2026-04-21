#include "../include/Interfaces/ISensors.hpp"
#include <webots/DistanceSensor.hpp>
#include <webots/Robot.hpp>

class WebotsSensors : public ISensors {
public:
    WebotsSensors(webots::Robot* robot) {

            distanceSensors[0] = robot->getDistanceSensor("s1");
            distanceSensors[1] = robot->getDistanceSensor("s2");
            distanceSensors[2] = robot->getDistanceSensor("s3");
            distanceSensors[3] = robot->getDistanceSensor("s4" );

            distanceSensors[0]->enable(32);
            distanceSensors[1]->enable(32);
            distanceSensors[2]->enable(32);
            distanceSensors[3]->enable(32);
        
    }

    std::array<int16_t, 4> getDistanceReadings() const override {
        return {
            static_cast<int16_t>(distanceSensors[0]->getValue()),
            static_cast<int16_t>(distanceSensors[1]->getValue()),
            static_cast<int16_t>(distanceSensors[2]->getValue()),
            static_cast<int16_t>(distanceSensors[3]->getValue())
        };
    }



    IMUData getIMUReadings() const override{ return IMUData();}
    EncoderData getEncoderReadings() const  override{ return EncoderData();}
private:
    std::array<webots::DistanceSensor*, 4> distanceSensors; // Only exists in Simulation
};