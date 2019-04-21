#include <avr/io.h>
#include <util/delay.h>

#include "mcu/usart/UARTConnection.hpp"

#include "mcu/timer/TimerFastPWM.hpp"

#include "mcu/interrupt/ExternalInterruptHandler.hpp"

#include "periph/Motor.hpp"


int main ()
{
    UARTConnection uartUSB(0, 9600);

    DigitalOutputPin dop(&PORTB, PB7);
    dop.Enable();

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
        motorRF.Update();
        motorRB.Update();
        motorLB.Update();
        motorLF.Update();

        motorRF.SetVelocity(-0x3f);
        motorRB.SetVelocity(-0x3f);
        motorLB.SetVelocity(0x3f);
        motorLF.SetVelocity(0x3f);
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop
}
