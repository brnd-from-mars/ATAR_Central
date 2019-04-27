//
// Created by Brendan Berg on 2019-04-28.
//

#ifndef ATAR_CENTRAL_TARGETROTATIONCONTROLLER_HPP
#define ATAR_CENTRAL_TARGETROTATIONCONTROLLER_HPP

#include "PIDController.hpp"
#include "MotorSet.hpp"


class TargetRotationController
{
public:

    TargetRotationController (MotorSet& motorSet, double distToAngle,
                              double gainP, double gainI, double gainD);

    void SetTarget (int32_t target);

    void Rotate ();

    void Reset ();


private:

    MotorSet& m_MotorSet;

    PIDController m_PIDController;

    double m_DistanceToAngleRatio;

    int32_t m_Target;

    int8_t m_Sign;



};


#endif //ATAR_CENTRAL_TARGETROTATIONCONTROLLER_HPP
