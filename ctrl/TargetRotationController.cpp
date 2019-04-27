//
// Created by Brendan Berg on 2019-04-28.
//

#include <stdlib.h>

#include <ctrl/TargetRotationController.hpp>

#define SIGN(x) (x == 0 ? 0 : (x > 0 ? 1 : -1))


TargetRotationController::TargetRotationController (MotorSet& motorSet,
                                                    double distToAngle,
                                                    double gainP, double gainI,
                                                    double gainD)
    : m_MotorSet(motorSet), m_DistanceToAngleRatio(distToAngle),
    m_PIDController(gainP, gainI, gainD), m_Target(0), m_Sign(1)
{ }


void TargetRotationController::SetTarget (int32_t target)
{
    m_Target = abs(static_cast<int16_t>(target * m_DistanceToAngleRatio));
    m_Sign = SIGN(target);
}


void TargetRotationController::Rotate ()
{
    auto error = m_Target - m_MotorSet.GetEncoderSteps();
    auto correction = m_PIDController.NextCorrection(error);

    if (correction > 140)
    {
        correction = 140;
    }
    if (correction < -140)
    {
        correction = -140;
    }

    m_MotorSet.Rotate(correction);
}


void TargetRotationController::Reset ()
{
    m_PIDController.Reset();
}
