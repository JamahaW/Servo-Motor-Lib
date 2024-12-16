#pragma once

#include "servomotor/ServoMotor.hpp"
#include "servomotor/core/PID.hpp"


namespace servomotor {
    class MockServoMotor : public ServoMotor {
    private:
        Position real_position{0};
        Speed real_speed{0};


    public:
        explicit MockServoMotor(Config<ServoMotor::Position, ServoMotor::Speed> &config) :
            ServoMotor(config) {}

        Position getPosition() override { return this->real_position; }

        Speed getSpeed() override { return this->real_speed; }
    };
}