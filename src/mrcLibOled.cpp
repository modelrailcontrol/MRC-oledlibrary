// ==================================================================================================
//
//  MRC Library OLED
//  Copyright (C) 2020  Peter Kindström
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Last modified: 2020-12-13
//  Compiled with: Arduino Uno
//
//  Uses the following card definitions:
//   -
//
//  Uses the following libraries:
//   U8g2 by oliver               - v2.28.8 - https://github.com/olikraus/u8g2
//
// ==================================================================================================
#include "Arduino.h"
#include "mrcLibOled.h"

// --------------------------------------------------------------------------------------------------
// Make new instance of u8g2 class
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


// --------------------------------------------------------------------------------------------------
//  Main class function
// --------------------------------------------------------------------------------------------------
//  type:
//    1 = Left two way turnout
//    2 = Right two way turnout
//    3 = Three way turnout
//    4 = Y turnout
//    5 = Single cross turnout
//    6 = Double cross turnout
//  dir:
//    0 -> eastbound turnout
//    1 -> westbound turnout
// --------------------------------------------------------------------------------------------------
mrcLibOled::mrcLibOled(int type, int dir) {
  // Set OLED screen type; 1 = 128x64
  oledType = type;

  // Set direction of the OLED screen; 
  oledDirection = dir;

  if (oledDirection == 0) {
    turnoutX=10;
    turnoutY=35;
  } else {
    turnoutX=10;
    turnoutY=30;
  };


  // Set to unknown turnout type
  turnoutType = 0;

//  init();
}

// --------------------------------------------------------------------------------------------------
//  Not in use (yet?)
// --------------------------------------------------------------------------------------------------
void mrcLibOled::init() {
}

// --------------------------------------------------------------------------------------------------
//  Public: Regulary update check
// --------------------------------------------------------------------------------------------------
void mrcLibOled::loop() {

  // Refresh screen on request
  if (oledRefresh == 1) {
    u8g2.begin();
    u8g2.firstPage();
    do {
      // Show title
      if (titleShow == 1) { showTitle(); };

      // Show MQTT status
      if (mqttShow == 1) { showMqtt(); }

      // Show moving indicator
      if (movingShow == 1) { showMoving(); }

      // Left turnout
      // Right turnout
      // Y turnout

      // Threeway turnout
      if (turnoutType == 3) {
        threeEastOutline();
        if (turnoutDir == "CLOSED")       { threeEastClosed(); }
        else if (turnoutDir == "LEFT")    { threeEastLeft(); }
        else if (turnoutDir == "RIGHT")   { threeEastRight(); }
        else if (turnoutDir == "UNKNOWN") { threeEastUnknown(); }
      }

      // Single cross turnout
      // Double cross turnout

    } while ( u8g2.nextPage() );
    u8g2.sendBuffer();

    // Refresh done, wait for next request
    oledRefresh = 0;
  }

}

// --------------------------------------------------------------------------------------------------
//  Public: Set turnout type
// --------------------------------------------------------------------------------------------------
//  1 = Left turnout
//  2 = Right turnout
//  3 = Threeway turnout
//  4 = Y turnout
//  5 = Single cross turnout
//  6 = Double cross turnout
// --------------------------------------------------------------------------------------------------
void mrcLibOled::setTurnoutType(int type) {
  turnoutType = type;
}

// --------------------------------------------------------------------------------------------------
//  Public: Set turnout direction
// --------------------------------------------------------------------------------------------------
//  Twoway: CLOSED, THROWN
//  Threeway: CLOSED, LEFT, RIGHT
//  Y: LEFT, RIGHT
//  Single cross: 
//  Double cross: 
// --------------------------------------------------------------------------------------------------
void mrcLibOled::setTurnoutDirection(String direction) {
  turnoutDir = direction;

  // Update screen
  oledRefresh = 1;
}

// --------------------------------------------------------------------------------------------------
//  Public: Set turnout moving symbol on/off
// --------------------------------------------------------------------------------------------------
//  General: STOP
//  Twoway: CLOSED, THROWN
//  Threeway: CLOSED, LEFT, RIGHT
//  Y: LEFT, RIGHT
//  Single cross: 
//  Double cross: 
// --------------------------------------------------------------------------------------------------
void mrcLibOled::setTurnoutMoveTo(String direction) {
  turnoutMoving = direction;

  // Check if we should show moving symbol
  if (turnoutMoving == "STOP") {
    movingShow = 0;
  } else {
    movingShow = 1;
  }

  // Update screen
  oledRefresh = 1;
}

// --------------------------------------------------------------------------------------------------
//  Public: Set MQTT status symbol on/off
// --------------------------------------------------------------------------------------------------
//  0 = off
//  1 = on
// --------------------------------------------------------------------------------------------------
void mrcLibOled::setMqttStatus(boolean show){
  mqttShow = show;

  // Update screen
  oledRefresh = 1;
}

