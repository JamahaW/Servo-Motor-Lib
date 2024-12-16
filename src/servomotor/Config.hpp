#pragma once

namespace servomotor {
    template<class PositionType, class SpeedType> struct Config {
        /// Максимальное абсолютное значение скорости
        SpeedType max_abs_speed;
        
        /// Максимальное абсолютное значение позиции
        PositionType max_abs_position;

        /// Максимально допустимое отклонение от целевой позиции
        PositionType max_position_error;
    };
}