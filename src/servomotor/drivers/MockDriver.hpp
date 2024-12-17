#pragma once

#include "servomotor/drivers/MotorDriver.hpp"


namespace servomotor {
    namespace drivers {
        using MockPower = int8_t;

        /// Заглушка драйвера
        class MockDriver : public MotorDriver<MockPower> {

            /// Заданная мощность
            mutable MockPower power_set{0};

        public:
            void setPower(MockPower power) const override { this->power_set = power; }
        };
    }
}