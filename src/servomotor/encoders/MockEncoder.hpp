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
            mutable core::Chronometer chronometer{};

        public:
            Speed getSpeed() const override {
                return this->differentiator.calc(this->current_position, chronometer.getDeltaTime());
            }

            Position getPosition() const override { return this->current_position; }
        };
    }
}