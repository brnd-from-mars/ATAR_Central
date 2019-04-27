//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_CENTRAL_DATADESTINATIONALPHA_HPP
#define ATAR_CENTRAL_DATADESTINATIONALPHA_HPP

#include "mcu/usart/UARTDataDestination.hpp"

#include "SensorDataContainer.hpp"


class DataDestinationAlpha : public UARTDataDestination
{
public:

    explicit DataDestinationAlpha (SensorDataContainer& sensorData);

    void DispatchMessage (const unsigned char* message, uint8_t len) override;


private:

    SensorDataContainer& m_SensorData;


};


#endif //ATAR_CENTRAL_DATADESTINATIONALPHA_HPP
