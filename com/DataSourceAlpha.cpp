//
// Created by Brendan Berg on 2019-04-24.
//

#include <com/DataSourceAlpha.hpp>


DataSourceAlpha::DataSourceAlpha ()
    : UARTDataSource(0)
{ }

void DataSourceAlpha::Start ()
{
    m_MessageLength = 1;
    m_Message[0] = 0xf0;
}

void DataSourceAlpha::EnableHeartbeat ()
{
    m_MessageLength = 1;
    m_Message[0] = 0xf1;
}


void DataSourceAlpha::DisableHeartbeat ()
{
    m_MessageLength = 1;
    m_Message[0] = 0xf2;
}


void DataSourceAlpha::SetServoPosition (uint8_t position)
{
    m_MessageLength = 2;
    m_Message[0] = 0x00;
    m_Message[1] = position;
}
