
#pragma once

#include "../Interfaces/IMotors.hpp"


class StmMotors : public IMotors {
public:
    StmMotors();
    void powerEngines(float left, float right) override;
    std::array<float, 2> getPower() const override;     

private:

};