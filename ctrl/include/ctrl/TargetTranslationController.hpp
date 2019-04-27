//
// Created by Brendan Berg on 2019-04-27.
//

#ifndef ATAR_CENTRAL_TARGETTRANSLATIONCONTROLLER_HPP
#define ATAR_CENTRAL_TARGETTRANSLATIONCONTROLLER_HPP

#include "PIDController.hpp"
#include "MotorSet.hpp"


class TargetTranslationController
{
public:

    TargetTranslationController (MotorSet& motorSet, double distToEnc,
                                 double gainP, double gainI, double gainD);

    void SetTarget (int32_t target);

    void Drive ();

    void Reset ();


private:

    MotorSet& m_MotorSet;

    PIDController m_PIDController;

    double m_DistanceToEncoderRatio;

    int32_t m_Target;

    int8_t m_Sign;


};


#endif //ATAR_CENTRAL_TARGETTRANSLATIONCONTROLLER_HPP
