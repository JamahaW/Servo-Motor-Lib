#pragma once

#include "Arduino.h"
#include "servomotor/Types.hpp"
#include "servomotor/core/Tools.hpp"


namespace servomotor {
    namespace core {
        /// Получить текущее время
        TimeMs getCurrentTime() { return static_cast<TimeMs>(millis()); }

        template<class T> struct Range {
            T min, max;

            T clamp(T value) const { return constrain(value, this->min, this->max); }
        };

        /// Хронометр - Рассчитывает dt
        class Chronometer {
            /// Время предыдущего расчёта
            TimeMs last_time{0};

        public:
            /// Рассчитать dt с предыдущей итерации
            TimeMs getDeltaTime() {
                TimeMs now = getCurrentTime();
                TimeMs dt = now - last_time;
                last_time = now;
                return dt;
            }
        };

        /// Вспомогательный класс находит производную значения
        template<class T> class Differentiator {

        private:
            /// Значение в предыдущий момент
            mutable T last_value{0};

            /// Возвращаемое значение
            mutable T diff{0};

        public:

            /// Рассчитать производную
            T calc(T current_value, TimeMs dt) const {
                if (dt > 0) {
                    diff = (current_value - last_value) / dt;
                    last_value = current_value;
                }

                return diff;
            }
        };

        /// Вспомогательный класс аккумулирует значения
        template<class T> class Integrator {
        private:
            /// Ограничение значений
            Range<T> range;

            mutable T integral{0};

        public:
            explicit Integrator(Range<T> range) :
                range{range} {}

            T calc(T current_value, TimeMs dt) const {
                if (dt > 0) {
                    integral = range.clamp(integral + current_value * dt);
                }

                return integral;
            }
        };
    }
}
