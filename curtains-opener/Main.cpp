#include <Arduino.h>
//#include <LinkedList.h>
//#include <functional-vlpp.h>
#include <Base.h>
#include <BlinkingLedButton.cpp>

//#include <Led.cpp>
//#include <Button.cpp>
//#include <TrafficLight.cpp>
static ButtonFSM* light;
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
//    Serial.flush(); //flush all previous received and transmitted data
//    while(!Serial.available()) ;
//    eventBus = new EventBus(Event::__TOTAL);
//    light = new ButtonFSM();
//    button.onClick([]() -> void {led.on();});
}

void loop() {
    Component::updateAll();
}
