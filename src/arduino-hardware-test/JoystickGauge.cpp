#include <Arduino.h>
#include <stdio.h>
#include "JoystickGauge.h"

long JoystickGauge::readX()
{
    long readout = analogRead(vrxPin);

    return readoutToRelativePosition(readout);
}

long JoystickGauge::readY()
{
    long readout = analogRead(vryPin);

    return readoutToRelativePosition(readout);
}

void JoystickGauge::drawScope(int centerX, int centerY)
{
    screen->drawCircle(centerX, centerY, scopeRadius, color);
}

void JoystickGauge::drawPointer(int pointerX, int pointerY)
{
    screen->drawPixel(x + pointerX, y + pointerY, color);
}

void JoystickGauge::displayReadouts(int xReadout, int yReadout)
{
    screen->textSize(1);
    screen->stroke(0xFF, 0xFF, 0xFF);
    screen->text((String(toFormat("%d, ", xReadout)) + String(toFormat("%d", yReadout))).c_str(), 0, 12);
    screen->text((String(toFormat("%d, ", analogRead(vrxPin))) + String(toFormat("%d", analogRead(vryPin)))).c_str(), 0, 0);
}

long JoystickGauge::readoutToRelativePosition(long readout)
{
    static const long readoutUpperRange = 1015;

    return map(readout, 0, readoutUpperRange, -scopeRadius, scopeRadius);
}

char *JoystickGauge::toFormat(char *format, long number)
{
    static char buffer[10];

    sprintf(buffer, format, number);

    return buffer;
}

void JoystickGauge::begin()
{
    pinMode(vrxPin, INPUT);
    pinMode(vryPin, INPUT);
}

void JoystickGauge::update()
{
    long xReadout = readX();
    long yReadout = readY();
    
    drawScope(x, y);
    drawPointer(xReadout, yReadout);
    displayReadouts(xReadout, yReadout);
}
