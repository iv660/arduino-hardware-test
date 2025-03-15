#pragma once

#include <ScreenInterface.h>

using XC::Hardware::ScreenInterface;

class JoystickGauge
{
    private:
        static const int scopeRadius = 20;
        unsigned int x;
        unsigned int y;
        unsigned int vrxPin;
        unsigned int vryPin;
        unsigned int color = 0xFFFF;
        ScreenInterface* screen;

        long readX();
        long readY();
        void drawScope(int centerX, int centerY);
        void drawPointer(int pointerX, int pointerY);
        void displayReadouts(int xReadout, int yReadout);
        long readoutToRelativePosition(long readout);

        char* toFormat(char* format, long number);
    public:
        JoystickGauge(unsigned int x, unsigned int y, 
            unsigned int vrxPin, unsigned int vryPin, 
            ScreenInterface* screen) : 
            x(x), y(y), vrxPin(vrxPin), vryPin(vryPin), 
            screen(screen) {};

        void begin();
        void update();
};
