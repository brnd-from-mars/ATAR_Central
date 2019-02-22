#include <util/delay.h>
#include <avr/io.h>

#include "mcu/io/DigitalOutputPin.hpp"
#include "mcu/usart/UARTConnection.hpp"


int main ()
{
    DigitalOutputPin dop(&PORTB, PB7);

    UARTConnection uartUSB(0, 115200);
    UARTConnection uartAuxMCAlpha(1, 115200);
    UARTConnection uartAuxMCBeta(2, 115200);
    UARTConnection uartAuxRPGamma(3, 115200);
    int i = 100;

    sei();


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        if (uartUSB.DataAvailable())
        {
            switch (uartUSB.ReadByte())
            {
                case '0':
                    dop.Disable();
                    break;
                case '1':
                    dop.Enable();
                    break;
                case 'e':
                    uartUSB.WriteString("echo\n");
                default:
                    break;
            }
        }

        if (i == 0)
        {
            i = 100;
            uartUSB.WriteByte('1');
        }
        --i;
        _delay_us(1);
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
