//
// Created by Brendan Berg on 2019-04-24.
//

#ifndef ATAR_CENTRAL_DATASOURCEALPHA_HPP
#define ATAR_CENTRAL_DATASOURCEALPHA_HPP

#include "mcu/usart/UARTDataSource.hpp"


class DataSourceAlpha : public UARTDataSource
{
public:

    DataSourceAlpha ();

    void Start ();

    void EnableHeartbeat ();

    void DisableHeartbeat ();

    void SetServoPosition (uint8_t position);


protected:

    void UpdateMessage () override {}


};


#endif //ATAR_CENTRAL_DATASOURCEALPHA_HPP
