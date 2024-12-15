#pragma once


namespace servomotor {
    /// Интерфейс взаимодействия с сервомотором
    template<class PositionType = long, class SpeedType = char, class ResetEnumType = char> class ServoMotor {

    public:
        /// Тип и единицы измерения позиции
        using Position = PositionType;

        /// Тип и единицы измерения скорости
        using Speed = SpeedType;

        /// Установить целевую позицию
        virtual void setPosition(Position new_target_position) = 0;

        /// Получить текущее положение
        virtual Position getPosition() = 0;

        /// Установить целевую скорость
        virtual void setSpeed(Speed new_target_speed) = 0;

        /// Получить текущую скорость
        virtual Speed getSpeed() = 0;

        /// Установить поддержание контура регулирования
        virtual void setEnabled(bool enable) = 0;

        /// Получить состояние привода
        virtual bool isMoving() = 0;

        /// Сбросить состояния
        virtual void reset(ResetEnumType flags) = 0;
    };
}