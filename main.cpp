#include <util/delay.h>
#include <avr/io.h>


int main ()
{
    DDRB |= (1 << PB7);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        PORTB |= 1 << PB7;
        _delay_ms(1000);
        PORTB &= ~(1 << PB7);
        _delay_ms(500);
    }
#pragma clang diagnostic pop

    return 0;
}
