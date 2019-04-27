//
// Created by Brendan Berg on 2019-04-26.
//

#ifndef ATAR_CENTRAL_PIDCONTROLLER_HPP
#define ATAR_CENTRAL_PIDCONTROLLER_HPP

#include <stdint.h>


class PIDController
{
public:

    PIDController (double gainP, double gainI, double gainD);

    double NextCorrection (int64_t errorP);

    void Reset ();


private:

    double m_GainP;

    double m_GainI;

    double m_GainD;

    int64_t m_ErrorP;

    int64_t m_ErrorI;


};


#endif //ATAR_CENTRAL_PIDCONTROLLER_HPP
