#include <avr/io.h>
#include <util/delay.h>

#include "mcu/io/AnalogInputController.hpp"

#include "mcu/usart/UARTConnection.hpp"
#include "mcu/usart/UARTInterruptMasterConnection.hpp"

#include "mcu/timer/TimerFastPWM.hpp"

#include "periph/Motor.hpp"
#include "periph/LightEmittingDiode.hpp"

#include "com/SensorDataContainer.hpp"
#include "com/DataSourceAlpha.hpp"
#include "com/DataSourceBeta.hpp"
#include "com/DataDestinationUSB.hpp"
#include "com/DataDestinationAlpha.hpp"
#include "com/DataDestinationBeta.hpp"

#include "ctrl/MotorSet.hpp"
#include "ctrl/TargetTranslationController.hpp"
#include "ctrl/TargetRotationController.hpp"


int main ()
{
    SingleColorLED ledHeartbeat;
    ledHeartbeat.RegisterPin(&PORTB, PB7);

//    // TODO: outsource
//    SingleColorLED ledGroundIllumination;
//    ledGroundIllumination.RegisterPin(&PORTH, PH4);
//    ledGroundIllumination.Disable();

//    AnalogInputController analogInputController;

//    // TODO: outsource
//    AnalogInputPin groundSensorLeft(0x07);
//    AnalogInputPin groundSensorRight(0x06);
//    analogInputController.RegisterAnalogPin(&groundSensorLeft);
//    analogInputController.RegisterAnalogPin(&groundSensorRight);

//    // TODO: outsource
//    AnalogInputPin batteryLevelSensor(0x05);
//    analogInputController.RegisterAnalogPin(&batteryLevelSensor);

//    analogInputController.Enable();

    SensorDataContainer sensorData;

    TimerFastPWM timer0(0x00, 0x0001);
    TimerFastPWM timer3(0x03, 0x0001);
    TimerFastPWM timer4(0x04, 0x0001);

    MotorSet motorSet(sensorData);

    Motor motorRF(&PORTL, PL0, &PORTL, PL2, &PINL, PL4, &PINL, PL6,
                  &PORTE, PE3, &timer3, 0x00);
    motorSet.RegisterMotor(&motorRF);

    Motor motorRB(&PORTB, PB2, &PORTB, PB0, &PING, PG2, &PING, PG0,
                  &PORTH, PH3, &timer4, 0x00);
    motorSet.RegisterMotor(&motorRB);

    Motor motorLF(&PORTA, PA7, &PORTA, PA5, &PINC, PC4, &PINC, PC6,
                  &PORTG, PG5, &timer0, 0x01);
    motorSet.RegisterMotor(&motorLF);

    Motor motorLB(&PORTA, PA1, &PORTA, PA3, &PINC, PC2, &PINC, PC0,
                  &PORTE, PE5, &timer3, 0x02);
    motorSet.RegisterMotor(&motorLB);

    timer0.Enable();
    timer3.Enable();
    timer4.Enable();

    DataDestinationUSB dataDestinationUSB;
    UARTConnection uartUSB(0x00, 38400, dataDestinationUSB);

    DataSourceAlpha dataSourceAlpha;
    DataDestinationAlpha dataDestinationAlpha(sensorData);
    UARTInterruptMasterConnection uartAlpha(
        0x01, 38400, dataDestinationAlpha, &PORTH, PH5);

    DataSourceBeta dataSourceBeta;
    DataDestinationBeta dataDestinationBeta(sensorData);
    UARTInterruptMasterConnection uartBeta(
        0x03, 38400, dataDestinationBeta, &PORTH, PH6);

    sei();

    _delay_ms(500);

    dataSourceAlpha.Start();
    uartAlpha.SendData(dataSourceAlpha);

    dataSourceBeta.Start();
    uartAlpha.SendData(dataSourceBeta);

    _delay_ms(500);

    uartAlpha.RequestData();
    uartBeta.RequestData();

    uartUSB.ReceiveData();
    uartAlpha.ReceiveData();
    uartBeta.ReceiveData();

    int i = 100;

    dataSourceBeta.SetLedState(0x01);
    uartBeta.SendData(dataSourceBeta);

    TargetTranslationController translationController(motorSet, 35.0, 3.0, 0.0, 0.5);
    translationController.SetTarget(-30);

    TargetRotationController rotationController(motorSet, 6.5, 3.0, 0.0, 0.5);
    rotationController.SetTarget(90);

    _delay_ms(500);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        uartAlpha.RequestData();
        uartBeta.RequestData();

        uartUSB.ReceiveData();
        uartAlpha.ReceiveData();
        uartBeta.ReceiveData();

        motorSet.UpdateEncoder();
        rotationController.Rotate();
        motorSet.UpdateVelocity(true);

        --i;
        if (i == 500)
        {
            ledHeartbeat.Disable();
            dataSourceAlpha.DisableHeartbeat();
            dataSourceBeta.DisableHeartbeat();
            uartAlpha.SendData(dataSourceAlpha);
            uartBeta.SendData(dataSourceBeta);
        }
        if (i == 0)
        {
            ledHeartbeat.Enable();
            dataSourceAlpha.EnableHeartbeat();
            dataSourceBeta.EnableHeartbeat();
            uartAlpha.SendData(dataSourceAlpha);
            uartBeta.SendData(dataSourceBeta);
            i = 1000;
        }
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop
}
