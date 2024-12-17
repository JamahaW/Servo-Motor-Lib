#pragma once

#include "Arduino.h"
#include "servomotor/Types.hpp"


namespace servomotor {
    namespace core {
        /// Получить текущее время
        TimeMs getCurrentTime() { return static_cast<TimeMs>(millis()); }
    }
}