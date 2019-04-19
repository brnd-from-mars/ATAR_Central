#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/DigitalOutputPin.hpp"
#include "mcu/io/AnalogInputPin.hpp"
#include "mcu/io/AnalogInputController.hpp"
#include "mcu/io/AnalogOutputPin.hpp"
#include "mcu/usart/UARTConnection.hpp"

#include "mcu/timer/Timer.hpp"
#include "mcu/timer/TimerFastPWM.hpp"


int main ()
{
    sei();

    TimerFastPWM timer0 (0, 256);
    TimerFastPWM timer1 (1, 256);
    TimerFastPWM timer3 (3, 1);

    AnalogOutputPin aop0(&PORTB, PB7, &timer0, 0);
    AnalogOutputPin aop1(&PORTB, PB6, &timer1, 1);
    AnalogOutputPin aop2(&PORTE, PE5, &timer3, 2);

    timer0.Enable();
    timer1.Enable();
    timer3.Enable();


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        aop0.SetValue(0x9f);
        aop1.SetValue(0x5f);
        aop2.SetValue(0x8f);
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
