#include <util/delay.h>
#include <avr/io.h>

#include "mcu/io/DigitalOutputPin.hpp"
#include "mcu/io/DigitalInputPin.hpp"


int main ()
{
    DigitalOutputPin dop(&PORTB, PB7);
    DigitalInputPin dip(&PINB, PB6);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        if (dip.Get())
        {
            dop.Enable();
        }
        else
        {
            dop.Disable();
        }
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
