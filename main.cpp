#include <avr/io.h>
#include <util/delay.h>

#include "mcu/io/AnalogInputController.hpp"
#include "mcu/io/AnalogInputPin.hpp"

#include "mcu/usart/UARTConnection.hpp"
#include "mcu/usart/UARTInterruptMasterConnection.hpp"

#include "mcu/timer/TimerFastPWM.hpp"

#include "periph/Motor.hpp"
#include "periph/LightEmittingDiode.hpp"

#include "com/DataDestinationUSB.hpp"
#include "com/DataDestinationAlpha.hpp"


int main ()
{
//    UARTInterruptMasterConnection uartBeta(0x03, 38400, &PORTH, PH6);
//    UARTConnection uartGamma(0x02, 38400);

    SingleColorLED ledHeartbeat;
    ledHeartbeat.RegisterPin(&PORTB, PB7);

//    // TODO: outsource
//    SingleColorLED ledGroundIllumination;
//    ledGroundIllumination.RegisterPin(&PORTH, PH4);

//    AnalogInputController analogInputController;
//
//    // TODO: outsource
//    AnalogInputPin groundSensorLeft(0x07);
//    AnalogInputPin groundSensorRight(0x06);
//    analogInputController.RegisterAnalogPin(&groundSensorLeft);
//    analogInputController.RegisterAnalogPin(&groundSensorRight);
//
//    // TODO: outsource
//    AnalogInputPin batteryLevelSensor(0x05);
//    analogInputController.RegisterAnalogPin(&batteryLevelSensor);
//
//    analogInputController.Enable();

//    TimerFastPWM timer0(0x00, 0x0001);
//    TimerFastPWM timer3(0x03, 0x0001);
//    TimerFastPWM timer4(0x04, 0x0001);
//
//    Motor motorRF(&PORTL, PL0, &PORTL, PL2, &PINL, PL4, &PINL, PL6,
//                  &PORTE, PE3, &timer3, 0x00);
//
//    Motor motorRB(&PORTB, PB2, &PORTB, PB0, &PING, PG2, &PING, PG0,
//                  &PORTH, PH3, &timer4, 0x00);
//
//    Motor motorLB(&PORTA, PA1, &PORTA, PA3, &PINC, PC2, &PINC, PC0,
//                  &PORTE, PE5, &timer3, 0x02);
//
//    Motor motorLF(&PORTA, PA7, &PORTA, PA5, &PINC, PC4, &PINC, PC6,
//                  &PORTG, PG5, &timer0, 0x01);
//
//    timer0.Enable();
//    timer3.Enable();
//    timer4.Enable();

    // TODO:
    DataDestinationUSB dataDestinationUSB(ledHeartbeat);
    UARTConnection uartUSB(0x00, 38400, dataDestinationUSB);

    DataDestinationAlpha dataDestinationAlpha(uartUSB);
    UARTInterruptMasterConnection uartAlpha(0x01, 38400, dataDestinationAlpha,
                                            &PORTH, PH5);

    sei();

    _delay_ms(2000);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        uartUSB.ReceiveData();
        uartAlpha.ReceiveData();

        uartAlpha.RequestData();

        _delay_ms(100);
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop
}
