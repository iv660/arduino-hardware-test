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
MomentarySwitchDisplay buttonA(10, 110, PIN5, 'A', &screen);

GaugeInterface* gauges[] = {&joystickGauge, &buttonA};

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
