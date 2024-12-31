#pragma once

#include "Arduino.h"
#include "servomotor/Types.hpp"
#include "servomotor/core/Tools.hpp"


namespace servomotor {
    namespace core {


        /// ПИД-Регулятор
        class PID {

        public:
            float kp, ki, kd;

            Differentiator<Position> differentiator{};
            Integrator<Position> integrator{};

            Position target{0};

            explicit PID(float p, float i, float d) :
                kp{p}, ki{i}, kd{d} {}

            /// Получить значение регулятора
            Position calc(Position input, TimeMs dt) {
                Position error = target - input;

                return Position((error * kp) + (integrator.calc(error, dt) * ki) + (differentiator.calc(error, dt) * kd));
            }
        };
    }
}