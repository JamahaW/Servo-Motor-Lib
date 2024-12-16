#pragma once

#include "servomotor/core/PID.hpp"


namespace servomotor {
    template<class PositionType, class SpeedType> struct Config {
        /// Настройки регулятора скорости
        core::PIDSettings<SpeedType> speed_regulator_settings;

        /// Настройки регулятора позиции
        core::PIDSettings<PositionType> position_regulator_settings;

        /// Максимально допустимое отклонение от целевой позиции
        PositionType max_position_error;
    };
}