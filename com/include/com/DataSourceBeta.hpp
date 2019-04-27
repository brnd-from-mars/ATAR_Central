//
// Created by Brendan Berg on 2019-04-24.
//

#ifndef ATAR_CENTRAL_DATASOURCEBETA_HPP
#define ATAR_CENTRAL_DATASOURCEBETA_HPP

#include "mcu/usart/UARTDataSource.hpp"


class DataSourceBeta : public UARTDataSource
{
public:

    DataSourceBeta ();

    void Start ();

    void EnableHeartbeat ();

    void DisableHeartbeat ();

    void SetLedVictim (uint8_t state);

    void SetLedState (uint8_t state);


protected:

    void UpdateMessage () override {}


};


#endif //ATAR_CENTRAL_DATASOURCEBETA_HPP
