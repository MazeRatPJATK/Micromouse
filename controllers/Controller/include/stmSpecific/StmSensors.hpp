#pragma once

#include "../Interfaces/ISensors.hpp"
#include <array>
#include "stm32f1xx_hal.h" 



class StmSensors : public ISensors {
public:
    StmSensors(ADC_HandleTypeDef* hadc1,TIM_HandleTypeDef* htim2);

    std::array<float, 4> getDistanceReadings() const override;

    IMUData getIMUReadings() const override;
    std::array<float, 2>  getEncoderReadings() const override;

private:
    ADC_HandleTypeDef* hadc1;
    TIM_HandleTypeDef* htim2;
    static constexpr size_t bufferLength_ = 10;
    uint16_t buffer[bufferLength_] = {0}; //4 sensors, on and off readings, times 16

};