#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/DigitalOutputPin.hpp"
#include "mcu/io/AnalogInputPin.hpp"
#include "mcu/io/AnalogInputController.hpp"
#include "mcu/io/AnalogOutputPin.hpp"
#include "mcu/usart/UARTConnection.hpp"

#include "mcu/timer/Timer.hpp"
#include "mcu/timer/TimerFastPWM.hpp"

#include "mcu/interrupt/ExternalInterruptHandler.hpp"


class SendInterrupt : public ExternalInterruptHandler
{
public:

    SendInterrupt (uint8_t extIntrptID, UARTConnection* uart)
        : ExternalInterruptHandler(
            extIntrptID, ExternalInterruptConfig::senseControlModeRising, this),
        m_UART(uart)
    { }


    void InterruptServiceRoutine () override
    {
        m_UART->WriteByte(0xbb);
    }


private:

    UARTConnection* m_UART;


};


int main ()
{
    UARTConnection uartUSB(0, 9600);

    DigitalOutputPin dop(&PORTH, PH5);

    sei();

    SendInterrupt sendInterrupt(5, &uartUSB);

    uint8_t i = 10;


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        uartUSB.WriteByte(0xaa);
        _delay_ms(100);
        --i;
        if (i == 0)
        {
            dop.Flip();
            i = 10;
        }
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop
}
