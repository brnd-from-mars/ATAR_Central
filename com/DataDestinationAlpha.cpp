//
// Created by Brendan Berg on 2019-04-23.
//

#include <com/DataDestinationAlpha.hpp>


DataDestinationAlpha::DataDestinationAlpha (SensorDataContainer& sensorData)
    : m_SensorData(sensorData)
{ }


void DataDestinationAlpha::DispatchMessage (const unsigned char* message,
                                            uint8_t len)
{
    m_SensorData.accelerometer.accelX = ((message[0] << 8) | (message[1]));
    m_SensorData.accelerometer.accelZ = ((message[2] << 8) | (message[3]));
    m_SensorData.accelerometer.angle = message[4];

    m_SensorData.rangeRF.raw = message[5];
    m_SensorData.rangeRF.linear = message[6];
    m_SensorData.rangeRB.raw = message[7];
    m_SensorData.rangeRB.linear = message[8];
    m_SensorData.rangeLB.raw = message[9];
    m_SensorData.rangeLB.linear = message[10];
    m_SensorData.rangeLF.raw = message[11];
    m_SensorData.rangeLF.linear = message[12];
}
