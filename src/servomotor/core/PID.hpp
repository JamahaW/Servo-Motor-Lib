#pragma once

#include "Arduino.h"
#include "servomotor/Types.hpp"
#include "Tools.hpp"


namespace servomotor {
    namespace core {

        template<class T> struct Range {
            T min, max;

            T clamp(T value) const {
                return constrain(value, this->min, this->max);
            }
        };

        /// настройки регулятора
        template<class Input, class Output> struct PIDSettings {
            float kp, ki, kd;
            Range<Input> input_range;
            Range<Output> output_range;
        };

        /// ПИД-Регулятор
        template<class Input, class Output> class PID {

        private:
            const PIDSettings<Input, Output> &settings;

            mutable Output last_error{0};
            mutable Output accumulated_error{0};
            mutable TimeMs last_time{0};

            Output target{0};

        public:

            /// Установить целевое значение
            void setTarget(Input new_target) { this->target = this->settings.input_range.clamp(new_target); }

            /// Установить диапазон выходных значений
            void setRange(Range<Output> range) { this->settings.output_range = range; }

            /// Получить целевое значение
            Output getTarget() { return this->target; }

            explicit PID(const PIDSettings<Input, Output> &settings) :
                settings{settings} {}


            /// Получить значение регулятора
            Output calc(Input input) {
                const Output error = target - static_cast<Output>(input);
                const TimeMs delta = core::getCurrentTime() - last_time;

                Output d_term{0};

                if (delta > 0) {
                    accumulated_error += error * delta;
                    d_term = settings.kd * (error - last_error) / delta;
                }

                last_error = error;
                last_time = core::getCurrentTime();

                return settings.output_range.clamp((error * settings.kp) + (accumulated_error * settings.ki) + d_term);
            }

        };

    }
}