#pragma once


#include <Arduino.h>
#include "servomotor/Types.hpp"
#include "servomotor/Config.hpp"
#include "servomotor/core/PID.hpp"
#include "servomotor/encoders/Encoder.hpp"
#include "servomotor/drivers/MotorDriver.hpp"


namespace servomotor {

    template<class DriverPower> class ServoMotor : public encoders::Encoder {

    protected:
        /// Конфигурация сервомотора
        const Config<DriverPower> &config;

        /// Датчик обратной связи по скорости и положению (энкодер)
        const encoders::Encoder &encoder;

        /// Драйвер установки скорости (мотор)
        const drivers::MotorDriver<DriverPower> &driver;

        /// Регулятор удержания целевой позиции
        core::PID<Position, Speed> position_regulator;

        /// Регулятор скорости
        core::PID<Speed, DriverPower> speed_regulator;

        /// Флаг регулирования
        bool is_enabled{false};

    public:

        explicit ServoMotor(const Config<DriverPower> &config, const encoders::Encoder &encoder, const drivers::MotorDriver<DriverPower> &driver) :
            config(config), encoder(encoder), driver(driver),
            position_regulator(config.position_regulator_settings),
            speed_regulator(config.speed_regulator_settings) {}

        Position getPosition() const override {
            return this->encoder.getPosition();
        }

        Speed getSpeed() const override {
            return this->encoder.getSpeed();
        }

        /// Установить целевую позицию
        void setPosition(Position new_target_position) {
            this->position_regulator.setTarget(new_target_position);
        }

        /// Установить целевую скорость
        void setSpeed(Speed new_target_speed) {
            this->speed_regulator.setRange(core::Range<DriverPower>{-new_target_speed, new_target_speed});
        }

        /// Установить активность поддержание контура регулирования
        void setEnabled(bool enable) {
            this->is_enabled = enable;
        }

        /// Сервомотор достиг целевой позиции
        bool isReady() {
            Position delta = this->position_regulator.getTarget() - getPosition();
            return abs(delta) <= this->config.target_position_deviation;
        };

        /// Обновить состояние сервопривода
        void update() {
            if (this->is_enabled) {
                this->speed_regulator.setTarget(this->position_regulator.calc(getPosition()));
                this->driver.setPower(this->speed_regulator.calc(getSpeed()));
            }
        }


    };
}