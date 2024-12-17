#pragma once

#include "Arduino.h"
#include "servomotor/Types.hpp"
#include "servomotor/core/Tools.hpp"


namespace servomotor {
    namespace core {

        /// настройки регулятора
        template<class Input, class Output> struct PIDSettings {
            float kp, ki, kd;
            Range<Input> input_range;
            Range<Output> output_range;
            Range<Output> integral_range;

            Output calc(Output p, Output i, Output d) const {
                return output_range.clamp((p * kp) + (i * ki) + (d * kd));
            }
        };

        /// ПИД-Регулятор
        template<class Input, class Output> class PID {

        private:
            const PIDSettings<Input, Output> &settings;

            Differentiator<Output> differentiator{};
            Integrator<Output> integrator;
            Chronometer chronometer{};

            Output target{0};

        public:

            explicit PID(const PIDSettings<Input, Output> &settings) :
                settings{settings}, integrator(settings.integral_range) {}

            /// Установить целевое значение
            void setTarget(Input new_target) { this->target = this->settings.input_range.clamp(new_target); }

            /// Установить диапазон выходных значений
            void setRange(Range<Output> range) { this->settings.output_range = range; }

            /// Получить целевое значение
            Output getTarget() { return this->target; }

            /// Получить значение регулятора
            Output calc(Input input) {
                const Output error = target - static_cast<Output>(input);
                const TimeMs dt = chronometer.getDeltaTime();
                return settings.calc(error, integrator.calc(error, dt), differentiator.calc(error, dt));
            }
        };
    }
}