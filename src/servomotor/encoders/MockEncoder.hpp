#pragma once

#include "servomotor/encoders/Encoder.hpp"
#include "servomotor/core/Tools.hpp"
#include "servomotor/core/Differentiator.hpp"


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
            Speed getSpeed() const override {
                return this->differentiator.calc(this->current_position);
            }

            Position getPosition() const override { return this->current_position; }
        };
    }
}