#include <Arduino.h>
#include <mrcLibOled.h>

// Usage: oledScreen (int Type, int Direction)
mrcLibOled oledScreen(1,0);

void setup() {
  // Usage: setTitleText(const char * Title, int Fontsize, boolean Showtitle)
  oledScreen.setTitleText("SJ10", 10, 1);

  // Usage: setTurnoutType(int Type)
  oledScreen.setTurnoutType(3);

  oledScreen.setMqttStatus(1);

  oledScreen.setTurnoutDirection("UNKNOWN");
  oledScreen.loop();
  delay(10000);
}

void loop() {

  // Usage: setTurnoutMoveTo(String Direction)
  oledScreen.setTurnoutMoveTo("STOP");
  // Usage: setTurnoutDirection(String Direction)
  oledScreen.setTurnoutDirection("RIGHT");
  // Usage: loop()
  oledScreen.loop();
  delay(5000);

  oledScreen.setTurnoutMoveTo("CLOSED");
  oledScreen.loop();
  delay(3000);

  oledScreen.setTurnoutMoveTo("STOP");
  oledScreen.setTurnoutDirection("CLOSED");
  oledScreen.loop();
  delay(5000);

  oledScreen.setTurnoutMoveTo("LEFT");
  oledScreen.loop();
  delay(3000);

  oledScreen.setTurnoutMoveTo("STOP");
  oledScreen.setTurnoutDirection("LEFT");
  oledScreen.loop();
  delay(5000);

  oledScreen.setTurnoutMoveTo("RIGHT");
  oledScreen.loop();
  delay(3000);
 }