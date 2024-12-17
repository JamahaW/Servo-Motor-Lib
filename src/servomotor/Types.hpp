#pragma once

#include <stdint.h>


namespace servomotor {
    /// Тип и единицы измерения позиции
    using Position = int32_t;

    /// Тип и единица измерения времени
    using TimeMs = uint32_t;

    /**
     * Тип и единицы измерения скорости
     *
     * Speed = Position / TimeMs
     * */
    using Speed = int16_t;
}