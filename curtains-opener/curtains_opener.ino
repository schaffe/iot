#include <Arduino.h>
#include <BlinkingLedButton.cpp>
#include <functional-vlpp.h>

//#include <Led.cpp>
//#include <Button.cpp>
//#include <TrafficLight.cpp>
static ButtonFSM light;
//static Led led(13);
//static Button button(8);
//static InputPin button(8);
//static TrafficLight trafficLight;

void setup() {
//    pinMode(8, INPUT_PULLUP);
//    pinMode(13, OUTPUT);

//    btn.setup();
//    led.setup();
//    Serial.begin(9600);
//    button.onClick([]() -> void {led.on();});
}

void loop() {
//    button.loop();
//
//    if (button.read())
//        led.on();
//    else
//        led.off();
//    Serial.println("test");
    light.loop();
}
