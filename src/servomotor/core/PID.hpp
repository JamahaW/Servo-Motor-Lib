#pragma once

namespace servomotor {
    namespace core {

        /// Интерфейс регулятора общего назначения
        template<class T> struct Regulator {
            /// Получить значение регулятора
            virtual T calc(T error) = 0;
        };

        template<class T> struct Proportional : Regulator<T> {
            const float kp;

            T calc(T error) override { return error * this->kp; }
        };

        template<class TimeType> struct TimeHelper {
            /// Единица измерения времени
            using TimeMs = TimeType;

            TimeMs last_update{0};

            /// Получить дельту времени
            TimeMs getDeltaMs() {
                TimeMs ret = getCurrentTime() - this->last_update;
                this->last_update = getCurrentTime();
                return ret;
            }

        private:
            inline static TimeMs getCurrentTime() { return reinterpret_cast<TimeMs>(millis()); }
        };

        /// Интегральный регулятор
        template<class T, class TimeType> struct Integral : Regulator<T> {

            const float ki;

            TimeHelper<TimeType> time_helper;
            T accumulated_error{0};

            explicit Integral(float ki) :
                ki{ki} {}

            T calc(T error) override {
                auto delta_ms = this->time_helper.getDeltaMs();

                if (delta_ms > 0) {
                    this->accumulated_error += error * delta_ms;
                }

                return this->accumulated_error * this->ki;
            }

        };

        /// Дифференциальный регулятор
        template<class T, class TimeType> struct Derivative : Regulator<T> {

            const float kd;

            TimeHelper<TimeType> time_helper;
            T last_error{0};

            explicit Derivative(float kd) :
                kd{kd} {}

            T calc(T error) override {
                auto delta_ms = this->time_helper.getDeltaMs();

                T ret{0};

                if (delta_ms > 0) {
                    ret = this->kd * (this->last_error - error) / delta_ms;
                }

                return ret;
            }

        };

        template<class T, class RegulatorA, class RegulatorB> struct PairRegulator : Regulator<T> {
            RegulatorA regulator_a;
            RegulatorB regulator_b;

            T calc(T error) override {
                return dynamic_cast<Regulator<T>>(this->regulator_b).calc(error) + dynamic_cast<Regulator<T>>(this->regulator_b).calc(error);
            }
        };

    }
}