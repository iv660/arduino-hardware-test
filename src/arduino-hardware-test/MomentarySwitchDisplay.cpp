#include <Arduino.h>
#include "MomentarySwitchDisplay.h"

bool MomentarySwitchDisplay::isDown()
{
    if (digitalRead(pin) == LOW) {
        return true;
    }

    return false;
}

bool MomentarySwitchDisplay::stateHasChanged()
{
    if (isDown() != isDownState) {
        return true;
    }

    return false;
}

void MomentarySwitchDisplay::drawFootprint()
{
    screen->drawCircle(x, y, radius, color);
}

void MomentarySwitchDisplay::drawIndicator()
{
    if (isDown()) {
        drawActiveIndicator();
    } else {
        drawInactiveIndicator();
    }
}

void MomentarySwitchDisplay::drawActiveIndicator()
{
    screen->fillCircle(x, y, getIndicatorRadius(), color);
}

void MomentarySwitchDisplay::drawInactiveIndicator()
{
    screen->fillCircle(x, y, getIndicatorRadius(), backgroundColor);
    screen->drawCircle(x, y, getIndicatorRadius(), color);
}

unsigned int MomentarySwitchDisplay::getIndicatorRadius()
{
    return radius - 2;
}

void MomentarySwitchDisplay::begin()
{
    pinMode(pin, INPUT_PULLUP);
    drawFootprint();
    drawIndicator();
}

void MomentarySwitchDisplay::update()
{
    drawFootprint();

    if (!stateHasChanged()) {    
        return;
    }

    drawIndicator();

    isDownState = isDown();
}
