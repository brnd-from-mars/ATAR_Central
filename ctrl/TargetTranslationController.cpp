//
// Created by Brendan Berg on 2019-04-27.
//

#include <stdlib.h>

#include <ctrl/TargetTranslationController.hpp>

#define SIGN(x) (x == 0 ? 0 : (x > 0 ? 1 : -1))


TargetTranslationController::TargetTranslationController (MotorSet& motorSet,
                                                          double distToEnc,
                                                          double gainP,
                                                          double gainI,
                                                          double gainD)
    : m_MotorSet(motorSet), m_DistanceToEncoderRatio(distToEnc),
    m_PIDController(gainP, gainI, gainD), m_Target(0), m_Sign(1)
{ }


void TargetTranslationController::SetTarget (int32_t target)
{
    m_Target = abs(static_cast<int16_t>(target * m_DistanceToEncoderRatio));
    m_Sign = SIGN(target);
}


void TargetTranslationController::Drive ()
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

    m_MotorSet.Drive(m_Sign * static_cast<int16_t>(correction));
}


void TargetTranslationController::Reset ()
{
    m_PIDController.Reset();
    m_Target = 0;
}
