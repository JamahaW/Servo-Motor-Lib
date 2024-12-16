#pragma once

#include "servomotor/Config.hpp"
#include "servomotor/core/PID.hpp"


namespace servomotor {
    /// Интерфейс взаимодействия с сервомотором
    template<class PositionType = int32_t, class SpeedType = int8_t> class ServoMotor {

    public:
        /// Тип и единицы измерения позиции
        using Position = PositionType;

        /// Тип и единицы измерения скорости
        using Speed = SpeedType;

    protected:
        /// Конфигурация сервомотора
        const Config<Position, Speed> &config;

        /// Регулятор позиции
        core::PID<Position> position_regulator;

        /// Регулятор скорости
        core::PID<Speed> speed_regulator;

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
            return abs(this->position_regulator.getTarget() - getPosition()) <= this->config.max_position_error;
        };

        /// Установить целевую позицию
        void setPosition(Position new_target_position) { this->position_regulator.setTarget(new_target_position); }

        /// Установить целевую скорость
        void setSpeed(Speed new_target_speed) { this->position_regulator.setTarget(new_target_speed); }

        /// Измерить реальное положение
        virtual Position getPosition() = 0;

        /// Измерить реальную скорость
        virtual Speed getSpeed() = 0;

        /// Сбросить состояния
        void reset() {};

    protected:

        /// Обновить регулятор
        virtual void updateRegulator() = 0;


    };
}