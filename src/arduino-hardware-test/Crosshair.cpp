#include "Crosshair.h"

void Crosshair::renderCrosshairOnScreen(unsigned long x, unsigned long y, unsigned int color, ScreenInterface *screen)
{
    screen->drawLine(x - size / 2, y, x + size / 2, y, color);
    screen->drawLine(x, y - size / 2, x, y + size / 2, color);
    screen->drawPixel(x, y, color);
}

void Crosshair::renderOn(ScreenInterface *screen)
{
    renderCrosshairOnScreen(x, y, color, screen);
}

void Crosshair::removeFrom(ScreenInterface *screen)
{
    renderCrosshairOnScreen(x, y, backgroundColor, screen);
}
