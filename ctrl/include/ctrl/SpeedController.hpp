//
// Created by Brendan Berg on 2019-04-25.
//

#ifndef ATAR_CENTRAL_SPEEDCONTROLLER_HPP
#define ATAR_CENTRAL_SPEEDCONTROLLER_HPP

#include "periph/Motor.hpp"

#include "PIDController.hpp"


class SpeedController
{
public:

    SpeedController ();

    SpeedController (Motor* motor, double gainP, double gainI, double gainD);

    void SetVelocity (int16_t velocity, int64_t meanEncoderSteps);

    void Reset ();


private:

    Motor* m_Motor;

    PIDController m_PIDController;


};


#endif //ATAR_CENTRAL_SPEEDCONTROLLER_HPP
