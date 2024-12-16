#pragma once

#include "servomotor/ServoMotor.hpp"
#include "servomotor/core/PID.hpp"


namespace servomotor {
    class MockServoMotor : public ServoMotor<> {
    private:
        Position real_position{0};
        Speed real_speed{0};


    public:
        Position getPosition() override { return this->real_position; }

        Speed getSpeed() override { return this->real_speed; }

        void reset(char flags) override {
            this->real_speed = 0;
            this->real_position = 0;
        }

    protected:
        void updateRegulator() override {
            this->real_position += getSpeed();
        }
    };
}