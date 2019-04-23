//
// Created by Brendan Berg on 2019-04-23.
//

#include <com/DataDestinationUSB.hpp>


DataDestinationUSB::DataDestinationUSB (SingleColorLED& ledHeartbeat)
    : m_LedHeartbeat(ledHeartbeat)
{ }


void DataDestinationUSB::DispatchMessage (const char* message, uint8_t len)
{
    if (message[0] == '1')
    {
        m_LedHeartbeat.Flip();
    }
}
