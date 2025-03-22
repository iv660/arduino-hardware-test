#include <Arduino.h>
#include <Appliance.h>
#include <TFTScreen.h>

#include "JoystickGauge.h"
#include "MomentarySwitchDisplay.h"

#define CS_PIN 10 // пин для подключения CS
#define DC_PIN 8  // пин для подключения A0
#define RST_PIN 9 // пин для подключения reset
#define VRX_PIN A0
#define VRY_PIN A1
#define COLOR_WHITE 0xFFFF


using XC::Hardware::Appliance;
using XC::Hardware::TFTScreen;

Appliance appliance;
TFTScreen screen(CS_PIN, DC_PIN, RST_PIN);

JoystickGauge joystickGauge(80, 64, VRX_PIN, VRY_PIN, &screen);
MomentarySwitchDisplay joystickButton(80, 64, PIN2, 'J', &screen);
MomentarySwitchDisplay pauseButton(120, 20, PIN3, 'P', &screen);
MomentarySwitchDisplay startButton(150, 20, PIN4, 'S', &screen);
MomentarySwitchDisplay buttonA(10, 110, PIN5, 'A', &screen);
MomentarySwitchDisplay buttonB(30, 110, PIN6, 'B', &screen);
MomentarySwitchDisplay buttonC(50, 110, PIN7, 'C', &screen);
MomentarySwitchDisplay buttonD(70, 110, 9, 'D', &screen);

GaugeInterface* gauges[] = {
    &joystickGauge, 
    &joystickButton,
    &pauseButton,
    &startButton,
    &buttonA, 
    &buttonB, 
    &buttonC, 
    &buttonD
};

// Serial.begin(115200);


void setup() 
{
    appliance.screen = &screen;
    appliance.directionSwitch = nullptr;
    appliance.pauseButton = nullptr;

    appliance.screen->begin();
    appliance.screen->background(0, 0, 0);
    appliance.screen->stroke(0xFF, 0xFF, 0xFF);
    appliance.screen->text("Joystick Gauge", 0, 0);
    
    for (auto& gauge: gauges) {
        gauge->begin();
    }
}

void loop() 
{
    for (auto& gauge: gauges) {
        gauge->update();
    }
}
