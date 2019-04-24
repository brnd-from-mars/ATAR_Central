//
// Created by Brendan Berg on 2019-04-24.
//

#include <com/DataSourceAlpha.hpp>


DataSourceAlpha::DataSourceAlpha ()
    : UARTDataSource(0)
{ }


void DataSourceAlpha::EnableHeartbeat ()
{
    m_MessageLength = 2;
    m_Message[0] = 0x00;
    m_Message[1] = 0x01;
}


void DataSourceAlpha::DisableHeartbeat ()
{
    m_MessageLength = 2;
    m_Message[0] = 0x00;
    m_Message[1] = 0x00;
}


void DataSourceAlpha::SetServoPosition (uint8_t position)
{
    m_MessageLength = 2;
    m_Message[0] = 0x01;
    m_Message[1] = position;
}


void DataSourceAlpha::CalibrateAccelerometer ()
{
    m_MessageLength = 2;
    m_Message[0] = 0x02;
    m_Message[1] = 0xff;
}
