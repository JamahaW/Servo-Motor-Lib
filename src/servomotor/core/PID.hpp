#pragma once

namespace servomotor {
    namespace core {

        /// ПИД-Регулятор
        template<class T, class TimeType = uint32_t> class PID {
        public:
            using TimeMs = TimeType;

        private:

            const float kp;
            const float ki;
            const float kd;

            T last_error{0};
            T accumulated_error{0};
            TimeMs last_time{0};

        public:

            explicit PID(float kp, float ki, float kd) :
                kp{kp}, ki{ki}, kd{kd} {}

            /// Получить значение регулятора
            T calc(T error) {
                const TimeMs delta = getCurrentTime() - last_time;

                T d_term{0};

                if (delta > 0) {
                    this->accumulated_error += error * delta;
                    d_term = this->kd * (error - last_error) / delta;
                }

                last_error = error;
                last_time = getCurrentTime();

                return (error * kp) + (this->accumulated_error * ki) + d_term;
            }

        private:

            inline static TimeMs getCurrentTime() { return reinterpret_cast<TimeMs>(millis()); }
        };

    }
}