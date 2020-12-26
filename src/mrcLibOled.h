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
//  Last modified: 2020-12-19
//  Compiled with: Arduino Uno
//
//  Uses the following card definitions:
//   -
//
//  Uses the following libraries:
//   U8g2 by oliver               - v2.28.8 - https://github.com/olikraus/u8g2
//
// ==================================================================================================
#include <Arduino.h>
#include <U8g2lib.h>

// --------------------------------------------------------------------------------------------------
//  Ensure "mrcLibOled.h" is only included/compiled once
// --------------------------------------------------------------------------------------------------
#ifndef mrcLibOled_h
#define mrcLibOled_h

// --------------------------------------------------------------------------------------------------
// Use SPI or I2C depending on choosen card
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// --------------------------------------------------------------------------------------------------
// Make the constant globally avaliable
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

// --------------------------------------------------------------------------------------------------
//  OLED class definition
// --------------------------------------------------------------------------------------------------
class mrcLibOled {

  // ------------------------------------------------------------------------------------------------
  // Variables and functions possible to use outside the class
  public:
    mrcLibOled(int type, int dir);
    void loop();
    void init();
    void setTitleText(const char * text, int font, boolean show);
    void setMqttStatus(boolean show);
    void setTurnoutType(int type);
    void setTurnoutDirection(String direction);
    void setTurnoutMoveTo(String direction);

  // ------------------------------------------------------------------------------------------------
  // Variables and functions only used inside the class
  private:
    int turnoutX;             // X coordinate to start drawing turnout symbol
    int turnoutY;             // Y coordinate to start drawing turnout symbol
    int turnoutType;          // Type of turnout
    String turnoutDir;        // Turnout direction
    String turnoutMoving;     // Where turnout is moving

    int oledType;             // Type of OLED screen
    int oledRefresh;          // Indicate need to refresh screen
    int oledDirection;        // Direction of OLED screen
 
    void showTitle();
    const char * titleText;
    int titleFont;
    boolean titleShow = 0;    // Default is not to show the title

    void showMqtt();
    boolean mqttShow;

    void showMoving();
    boolean movingShow;

    void threeEastOutline();
    void threeEastClosed();
    void threeEastLeft();
    void threeEastRight();
    void threeEastUnknown();

};

#endif