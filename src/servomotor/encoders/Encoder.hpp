#pragma once

#include "servomotor/Types.hpp"


namespace servomotor {
    /// Датчики скорости и положения
    namespace encoders {
        /// Интерфейс Датчика скорости и положения
        class Encoder {
        public:
            /// Измерить текущую скорость
            virtual Speed getSpeed() const = 0;

            /// Измерить текущее положение
            virtual Position getPosition() const = 0;
        };
    }
}