// --------------------------------------------------------------------------------------------------
//  Public: Set title text, font and on/off
// --------------------------------------------------------------------------------------------------
//  text:
//    Any text string between 15 and 20 characters (only numbers and us/english characters at the moment)
//  font:
//     8 =  8 px fontsize
//     9 =  9 px fontsize
//    10 = 10 px fontsize
//  show:
//    0 = off
//    1 = on
// --------------------------------------------------------------------------------------------------
void mrcLibOled::setTitleText(const char * text, int font, boolean show) {
  titleText = text;
  titleFont = font;
  titleShow = show;

  // Set main X and Y coordinates
  if (titleShow == 1) {
    turnoutX=10;
    turnoutY=35;
  } else {
    turnoutX=10;
    turnoutY=30;
  };

  // Update screen
  oledRefresh = 1;
}

// --------------------------------------------------------------------------------------------------
//  Private: Shows a text in the upper left corner
// --------------------------------------------------------------------------------------------------
void mrcLibOled::showTitle() {
  int titleX;
  int titleY;

  // Check which font to use
  if (titleFont == 8) {
    u8g2.setFont(u8g2_font_t0_12_mr);     // 8px restricted font, type UW ttyp0
    titleX = 1; titleY = 8;               // Set screen coordinates
  } else if (titleFont ==9 ) {
    u8g2.setFont(u8g2_font_t0_13_mr);     // 9px restricted font, type UW ttyp0
    titleX = 1; titleY = 9;               // Set screen coordinates
  } else if (titleFont ==10 ) {
    u8g2.setFont(u8g2_font_t0_16_mr);     // 10px restricted font
    titleX = 1; titleY = 10;              // Set screen coordinates
  }

  // Draw symbol
  u8g2.setDrawColor(1);                   // Normal text
  u8g2.drawStr(titleX,titleY,titleText);  // Write something to the internal memory
}

// --------------------------------------------------------------------------------------------------
//  Private: Shows a small wifi symbol in the upper right corner
// --------------------------------------------------------------------------------------------------
void mrcLibOled::showMqtt() {
  int mqttX=122;
  int mqttY=4;

  // Draw symbol
  u8g2.setDrawColor(1);
  u8g2.drawPixel(mqttX,mqttY);                    // Inner circle
  u8g2.drawLine(mqttX+2,mqttY, mqttX+2,mqttY-1);  // Middle circle
  u8g2.drawLine(mqttX,mqttY-2, mqttX+1,mqttY-2);  // Middle circle
  u8g2.drawLine(mqttX+4,mqttY, mqttX+4,mqttY-2);  // Outer circle
  u8g2.drawLine(mqttX,mqttY-4, mqttX+2,mqttY-4);  // Outer circle
  u8g2.drawPixel(mqttX+3,mqttY-3);                // Outer circle

}

// --------------------------------------------------------------------------------------------------
//  Private: Shows a small symbol when turnout is shifting direction
// --------------------------------------------------------------------------------------------------
void mrcLibOled::showMoving() {
  int extraY;
  int extraX;

  // Check in which direction to draw the symbols
  if (oledDirection == 0) {
    // Draw eastbound turnout
    extraX = 104;

    // Set Y coordinate depending on turnout type
    if (turnoutType == 3 && turnoutMoving == "CLOSED") {extraY = 10;}
    if (turnoutType == 3 && turnoutMoving == "RIGHT") {extraY = 29;}
    if (turnoutType == 3 && turnoutMoving == "LEFT") {extraY = -10;}

  } else if (oledDirection == 1) {
    // Draw westbound turnout
  
  }

  // Draw symbol
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(turnoutX+extraX,turnoutY+extraY,0x23f3);

}

// --------------------------------------------------------------------------------------------------
//  Private: Shows an outlined threeway turnout
// --------------------------------------------------------------------------------------------------
void mrcLibOled::threeEastOutline() {

  // Check in which direction to draw the symbols
  if (oledDirection == 0) {
    // Draw eastbound turnout
    u8g2.setDrawColor(1);
  
    // Closed
    u8g2.drawBox(turnoutX,turnoutY, 16,8);
    u8g2.drawLine(turnoutX+29,turnoutY, turnoutX+100,turnoutY);
    u8g2.drawLine(turnoutX+29,turnoutY+7, turnoutX+100,turnoutY+7);

    // Left
    u8g2.drawLine(turnoutX+15,turnoutY-1, turnoutX+57,turnoutY-21);
    u8g2.drawLine(turnoutX+30,turnoutY-1, turnoutX+56,turnoutY-13);
    u8g2.drawLine(turnoutX+56,turnoutY-21, turnoutX+100,turnoutY-21);
    u8g2.drawLine(turnoutX+55,turnoutY-13, turnoutX+100,turnoutY-13);

    // Right
    u8g2.drawLine(turnoutX+15,turnoutY+8, turnoutX+55,turnoutY+28);
    u8g2.drawLine(turnoutX+29,turnoutY+8, turnoutX+56,turnoutY+21);
    u8g2.drawLine(turnoutX+56,turnoutY+21, turnoutX+100,turnoutY+21);
    u8g2.drawLine(turnoutX+55,turnoutY+28, turnoutX+100,turnoutY+28);
  } else if (oledDirection == 1) {
    // Draw westbound turnout
    u8g2.setDrawColor(1);
  }
  
}

