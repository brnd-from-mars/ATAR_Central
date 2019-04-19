#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/DigitalOutputPin.hpp"
#include "mcu/io/AnalogInputPin.hpp"
#include "mcu/io/AnalogInputController.hpp"
#include "mcu/usart/UARTConnection.hpp"


int main ()
{
    AnalogInputController aic;
    AnalogInputPin aip1(7);

    DigitalOutputPin dop(&PORTB, PB7);

    sei();

    UARTConnection uartUSB(0, 115200);

    aic.EnableAnalogController();

    int i = 1000;


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        uartUSB.WriteByte(aip1.GetValue());
        _delay_ms(1);
        --i;
        if (i == 0)
        {
            dop.Flip();
            i = 1000;
        }
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
