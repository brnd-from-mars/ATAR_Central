//
// Created by Brendan Berg on 2019-04-24.
//

#ifndef ATAR_CENTRAL_DATADESTINATIONBETA_HPP
#define ATAR_CENTRAL_DATADESTINATIONBETA_HPP

#include "mcu/usart/UARTDataDestination.hpp"

#include "SensorDataContainer.hpp"


class DataDestinationBeta : public UARTDataDestination
{
public:

    explicit DataDestinationBeta (SensorDataContainer& sensorData);

    void DispatchMessage (const unsigned char* message, uint8_t len) override;


private:

    SensorDataContainer& m_SensorData;


};


#endif //ATAR_CENTRAL_DATADESTINATIONBETA_HPP
