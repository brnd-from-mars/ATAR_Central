#include <avr/io.h>
#include <util/delay.h>

#include "mcu/io/AnalogInputController.hpp"

#include "mcu/usart/UARTConnection.hpp"
#include "mcu/usart/UARTInterruptMasterConnection.hpp"

#include "mcu/timer/TimerFastPWM.hpp"

#include "mcu/interrupt/ExternalInterruptHandler.hpp"

#include "periph/Motor.hpp"
#include "periph/LightEmittingDiode.hpp"


int main ()
{
    UARTConnection uartUSB(0, 9600);
    UARTConnection uartGamma(2, 38400);
    UARTInterruptMasterConnection uartAlpha(1, 38400, &PORTH, PH5);
    UARTInterruptMasterConnection uartBeta(3, 38400, &PORTH, PH6);

    SingleColorLED ledHeartbeat;
    ledHeartbeat.RegisterPin(&PORTB, PB7);

    SingleColorLED ledGroundIllumination;
    ledGroundIllumination.RegisterPin(&PORTH, PH4);

    AnalogInputController analogInputController;

    AnalogInputPin groundSensorLeft(7);
    AnalogInputPin groundSensorRight(6);
    analogInputController.RegisterAnalogPin(&groundSensorLeft);
    analogInputController.RegisterAnalogPin(&groundSensorRight);

    AnalogInputPin batteryLevelSensor(5);
    analogInputController.RegisterAnalogPin(&batteryLevelSensor);

    analogInputController.Enable();

    TimerFastPWM timer0(0, 1);
    TimerFastPWM timer3(3, 1);
    TimerFastPWM timer4(4, 1);

    Motor motorRF(&PORTL, PL0, &PORTL, PL2, &PINL, PL4, &PINL, PL6,
                  &PORTE, PE3, &timer3, 0);

    Motor motorRB(&PORTB, PB2, &PORTB, PB0, &PING, PG2, &PING, PG0,
                  &PORTH, PH3, &timer4, 0);

    Motor motorLB(&PORTA, PA1, &PORTA, PA3, &PINC, PC2, &PINC, PC0,
                  &PORTE, PE5, &timer3, 2);

    Motor motorLF(&PORTA, PA7, &PORTA, PA5, &PINC, PC4, &PINC, PC6,
                  &PORTG, PG5, &timer0, 1);

    timer0.Enable();
    timer3.Enable();
    timer4.Enable();

    sei();


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        uartAlpha.Update();
        uartBeta.Update();

        motorRF.Update();
        motorRB.Update();
        motorLB.Update();
        motorLF.Update();

        _delay_ms(1000);
        ledHeartbeat.Enable();
        _delay_ms(1000);
        ledHeartbeat.Disable();
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop
}
