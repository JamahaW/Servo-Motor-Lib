#pragma once

#include "servomotor/Config.hpp"


namespace servomotor {
    /// Интерфейс взаимодействия с сервомотором
    template<class PositionType = int32_t, class SpeedType = int8_t, class ResetEnumType = char> class ServoMotor {

    public:
        /// Тип и единицы измерения позиции
        using Position = PositionType;

        /// Тип и единицы измерения скорости
        using Speed = SpeedType;

    protected:
        /// Конфигурация сервомотора
        const Config<Position, Speed> &config;

        /// Целевая позиция регулятора
        Position target_position{0};

        /// Целевая скорость достижения позиции
        Speed target_speed{0};

        /// Флаг регулирования
        bool is_enabled{false};

    public:

        explicit ServoMotor(const Config<Position, Speed> &config) :
            config{config} {}

        /// Обновить состояние сервопривода
        void update() { if (this->is_enabled) { updateRegulator(); }}

        /// Установить активность поддержание контура регулирования
        void setEnabled(bool enable) { this->is_enabled = enable; }

        /// Сервомотор достиг целевой позиции
        bool isReady() {
            return abs(this->target_position - getPosition()) <= this->config.max_position_error;
        };

        /// Установить целевую позицию
        void setPosition(Position new_target_position) {
            this->target_position = clampToMax(new_target_position, this->config.max_abs_position);
        }

        /// Установить целевую скорость
        void setSpeed(Speed new_target_speed) {
            this->target_speed = clampToMax(new_target_speed, this->config.max_abs_speed);
        }

        /// Измерить реальное положение
        virtual Position getPosition() = 0;

        /// Измерить реальную скорость
        virtual Speed getSpeed() = 0;

        /// Сбросить состояния
        virtual void reset(ResetEnumType flags) = 0;

    protected:

        /// Обновить регулятор
        virtual void updateRegulator() = 0;

    private:

        template<class T> inline static T clampToMax(T value, T abs_max) {
            return constrain(value, -abs_max, +abs_max);
        }
    };
}