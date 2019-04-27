//
// Created by Brendan Berg on 2019-04-25.
//

#include <ctrl/SpeedController.hpp>


SpeedController::SpeedController ()
    : m_Motor(nullptr), m_PIDController(0.0, 0.0, 0.0)
{ }


SpeedController::SpeedController (Motor* motor, double gainP, double gainI,
                                  double gainD)
    : m_Motor(motor), m_PIDController(gainP, gainI, gainD)
{ }


void SpeedController::SetVelocity (int16_t velocity, int64_t meanEncoderSteps)
{
    auto errorP = meanEncoderSteps - m_Motor->GetEncoderSteps();
    auto correct = m_PIDController.NextCorrection(errorP);

    velocity += static_cast<int16_t>(correct);

    m_Motor->SetVelocity(velocity);
}


void SpeedController::Reset ()
{
    m_PIDController.Reset();
}
