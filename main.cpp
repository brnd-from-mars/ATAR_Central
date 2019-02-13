#include <util/delay.h>
#include <avr/io.h>

#include "mcu/io/DigitalOutputPin.hpp"


int main ()
{
    DigitalOutputPin dop(&PORTB, PB7);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        dop.Enable();
        _delay_ms(1000);
        dop.Disable();
        _delay_ms(1000);
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
