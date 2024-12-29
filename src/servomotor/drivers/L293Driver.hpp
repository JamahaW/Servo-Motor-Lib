#pragma once

#include "servomotor/drivers/MotorDriver.hpp"
#include "Arduino.h"


namespace servomotor {
    namespace drivers {
        class L293Driver : public MotorDriver<int16_t> {
        private:
            /// Пин скорости
            const Pin speed;

            /// Пин направления
            const Pin dir;

            const uint8_t is_dir_reversed;

        public:
            explicit L293Driver(Pin speed, Pin dir, Direction move_dir) :
                speed(speed), dir(dir), is_dir_reversed(static_cast<uint8_t>(move_dir)) {
                pinMode(speed, OUTPUT);
                pinMode(dir, OUTPUT);
            }

            void setPower(int16_t power) const override {
                power = constrain(power, -255, 255);
                analogWrite(this->speed, abs(power));
                digitalWrite(this->dir, (power > 0) ^ this->is_dir_reversed);
            }
        };
    }
}