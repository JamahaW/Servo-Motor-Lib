#pragma once

namespace servomotor {
    namespace core {

        template<class T> struct PIDSettings {
            float kp;
            float ki;
            float kd;
            T value_abs_max;

            T clamp(T value) const { return constrain(value, -this->value_abs_max, this->value_abs_max); }
        };

        /// ПИД-Регулятор
        template<class T, class TimeType = uint32_t> class PID {
        private:

            using TimeMs = TimeType;
            const PIDSettings<T> settings;

            T target{0};

            mutable T last_error{0};
            mutable T accumulated_error{0};
            mutable TimeMs last_time{0};

        public:

            explicit PID(const PIDSettings<T> settings) :
                settings{settings} {}

            /// Установить целевое значение регулятора
            void setTarget(T new_target) { this->target = this->settings.clamp(new_target); }

            /// Получить целевое значение регулятора
            T getTarget() { return this->target; }

            /// Получить значение регулятора
            T calc(T input) {
                const T error = this->target - input;
                const TimeMs delta = getCurrentTime() - last_time;

                T d_term{0};

                if (delta > 0) {
                    this->accumulated_error += error * delta;
                    d_term = this->settings.kd * (error - last_error) / delta;
                }

                last_error = error;
                last_time = getCurrentTime();

                return (error * this->settings.kp) + (this->accumulated_error * this->settings.ki) + d_term;
            }

        private:

            inline static TimeMs getCurrentTime() { return reinterpret_cast<TimeMs>(millis()); }


        };

    }
}