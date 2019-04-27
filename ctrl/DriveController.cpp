//
// Created by Brendan Berg on 2019-04-27.
//

#include <stdlib.h>

#include <ctrl/DriveController.hpp>


DriveController::DriveController (SensorDataContainer& sensorData,
                                  double gainRotP, double gainRotI,
                                  double gainRotD, double gainTransP,
                                  double gainTransI, double gainTransD)
    : m_SensorData(sensorData),
      m_RotPIDController(gainRotP, gainRotI, gainRotD),
      m_TransPIDController(gainTransP, gainTransI, gainTransD),
      m_TargetWallDistance(40)
{

}


void DriveController::Drive (int16_t velocity, int16_t& velocityRight,
                             int16_t& velocityLeft)
{
    auto errorRot = CalculateRotationError();
    auto correctionRot = m_RotPIDController.NextCorrection(errorRot);

    auto errorTrans = CalculateTranslationError();
    auto correctionTrans = m_TransPIDController.NextCorrection(errorTrans);

    if (velocity < 0)
    {
        correctionTrans *= -1;
    }

    auto correction = correctionRot + correctionTrans;

    velocityRight = velocity + static_cast<int16_t>(correction);
    velocityLeft = velocity - static_cast<int16_t>(correction);
}


void DriveController::Reset ()
{
    m_RotPIDController.Reset();
    m_TransPIDController.Reset();
}


int16_t DriveController::CalculateRotationError ()
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


int16_t DriveController::CalculateTranslationError ()
{
    int16_t errorPos = 0;

    if (m_SensorData.EntireWallOnSide(3, 70) &&
        m_SensorData.EntireWallOnSide(1, 70))
    {
        errorPos = m_SensorData.GetWallDistanceOnSide(3) -
                   m_SensorData.GetWallDistanceOnSide(1);
    }
    else if (m_SensorData.EntireWallOnSide(3, 70))
    {
        errorPos =
            -(m_TargetWallDistance - m_SensorData.GetWallDistanceOnSide(3));
    }
    else if (m_SensorData.EntireWallOnSide(1, 70))
    {
        errorPos =
            (m_TargetWallDistance - m_SensorData.GetWallDistanceOnSide(1));
    }

    return errorPos;
}