// --------------------------------------------------------------------------------------------------
//  Private: Shows a closed threeway turnout
// --------------------------------------------------------------------------------------------------
void mrcLibOled::threeEastClosed() {

  // Check in which direction to draw the symbols
  if (oledDirection == 0) {
    // Draw eastbound turnout
    u8g2.setDrawColor(1);
    u8g2.drawBox(turnoutX+16,turnoutY, 85,8);

  } else if (oledDirection == 1) {
    // Draw westbound turnout
    u8g2.setDrawColor(1);

  }
}

// --------------------------------------------------------------------------------------------------
//  Private: Shows a left threeway turnout
// --------------------------------------------------------------------------------------------------
void mrcLibOled::threeEastLeft() {

  // Check in which direction to draw the symbols
  if (oledDirection == 0) {
    // Draw eastbound turnout
    u8g2.setDrawColor(1);

    // Mot stickspår
    u8g2.drawLine(turnoutX+16,turnoutY-1, turnoutX+58,turnoutY-21);
    u8g2.drawLine(turnoutX+18,turnoutY-1, turnoutX+60,turnoutY-21);
    u8g2.drawLine(turnoutX+20,turnoutY-1, turnoutX+62,turnoutY-21);
    u8g2.drawLine(turnoutX+22,turnoutY-1, turnoutX+64,turnoutY-21);
    u8g2.drawLine(turnoutX+24,turnoutY-1, turnoutX+66,turnoutY-21);
    u8g2.drawLine(turnoutX+26,turnoutY-1, turnoutX+68,turnoutY-21);
    u8g2.drawLine(turnoutX+28,turnoutY-1, turnoutX+70,turnoutY-21);
    u8g2.drawLine(turnoutX+30,turnoutY-1, turnoutX+72,turnoutY-21);

    // Spårkors
    u8g2.drawTriangle(turnoutX+16,turnoutY, turnoutX+16,turnoutY+8, turnoutX+29,turnoutY);

    // Stickspåret
    u8g2.drawBox(turnoutX+58,turnoutY-21, 43,8);

  } else if (oledDirection == 1) {
    // Draw westbound turnout
    u8g2.setDrawColor(1);
  
  }
}

// --------------------------------------------------------------------------------------------------
//  Private: Shows a right threeway turnout
// --------------------------------------------------------------------------------------------------
void mrcLibOled::threeEastRight() {

  // Check in which direction to draw the symbols
  if (oledDirection == 0) {
    // Draw eastbound turnout
    u8g2.setDrawColor(1);

    // Mot stickspår, fyllning
    u8g2.drawLine(turnoutX+17,turnoutY+8, turnoutX+57,turnoutY+28);
    u8g2.drawLine(turnoutX+19,turnoutY+8, turnoutX+59,turnoutY+28);
    u8g2.drawLine(turnoutX+21,turnoutY+8, turnoutX+61,turnoutY+28);
    u8g2.drawLine(turnoutX+23,turnoutY+8, turnoutX+63,turnoutY+28);
    u8g2.drawLine(turnoutX+25,turnoutY+8, turnoutX+65,turnoutY+28);
    u8g2.drawLine(turnoutX+27,turnoutY+8, turnoutX+67,turnoutY+28);

    // Spårkort, fyllning
    u8g2.drawTriangle(turnoutX+16,turnoutY, turnoutX+30,turnoutY+8, turnoutX+16,turnoutY+8);

    // Stickspår, fyllning
    u8g2.drawBox(turnoutX+58,turnoutY+21, 43,8);

  } else if (oledDirection == 1) {
    // Draw westbound turnout
    u8g2.setDrawColor(1);
  
  }
}

// --------------------------------------------------------------------------------------------------
//  Private: Shows an unknown threeway turnout
// --------------------------------------------------------------------------------------------------
void mrcLibOled::threeEastUnknown() {

    // Check in which direction to draw the symbols
  if (oledDirection == 0) {
    // Draw eastbound turnout
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_unifont_t_symbols);
    u8g2.drawGlyph(turnoutX+110,turnoutY-2,0x003f);   // 0x003f = "?" character
    u8g2.drawGlyph(turnoutX+110,turnoutY+20,0x003f);  // 0x003f = "?" character

  } else if (oledDirection == 1) {
    // Draw westbound turnout
    u8g2.setDrawColor(1);
  
  }
}