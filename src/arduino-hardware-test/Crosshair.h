#pragma once

#include <ScreenInterface.h>

using XC::Hardware::ScreenInterface;

class Crosshair
{
    private:
        unsigned long x = 0;
        unsigned long y = 0;
        const unsigned int color = 0xFFFF;
        const unsigned int backgroundColor = 0;
        const unsigned int size = 9;

        void renderCrosshairOnScreen(unsigned long x, unsigned long y, unsigned int color, ScreenInterface* screen);

    public:
        Crosshair(unsigned long x, unsigned long y) : x(x), y(y) {}
        void renderOn(ScreenInterface* screen);
        void removeFrom(ScreenInterface* screen);
};