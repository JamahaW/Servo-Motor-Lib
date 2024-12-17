#pragma once

#include "servomotor/drivers/MotorDriver.hpp"


namespace servomotor {
    namespace drivers {
        class L293Driver : public MotorDriver<int16_t> {
        private:
            /// Пин скорости
            const Pin speed;

            /// Пин направления
            const Pin dir;

        public:
            explicit L293Driver(Pin speed, Pin dir) :
                speed(speed), dir(dir) {
                pinMode(speed, OUTPUT);
                pinMode(dir, OUTPUT);
            }

            void setPower(int16_t power) const override {
                power = constrain(power, -255, 255);
                analogWrite(this->speed, abs(power));
                digitalWrite(this->dir, power > 0);
            }
        };
    }
}