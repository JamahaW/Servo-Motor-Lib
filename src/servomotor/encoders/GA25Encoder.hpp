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

            mutable volatile Position current_position{0};

        public:

            explicit GA25Encoder(Pin phase_alpha, Pin phase_beta, void(*on_encoder_move)(), Direction direction) :
                phase_beta{phase_beta}, direction{direction} {
                pinMode(phase_beta, INPUT);
                attachInterrupt(digitalPinToInterrupt(phase_alpha), on_encoder_move, RISING);
            }

            Position getPosition() const override {
                return current_position;
            }

            /// Вызывать в обработчике прерываний
            void onEncoderMoved() const {
                if (digitalRead(phase_beta) == (direction == Direction::forward)) {
                    current_position++;
                } else {
                    current_position--;
                }
            }
        };
    }
}