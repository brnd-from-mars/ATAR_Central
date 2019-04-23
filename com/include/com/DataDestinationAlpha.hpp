//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_CENTRAL_DATADESTINATIONALPHA_HPP
#define ATAR_CENTRAL_DATADESTINATIONALPHA_HPP

#include "mcu/usart/UARTDataDestination.hpp"

#include "mcu/usart/UARTConnection.hpp"


class DataDestinationAlpha : public UARTDataDestination
{
public:

    explicit DataDestinationAlpha (UARTConnection& uartUSB);

    void DispatchMessage (const char* message, uint8_t len) override;


private:

    UARTConnection& m_UARTUSB;


};


#endif //ATAR_CENTRAL_DATADESTINATIONALPHA_HPP
