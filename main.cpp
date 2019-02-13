#include <util/delay.h>
#include <avr/io.h>

#include "mcu/io/DigitalOutputPin.hpp"


int main ()
{
    DDRB |= (1 << PB7);
    DigitalOutputPin dop(&PORTB, PB7);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        dop.Enable();
        _delay_ms(50);
        dop.Disable();
        _delay_ms(100);
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
