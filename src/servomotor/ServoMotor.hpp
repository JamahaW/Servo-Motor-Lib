#pragma once

#include "servomotor/Config.hpp"
#include "servomotor/core/PID.hpp"


namespace servomotor {
    /// Интерфейс взаимодействия с сервомотором
    class ServoMotor {

    public:
        /// Тип и единицы измерения позиции
        using Position = int32_t;

        /// Тип и единицы измерения скорости
        using Speed = int8_t;

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
            config{config}, position_regulator{config.position_regulator_settings}, speed_regulator{config.speed_regulator_settings} {}

        /// Измерить реальное положение
        virtual Position getPosition() = 0;

        /// Измерить реальную скорость
        virtual Speed getSpeed() = 0;

        /// Установить целевую позицию
        void setPosition(Position new_target_position) { this->position_regulator.setTarget(new_target_position); }

        /// Установить целевую скорость
        void setSpeed(Speed new_target_speed) { this->speed_regulator.setTarget(new_target_speed); }

        /// Установить активность поддержание контура регулирования
        void setEnabled(bool enable) { this->is_enabled = enable; }

        /// Сервомотор достиг целевой позиции
        bool isReady() {
            return abs(this->position_regulator.getTarget() - getPosition()) <= this->config.max_position_error;
        };

        /// Обновить состояние сервопривода
        void update() {
            if (not this->is_enabled) {
                return;
            }

            auto driver_u = this->speed_regulator.calc(getSpeed());
            // TODO struct контур регулирования: PID + get + write
            // driver.write(driver_u)

            auto speed_u = static_cast<Speed>(this->position_regulator.calc(getPosition()));
            // setSpeed(speed_u)
        }
    };
}