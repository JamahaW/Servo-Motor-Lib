#pragma once

#include "servomotor/encoders/Encoder.hpp"
#include "servomotor/core/Tools.hpp"
#include "Arduino.h"


namespace servomotor {
    namespace encoders {

        class GA25Encoder : public Encoder {
        private:
            const Pin phase_beta;
            const Direction direction;

            static constexpr int DIFF_K = 100;

            mutable volatile Position current_position{0};
            core::Differentiator<Position> differentiator{};
            mutable core::Chronometer chronometer{};

        public:

            explicit GA25Encoder(Pin phase_alpha, Pin phase_beta, void(*on_encoder_move)(), Direction direction) :
                phase_beta{phase_beta}, direction{direction} {
                pinMode(phase_beta, INPUT);
                attachInterrupt(digitalPinToInterrupt(phase_alpha), on_encoder_move, RISING);
            }

            Speed getSpeed() const override {
                return static_cast<Speed>(differentiator.calc(current_position, chronometer.getDeltaTime()));
            }

            Position getPosition() const override {
                return this->current_position;
            }

            /// Вызывать в обработчике прерываний
            void onEncoderMoved() const {
                if (digitalRead(this->phase_beta) == (direction == Direction::forward)) {
                    this->current_position += DIFF_K;
                } else {
                    this->current_position -= DIFF_K;
                }
            }
        };
    }
}