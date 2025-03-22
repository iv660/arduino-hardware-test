#pragma once

#include <ScreenInterface.h>

#include "GaugeInterface.h"

using XC::Hardware::ScreenInterface;

class MomentarySwitchDisplay: public GaugeInterface
{
    private:
        unsigned int x = 0;
        unsigned int y = 0;
        unsigned int pin = 0;
        unsigned int color = 0xFFFF;
        unsigned int backgroundColor = 0;
        char label;
        unsigned int radius = 7;
        bool isDownState = false;

        ScreenInterface* screen;

        bool isDown();
        bool stateHasChanged();

        void drawFootprint();
        void drawIndicator();
        void drawActiveIndicator();
        void drawInactiveIndicator();

        unsigned int getIndicatorRadius();
    public:
        MomentarySwitchDisplay(unsigned int x, unsigned int y, 
            unsigned int pin, char label, ScreenInterface* screen) 
            : x(x), y(y), pin(pin), label(label), screen(screen) {}

        void begin() override;
        void update() override;
};
