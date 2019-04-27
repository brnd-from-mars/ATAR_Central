//
// Created by Brendan Berg on 2019-04-25.
//

#include <stdlib.h>

#include <ctrl/MotorSet.hpp>


MotorSet::MotorSet (SensorDataContainer& sensorData)
    : m_AlignmentController(sensorData, 6.0, 0.02, 0.005, 6.0, 0.02, 0.005),
    m_DriveController(sensorData, 3.0, 0.001, 0.0, 3.0, 0.0, 0.0),
    m_RegisteredMotors(0), m_VelocityRight(0), m_VelocityLeft(0)
{ }


void MotorSet::RegisterMotor (Motor* motor)
{
    m_Motors[m_RegisteredMotors] = motor;
    m_SpeedController[m_RegisteredMotors] =
        SpeedController(motor, 3.0, 0.00, 0.5);
    ++m_RegisteredMotors;
}


void MotorSet::Drive (int16_t velocity)
{
    m_DriveController.Drive(velocity, m_VelocityRight, m_VelocityLeft);
}


void MotorSet::Rotate (int16_t velocity)
{
    m_VelocityRight = velocity;
    m_VelocityLeft = -velocity;
}


int16_t MotorSet::CorrectAlignment ()
{
    return m_AlignmentController.CorrectAlignment(m_VelocityRight,
                                                  m_VelocityLeft);
}


void MotorSet::UpdateEncoder ()
{
    for (uint8_t i = 0; i < m_RegisteredMotors; ++i)
    {
        m_Motors[i]->Update();
    }
}


void MotorSet::UpdateVelocity (bool velocityIsConstant)
{
    int16_t targetEncoderRight = 0;
    int16_t targetEncoderLeft = 0;

    if (velocityIsConstant)
    {
        auto encoderRatioRight =
            static_cast<double>(m_Motors[0]->GetEncoderSteps() +
                                m_Motors[1]->GetEncoderSteps()) /
            static_cast<double>(m_VelocityRight) / 4;
        auto encoderRatioLeft =
            static_cast<double>(m_Motors[2]->GetEncoderSteps() +
                                m_Motors[3]->GetEncoderSteps()) /
            static_cast<double>(m_VelocityLeft) / 4;

        auto targetEncoderRatio = encoderRatioLeft + encoderRatioRight;

        targetEncoderRight = static_cast<int16_t>(
            targetEncoderRatio * m_VelocityRight);
        targetEncoderLeft = static_cast<int16_t>(
            targetEncoderRatio * m_VelocityLeft);
    }
    else
    {
        targetEncoderRight = (m_Motors[0]->GetEncoderSteps() +
                              m_Motors[1]->GetEncoderSteps()) / 2;
        targetEncoderLeft = (m_Motors[2]->GetEncoderSteps() +
                             m_Motors[3]->GetEncoderSteps()) / 2;
    }

    m_SpeedController[0].SetVelocity(m_VelocityRight, targetEncoderRight);
    m_SpeedController[1].SetVelocity(m_VelocityRight, targetEncoderRight);

    m_SpeedController[2].SetVelocity(m_VelocityLeft, targetEncoderLeft);
    m_SpeedController[3].SetVelocity(m_VelocityLeft, targetEncoderLeft);
}


int32_t MotorSet::GetEncoderSteps ()
{
    int32_t sum = 0;

    for (uint8_t i = 0; i < m_RegisteredMotors; ++i)
    {
        sum += abs(m_Motors[i]->GetEncoderSteps());
    }

    return sum;
}
