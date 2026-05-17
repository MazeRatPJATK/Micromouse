#pragma once
#include <array>
#include <cstdint>

struct IMUData {
    double roll, pitch, yaw;
};

struct EncoderData {
    int32_t left;
    int32_t right;
};

class ISensors {
public:
    virtual ~ISensors() = default;

    virtual std::array<float, 4> getDistanceReadings() const = 0;
    virtual IMUData getIMUReadings() const = 0;
    virtual std::array<float, 2>  getEncoderReadings() const = 0;
};