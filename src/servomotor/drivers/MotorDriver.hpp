#pragma once

#include "servomotor/Types.hpp"


namespace servomotor {

    /// Драйверы для управления моторами
    namespace drivers {

        /// Интерфейс драйвера мотора
        template<class Power> class MotorDriver {
        public:

            /// Подать мощность на мотор
            virtual void setPower(Power power) const = 0;
        };
    }
}