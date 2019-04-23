//
// Created by Brendan Berg on 2019-04-23.
//

#include <com/DataDestinationAlpha.hpp>


DataDestinationAlpha::DataDestinationAlpha (UARTConnection& uartUSB)
    : m_UARTUSB(uartUSB)
{ }


void DataDestinationAlpha::DispatchMessage (const char* message, uint8_t len)
{
    m_UARTUSB.WriteString(message, len);
    for (uint8_t i = 0; i < (16 - len); ++i)
    {
        m_UARTUSB.WriteByte(0x00);
    }
}
