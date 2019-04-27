//
// Created by Brendan Berg on 2019-04-25.
//

#ifndef ATAR_CENTRAL_MOTORSET_HPP
#define ATAR_CENTRAL_MOTORSET_HPP

#include "periph/Motor.hpp"

#include "com/SensorDataContainer.hpp"

#include "SpeedController.hpp"
#include "AlignmentController.hpp"
#include "DriveController.hpp"


class MotorSet
{
public:

    explicit MotorSet (SensorDataContainer& sensorData);

    void RegisterMotor (Motor* motor);

    void Drive (int16_t velocity);

    void Rotate (int16_t velocity);

    int16_t CorrectAlignment ();

    void UpdateEncoder ();

    void UpdateVelocity (bool velocityIsConstant = false);

    int32_t GetEncoderSteps ();


private:

    Motor* m_Motors[4] = {nullptr};

    SpeedController m_SpeedController[4];

    AlignmentController m_AlignmentController;

    DriveController m_DriveController;

    uint8_t m_RegisteredMotors;

    int16_t m_VelocityRight;

    int16_t m_VelocityLeft;


};


#endif //ATAR_CENTRAL_MOTORSET_HPP
