#pragma once

#include "../Interfaces/ISensors.hpp"
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Robot.hpp>
#include <array>

class WebotsSensors : public ISensors {
public:
    WebotsSensors(webots::Robot* robot);

    std::array<float, 4> getDistanceReadings() const override;

    IMUData getIMUReadings() const override;
    std::array<float, 2>  getEncoderReadings() const override;

private:
    std::array<webots::DistanceSensor*, 4> distanceSensors;
    std::array<webots::PositionSensor*, 2> positionSensors;
};