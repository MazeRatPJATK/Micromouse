#include "../include/stmSpecific/StmSensors.hpp"
#include "../include/globals.hpp"


StmSensors::StmSensors(ADC_HandleTypeDef* hadc1,TIM_HandleTypeDef* htim2):hadc1(hadc1),htim2(htim2) {
    HAL_ADCEx_Calibration_Start(hadc1);
    HAL_ADC_Start_DMA(hadc1, (uint32_t*)buffer, bufferLength_);
    HAL_TIM_OC_Start(htim2,TIM_CHANNEL_4);
    HAL_TIM_OC_Start(htim2,TIM_CHANNEL_2);
    // HAL_ADC_Start(hadc1);

}

std::array<float, 4> StmSensors::getDistanceReadings() const {

        return {
            static_cast<float>(buffer[6] - buffer[1]),
            static_cast<float>(buffer[7] - buffer[2]),
            static_cast<float>(buffer[8] - buffer[3]),
            static_cast<float>(buffer[9] - buffer[4])
        };
}

    IMUData StmSensors::getIMUReadings() const {
        return IMUData();
    }


    std::array<float, 2>  StmSensors::getEncoderReadings() const {
        return {
            static_cast<float>(1),
            static_cast<float>(1)
        };
    }