//
// Created by Brendan Berg on 2019-04-24.
//

#include <com/DataDestinationBeta.hpp>


DataDestinationBeta::DataDestinationBeta (SensorDataContainer& sensorData)
    : m_SensorData(sensorData)
{ }


void DataDestinationBeta::DispatchMessage (const unsigned char* message,
                                           uint8_t len)
{
    uint8_t switchStates = message[0];
    m_SensorData.switch0.state = ((switchStates >> 0) & 1);
    m_SensorData.switch0.changed = ((switchStates >> 1) & 1);
    m_SensorData.switch1.state = ((switchStates >> 2) & 1);
    m_SensorData.switch1.changed = ((switchStates >> 3) & 1);
    m_SensorData.switch2.state = ((switchStates >> 4) & 1);
    m_SensorData.switch2.changed = ((switchStates >> 5) & 1);

    m_SensorData.rangeFL.raw = message[1];
    m_SensorData.rangeFL.linear = message[2];
    m_SensorData.rangeFC.raw = message[3];
    m_SensorData.rangeFC.linear = message[4];
    m_SensorData.rangeFR.raw = message[5];
    m_SensorData.rangeFR.linear = message[6];
    m_SensorData.rangeBR.raw = message[7];
    m_SensorData.rangeBR.linear = message[8];
    m_SensorData.rangeBL.raw = message[9];
    m_SensorData.rangeBL.linear = message[10];
}
