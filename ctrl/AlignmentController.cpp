//
// Created by Brendan Berg on 2019-04-25.
//

#include <stdlib.h>

#include <ctrl/AlignmentController.hpp>


AlignmentController::AlignmentController (SensorDataContainer& sensorData,
                                          double gainRotP, double gainRotI,
                                          double gainRotD, double gainTransP,
                                          double gainTransI, double gainTransD)
    : m_SensorData(sensorData),
    m_RotPIDController(gainRotP, gainRotI, gainRotD),
    m_TransPIDController(gainTransP, gainTransI, gainTransD),
    m_TargetWallDistance(40)
{ }


int16_t AlignmentController::CorrectAlignment (int16_t& velocityRight,
                                               int16_t& velocityLeft)
{
    auto errorRot = CalculateRotationError();
    auto correctionRot = m_RotPIDController.NextCorrection(errorRot);

    auto errorTrans = CalculateTranslationError();
    auto correctionTrans = m_TransPIDController.NextCorrection(errorTrans);

    velocityRight = static_cast<int16_t>(correctionTrans + correctionRot);
    velocityLeft = static_cast<int16_t>(correctionTrans - correctionRot);

    return abs(errorRot) + abs(errorTrans);
}


void AlignmentController::Reset ()
{
    m_RotPIDController.Reset();
    m_TransPIDController.Reset();
}


int16_t AlignmentController::CalculateRotationError ()
{
    int16_t errorRot = 0;
    uint8_t sides = 0;

    for (uint8_t side = 0; side < 4; ++side)
    {
        if (m_SensorData.EntireWallOnSide(side, 70))
        {
            errorRot += m_SensorData.rangeOnSide[side][1]->linear -
                        m_SensorData.rangeOnSide[side][0]->linear;
            ++sides;
        }
    }

    if (sides == 0)
    {
        return 0;
    }

    errorRot /= sides;
    return errorRot;
}


int16_t AlignmentController::CalculateTranslationError ()
{
    int16_t errorPos = 0;

    if (m_SensorData.EntireWallOnSide(0, 70) &&
        m_SensorData.EntireWallOnSide(2, 70))
    {
        errorPos = m_SensorData.GetWallDistanceOnSide(0) -
            m_SensorData.GetWallDistanceOnSide(2);
    }
    else if (m_SensorData.EntireWallOnSide(0, 70))
    {
        errorPos =
            -(m_TargetWallDistance - m_SensorData.GetWallDistanceOnSide(0));
    }
    else if (m_SensorData.EntireWallOnSide(2, 70))
    {
        errorPos =
            (m_TargetWallDistance - m_SensorData.GetWallDistanceOnSide(2));
    }

    return errorPos;
}
