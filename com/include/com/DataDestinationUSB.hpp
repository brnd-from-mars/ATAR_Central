//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_CENTRAL_DATADESTINATIONUSB_HPP
#define ATAR_CENTRAL_DATADESTINATIONUSB_HPP

#include "mcu/usart/UARTDataDestination.hpp"

#include "periph/LightEmittingDiode.hpp"


class DataDestinationUSB : public UARTDataDestination
{
public:

    explicit DataDestinationUSB (SingleColorLED& ledHeartbeat);

    void DispatchMessage (const char* message, uint8_t len) override;


private:

    SingleColorLED& m_LedHeartbeat;


};


#endif //ATAR_CENTRAL_DATADESTINATIONUSB_HPP
