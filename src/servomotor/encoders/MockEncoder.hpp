#pragma once

#include "servomotor/encoders/Encoder.hpp"
#include "servomotor/core/Tools.hpp"


namespace servomotor {
    namespace encoders {
        /// Реализация-Заглушка для энкодера
        class MockEncoder : public Encoder {

        public:
            /// Текущая позиция энкодера
            mutable Position current_position{0};

        private:
            core::Differentiator<Position> differentiator{};

        public:
            Speed getSpeed(TimeMs dt) const override {
                return differentiator.calc(current_position, dt);
            }

            Position getPosition() const override { return current_position; }
        };
    }
}