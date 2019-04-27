//
// Created by Brendan Berg on 2019-04-26.
//

#include <ctrl/PIDController.hpp>


PIDController::PIDController (double gainP, double gainI, double gainD)
    : m_GainP(gainP), m_GainI(gainI), m_GainD(gainD), m_ErrorP(0), m_ErrorI(0)
{ }


double PIDController::NextCorrection (int64_t errorP)
{
    auto errorD = errorP - m_ErrorP;
    m_ErrorP = errorP;
    m_ErrorI += errorP;

    auto correction = m_GainP * errorP +
                      m_GainI * m_ErrorI +
                      m_GainD * errorD;

    return correction;
}


void PIDController::Reset ()
{
    m_ErrorP = 0;
    m_ErrorI = 0;
}
