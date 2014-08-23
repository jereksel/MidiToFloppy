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

int song[3]={0,0,0};

#include <avr/pgmspace.h>
#include "scale.h"
#include "song.h"
#include <limits.h>


const long floppyConv = 31400000;

const int freq[]PROGMEM = {3,3,3,4,4,4,4,5,5,5,6,6,
    6,7,7,8,8,9,9,10,10,11,12,12,
    13,14,15,16,17,18,19,20,21,23,24,25,
    27,29,30,32,34,36,38,41,43,46,48,51,
    55,58,61,65,69,73,77,82,87,92,97,103,
    110,116,123,130,138,146,155,164,174,184,195,207,
    220,233,246,261,277,293,311,329,349,369,391,415,
    440,466,493,523,554,587,622,659,698,739,783,830,
    880,932,987,1046,1108,1174,1244,1318,1396,1479,1567,1661,
    1760,1864,1975,2093,2217,2349,2489,2637,2793,2959,3135,3322,
    3520,3729,3951,4186,4434,4698,4978,5274,5587,5919,6271,6644,
    7040,7458,7902,8372,8869,9397,9956,10548,11175,11839,12543,13289};


long endTime[devices];
long pauseTime[devices];
int note_number[devices];
int dir[devices];
long pause_a[devices];

int k;

 int a=0;

void setup(void)
{
    Serial.begin(9600);           // set up Serial library at 9600 bps

    Serial.println("test");
    int test = freq[3];
//    Serial.println(test);
    Serial.println("test");
  
    for (int i = 0; i<devices; i++)
    {
        note_number[i] = -1;
        endTime[i] = 0;
        pauseTime[i] = 0;
        dir[i] = 0;
        pause_a[i] = 0;
    }
    
    for (int i = 0; i<devices; i++)
    {
        pinMode(pins[i][0], OUTPUT);
        pinMode(pins[i][1], OUTPUT);
    }
    
     pinMode(2, OUTPUT);
     pinMode(3, OUTPUT);
}


void loop()
{
  
    for (int i = 0; i<devices; i++)
    {
      if (millis() >= endTime[i])
      {
          note_number[i] = note_number[i]+1;
          a = note_number[i];
          getMusic(i, a);
          
          Serial.println(song[0]);
    //      return;
          if (song[0] == 254) {
              shutdown();
          }
          else if (song[0] != 255)
          {

              //int adjustedfreq = pgm_read_byte(&freq[(song[1]+3+changes[i])*12 + song[0]]);
              
              int adjustedfreq = pgm_read_byte(&freq[(song[1]+3+changes[i])*12 + song[0]]);
            
              pause_a[i] = (floppyConv /(adjustedfreq))/100;
              
         //     Serial.println(pause_a[i]);
              
              pauseTime[i] = micros() + pause_a[i];
              
          }
          else
          {
              pauseTime[i] = LONG_MAX;
          }
          endTime[i] = millis() + song[2];
      }
      if (micros() >= pauseTime[i])
      {
        
          if (dir[i] == 0)
            dir[i] = 1;
          else
            dir[i] = 0;
            
          digitalWrite(pins[i][0], dir[i]);
          pauseTime[i] = micros() + pause_a[i];
          
     //     Serial.println(pause_a[i]);
          
          digitalWrite(pins[i][1], HIGH);
          digitalWrite(pins[i][1], LOW);
      }
     
    }
    
    

}

void shutdown()
{
  // add you emergency shutdown code here
  while(1);  // endless loop
}
