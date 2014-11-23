/*
 The MIT License (MIT)

 Copyright (c) 2014 Andrzej Ressel (jereksel@gmail.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "song.h"
#include <limits.h>
#include <avr/pgmspace.h>
#include "scale.h"


/* EDIT ONLY THIS */

#define devices_number 1
const int pins[][2] = {{22, 23}};

#include "samurai.h"
#include "lying.h"
#include "king.h"
#include "mortal.h"
#include "sinusoid.h"

Song *songs[] = {new King(), new Mortal(), new Sinusoid()};
/* EDIT ONLY THIS */




#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

bool swagger_bool;
unsigned long swagger_time = 0;

unsigned int song[4] = {
  0, 0, 0, 0
};

const long floppyConv = 31400000;

const int freq[] PROGMEM = {
  3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6,
  6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 12, 12,
  13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 24, 25,
  27, 29, 30, 32, 34, 36, 38, 41, 43, 46, 48, 51,
  55, 58, 61, 65, 69, 73, 77, 82, 87, 92, 97, 103,
  110, 116, 123, 130, 138, 146, 155, 164, 174, 184, 195, 207,
  220, 233, 246, 261, 277, 293, 311, 329, 349, 369, 391, 415,
  440, 466, 493, 523, 554, 587, 622, 659, 698, 739, 783, 830,
  880, 932, 987, 1046, 1108, 1174, 1244, 1318, 1396, 1479, 1567, 1661,
  1760, 1864, 1975, 2093, 2217, 2349, 2489, 2637, 2793, 2959, 3135, 3322,
  3520, 3729, 3951, 4186, 4434, 4698, 4978, 5274, 5587, 5919, 6271, 6644,
  7040, 7458, 7902, 8372, 8869, 9397, 9956, 10548, 11175, 11839, 12543, 13289
};


// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50) return btnRIGHT;
  if (adc_key_in < 195) return btnUP;
  if (adc_key_in < 380) return btnDOWN;
  if (adc_key_in < 555) return btnLEFT;
  if (adc_key_in < 790) return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}


long endTime[devices_number];
long pauseTime[devices_number];
int note_number[devices_number];
int dir[devices_number];
long pause[devices_number];

byte swagger[devices_number];
bool swagger_pin[devices_number];
bool waiting[devices_number];

int index = 0;

int numberOfSongs;

int a = 0;

void setup()
{
  Serial.begin(9600);

  numberOfSongs = sizeof(songs) / sizeof(Song);

  cleandata();

  for (byte i = 0; i < devices_number; i++)
  {
    pinMode(pins[i][0], OUTPUT);
    pinMode(pins[i][1], OUTPUT);
  }

  menu();
}

void cleandata()
{
  swagger_bool = false;
  swagger_time = 0;
  for (byte i = 0; i < devices_number; i++)
  {
    swagger[i] = 0;
    swagger_pin[i] = 1;
    waiting[i] = false;
    note_number[i] = -1;
    endTime[i] = 0;
    pauseTime[i] = 0;
    dir[i] = 0;
    pause[i] = 0;
  }
}

void menu()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Select song");
  lcd.setCursor(0, 1);
  lcd.print(songs[index]->getName());
}


void loop()
{

  lcd.setCursor(0, 1);
  lcd_key = read_LCD_buttons();  // read the buttons

  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnUP:
      {
        index++;

        if (index >= numberOfSongs)
        {
          index = 0;
        }

        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(songs[index]->getName());
        delay(500);
        break;
      }
    case btnDOWN:
      {
        index--;

        if (index < 0)
        {
          index = numberOfSongs - 1;
        }

        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(songs[index]->getName());
        delay(500);
        break;
      }

    case btnSELECT:
      {

        play(songs[index]);

        break;
      }
  }

}

void play(Song *s)
{
  delay(500);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("UP: Toggle swag");
  lcd.setCursor(0, 1);
  lcd.print("DOWN: Stop");

  playsong(s);
  cleandata();
  menu();
}

void reset()
{
  for (byte i = 0; i < devices_number; i++)
  {
    for (byte s = 0; s < 100; s++)
    {
      digitalWrite(pins[i][0], LOW);
      digitalWrite(pins[i][1], HIGH);
      digitalWrite(pins[i][1], LOW);
      delay(5);
    }

    for (byte s = 0; s < 10; s++)
    {
      digitalWrite(pins[i][0], HIGH);
      digitalWrite(pins[i][1], HIGH);
      digitalWrite(pins[i][1], LOW);
      delay(5);
    }
  }
}

void playsong(Song *s)
{
  int device = s->getDevicesNumber();

  int button;
  int adjustedfreq;

  if (device > devices_number)
  {
    return;
  }

  while (1)
  {
    for (int i = 0; i < device; i++)
    {

      button = read_LCD_buttons();

      if (button == btnDOWN)
      {       
        
        return;
      }

      if (button == btnUP && millis() > swagger_time)
      {
        swagger_bool = !swagger_bool;
        swagger_time = millis() + 500;
      }

      if (millis() >= endTime[i])
      {
        note_number[i] = note_number[i] + 1;
        a = note_number[i];
        s->getMusic(i, a, song);

        switch (song[0])
        {
          case ((byte)(-2)) :
            delete s;
            return;
            break;

          case ((byte)(-1)) :
            pauseTime[i] = LONG_MAX;
            break;

          default:
            adjustedfreq = pgm_read_byte(&freq[(song[1] + 3 + song[3]) * 12 + song[0]]);
            pause[i] = (floppyConv / (adjustedfreq)) / 100;
            pauseTime[i] = (micros() + pause[i]);
            if (swagger_bool)
            {
              pauseTime[i] = pauseTime[i] - 2500;
            }
            break;
        }

        endTime[i] = millis() + song[2];
      }
      if (micros() >= pauseTime[i])
      {

        if (swagger_bool)
        {
          if (waiting[i])
          {
            waiting[i] = false;
          }
          else
          {
            digitalWrite(pins[i][0], swagger_pin[i]); // Go in reverse
            digitalWrite(pins[i][1], HIGH);
            digitalWrite(pins[i][1], LOW);

            swagger[i]++;

            if (swagger[i] >= 60)
            {
              swagger[i] = 0;
              swagger_pin[i] = !swagger_pin[i];
            }

            pauseTime[i] = (micros() + 2500);
            waiting[i] = true;
            continue;
          }
        }

        dir[i] = !dir[i];

        digitalWrite(pins[i][0], dir[i]);
        pauseTime[i] = micros() + pause[i];
        if (swagger_bool)
        {
          pauseTime[i] = pauseTime[i] - 2500;
        }
        digitalWrite(pins[i][1], HIGH);
        digitalWrite(pins[i][1], LOW);

      }
    }
  }
}
