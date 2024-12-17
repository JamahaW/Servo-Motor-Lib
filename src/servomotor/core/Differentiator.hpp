#pragma once

#include "servomotor/core/Tools.hpp"


namespace servomotor {
    namespace core {

        /// Вспомогательный класс находит производную значения
        template<class T> class Differentiator {

        private:
            /// Значение в предыдущий момент
            mutable T last_value{0};

            /// Время предыдущего расчёта
            mutable TimeMs last_time{0};

            /// Возвращаемое значение
            mutable Speed diff{0};

        public:

            /// Рассчитать производную
            T calc(T current_value) const {
                TimeMs now = core::getCurrentTime();
                TimeMs dt = now - last_time;

                if (dt > 0) {
                    this->diff = (current_value - last_value) / dt;

                    last_value = current_value;
                    last_time = now;
                }

                return this->diff;
            }
        };
    }
}