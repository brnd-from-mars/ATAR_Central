//
// Created by Brendan Berg on 2019-04-27.
//

#ifndef ATAR_CENTRAL_DRIVECONTROLLER_HPP
#define ATAR_CENTRAL_DRIVECONTROLLER_HPP

#include <stdint.h>

#include "com/SensorDataContainer.hpp"

#include "PIDController.hpp"


class DriveController
{
public:

    DriveController (SensorDataContainer& sensorData, double gainRotP,
                     double gainRotI, double gainRotD, double gainTransP,
                     double gainTransI, double gainTransD);

    void Drive (int16_t velocity, int16_t& velocityRight,
                int16_t& velocityLeft);

    void Reset ();


private:

    SensorDataContainer& m_SensorData;

    PIDController m_RotPIDController;

    PIDController m_TransPIDController;

    int16_t m_TargetWallDistance;

    int16_t CalculateRotationError ();

    int16_t CalculateTranslationError ();


};


#endif //ATAR_CENTRAL_DRIVECONTROLLER_HPP
