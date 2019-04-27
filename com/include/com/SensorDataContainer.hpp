//
// Created by Brendan Berg on 2019-04-25.
//

#ifndef ATAR_CENTRAL_SENSORDATACONTAINER_HPP
#define ATAR_CENTRAL_SENSORDATACONTAINER_HPP

#include <stdint.h>


struct SensorDataContainer
{
    struct IRRangeFinderData
    {
        uint8_t raw = 0x00;
        uint8_t linear = 0x00;
    };

    IRRangeFinderData rangeFL;
    IRRangeFinderData rangeFC;
    IRRangeFinderData rangeFR;
    IRRangeFinderData rangeRF;
    IRRangeFinderData rangeRB;
    IRRangeFinderData rangeBR;
    IRRangeFinderData rangeBL;
    IRRangeFinderData rangeLB;
    IRRangeFinderData rangeLF;

    IRRangeFinderData* rangeOnSide[4][2] = {
        {&rangeFL, &rangeFR},
        {&rangeRF, &rangeRB},
        {&rangeBR, &rangeBL},
        {&rangeLB, &rangeLF}
    };

    bool EntireWallOnSide (uint8_t side, uint8_t threshold)
    {
        return ((rangeOnSide[side][0]->linear < threshold) &&
                (rangeOnSide[side][1]->linear < threshold));
    }

    uint8_t GetWallDistanceOnSide (uint8_t side)
    {
        return (rangeOnSide[side][0]->linear +
                rangeOnSide[side][1]->linear) / 2;
    }


    struct ToggleSwitchData
    {
        bool state = false;
        bool changed = false;
    };

    ToggleSwitchData switch0;
    ToggleSwitchData switch1;
    ToggleSwitchData switch2;


    struct Accelerometer
    {
        int16_t accelX = 0x0000;
        int16_t accelZ = 0x0000;
        int8_t angle = 0x00;
    };

    Accelerometer accelerometer;


};


#endif //ATAR_CENTRAL_SENSORDATACONTAINER_HPP
