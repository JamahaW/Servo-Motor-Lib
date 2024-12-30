#pragma once

#include <stdint.h>


namespace servomotor {
    /// Тип и единицы измерения позиции
    using Position = int64_t;

    /// Тип и единица измерения времени
    using TimeMs = uint32_t;

    /**
     * Тип и единицы измерения скорости
     *
     * Speed = Position / TimeMs
     * */
    using Speed = float;

    /// Вывод
    using Pin = uint8_t;

    /// Направление
    enum class Direction : uint8_t {
        /// Прямое
        forward = 0x00,

        /// Обратное
        reverse = 0x01
    };
}