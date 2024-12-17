#pragma once

#include "servomotor/core/PID.hpp"
#include "Types.hpp"


namespace servomotor {
    template<class DriverPower> struct Config {
        /// Настройки регулятора смещения
        core::PIDSettings<Speed, DriverPower> speed_regulator_settings;

        /// Настройки регулятора позиции
        core::PIDSettings<Position, Speed> position_regulator_settings;

        /// Максимально допустимое отклонение от целевой позиции
        Position target_position_deviation;
    };
}