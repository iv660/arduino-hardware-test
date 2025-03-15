#pragma once

#include <ScreenInterface.h>
#include "JoystickGaugePosition.h"

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

        bool pointerIsVisible = false;
        JoystickGaugePosition pointerPosition;

        ScreenInterface* screen;

        long readX();
        long readY();

        void drawScope(int centerX, int centerY);

        void drawPointer(int pointerX, int pointerY);
        void updatePointer(int pointerX, int pointerY);
        void removeVisiblePointer();
        bool pointerPositionHasChanged(int pointerX, int pointerY);

        void displayReadouts(int xReadout, int yReadout);

        long readoutToRelativePosition(long readout);
        char* toFormat(char* format, long number);
        void message(char* text);
    public:
        JoystickGauge(unsigned int x, unsigned int y, 
            unsigned int vrxPin, unsigned int vryPin, 
            ScreenInterface* screen) : 
            x(x), y(y), vrxPin(vrxPin), vryPin(vryPin), 
            screen(screen) {};

        void begin();
        void update();
};
