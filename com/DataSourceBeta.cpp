//
// Created by Brendan Berg on 2019-04-24.
//

#include <com/DataSourceBeta.hpp>


DataSourceBeta::DataSourceBeta ()
    : UARTDataSource(0)
{ }


void DataSourceBeta::Start ()
{
    m_MessageLength = 1;
    m_Message[0] = 0xf0;
}


void DataSourceBeta::EnableHeartbeat ()
{
    m_MessageLength = 1;
    m_Message[0] = 0xf1;
}


void DataSourceBeta::DisableHeartbeat ()
{
    m_MessageLength = 1;
    m_Message[0] = 0xf2;
}


void DataSourceBeta::SetLedVictim (uint8_t state)
{
    m_MessageLength = 2;
    m_Message[0] = 0x01;
    m_Message[1] = state;
}


void DataSourceBeta::SetLedState (uint8_t state)
{
    m_MessageLength = 2;
    m_Message[0] = 0x02;
    m_Message[1] = state;
}
