#include <Arduino.h>
#include <stdio.h>
#include "JoystickGauge.h"
#include "Crosshair.h"

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
    Crosshair(x + pointerX, y + pointerY)
        .renderOn(screen);

    pointerPosition.x = pointerX;
    pointerPosition.y = pointerY;
    pointerIsVisible = true;
}

void JoystickGauge::updatePointer(int pointerX, int pointerY)
{
    if (pointerIsVisible) {
        removeVisiblePointer();
    }

    drawPointer(pointerX, pointerY);
}

void JoystickGauge::removeVisiblePointer()
{
    Crosshair(x + pointerPosition.x, y + pointerPosition.y)
        .removeFrom(screen);
    pointerIsVisible = false;
}

bool JoystickGauge::pointerPositionHasChanged(int pointerX, int pointerY)
{
    if (pointerX != pointerPosition.x) {
        return true;
    }

    if (pointerY != pointerPosition.y) {
        return true;
    }

    return false;
}

void JoystickGauge::displayReadouts(int xReadout, int yReadout)
{
    // Do not display readouts
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

void JoystickGauge::message(char * text)
{
    screen->textSize(1);
    screen->fill(0, 0, 0);
    screen->stroke(0, 0, 0);
    screen->rect(0, 0, screen->width(), 8);

    screen->stroke(0xFF, 0xFF, 0xFF);
    screen->text(text, 0, 0);
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

    if (!pointerPositionHasChanged(xReadout, yReadout)) {
        return;
    }
    
    drawScope(x, y);
    updatePointer(xReadout, yReadout);
    displayReadouts(xReadout, yReadout);
}
