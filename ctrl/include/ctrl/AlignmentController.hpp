//
// Created by Brendan Berg on 2019-04-25.
//

#ifndef ATAR_CENTRAL_ALIGNMENTCONTROLLER_HPP
#define ATAR_CENTRAL_ALIGNMENTCONTROLLER_HPP

#include <stdint.h>

#include "com/SensorDataContainer.hpp"

#include "PIDController.hpp"


class AlignmentController
{
public:

    AlignmentController (SensorDataContainer& sensorData, double gainRotP,
                         double gainRotI, double gainRotD, double gainTransP,
                         double gainTransI, double gainTransD);

    int16_t CorrectAlignment (int16_t& velocityRight, int16_t& velocityLeft);

    void Reset ();


private:

    SensorDataContainer& m_SensorData;

    int16_t m_TargetWallDistance;

    PIDController m_RotPIDController;

    PIDController m_TransPIDController;

    int16_t CalculateRotationError ();

    int16_t CalculateTranslationError ();


};


#endif //ATAR_CENTRAL_ALIGNMENTCONTROLLER_HPP
