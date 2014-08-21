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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softTone.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "scale.h"
#include "song.h"


const int floppyConv = 31400000;

int freq[14][12];

int endTime[] = {0,0,0};
int pauseTime[] = {0,0,0};
int note_number[] = {-1,-1,-1};
int dir[] = {0,0,0};
int pause_a[] = {0,0,0};

int init()
{
    if (wiringPiSetup() == -1)
    {
        printf("Failed to initialize wiringPi\n");
        return 1;
    }

    for (int i = 0; i<devices; i++)
    {
        if (is_floppy[i])
        {
            pinMode(pins[i][0], OUTPUT);
            pinMode(pins[i][1], OUTPUT);

        }
        else
        {
            pinMode(pins[i][0], OUTPUT);
        }

    }

    for (int octave = -3; octave < 9; octave++) {
        for (int note = 0; note < 12; note++) {
            double a = pow((double) 2,(double) octave);
            double b = pow((double) 1.059463,(double) note);
            freq[octave+3][note] = (275*a*b)/10;
        }
    }

    return 0;
}



void playMusic()
{

    int a;
    int* song;

    int i;

    for (int i = 0; i<devices; i++)
    {
        if (is_floppy[i])
        {
            digitalWrite(pins[i][0], 1);
            digitalWrite(pins[i][1], HIGH);
            digitalWrite(pins[i][1], LOW);
        }
        else
        {
            softToneCreate(pins[i][0]);
        }

    }

    i=-1;

    while (1)
    {
        for (i = 0; i<devices; i++)
        {
            if (is_floppy[i])
            {
                if (millis() >= endTime[i])
                {
                    note_number[i] = note_number[i]+1;
                    a = note_number[i];

                    song = getMusic(i, a);

                    if (song[0] != -1)
                    {
                        pause_a[i] = (floppyConv / (freq[song[1]+3+changes[i]][song[0]]))/100;

                        pauseTime[i] = micros() + pause_a[i];
                    }
                    else
                    {
                        pauseTime[i] = INT_MAX;
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
                    digitalWrite(pins[i][1], HIGH);
                    digitalWrite(pins[i][1], LOW);
                }


            }
           else
           {
                if (millis() >= endTime[i])
                {

                    a = note_number[i];

                    int* song = getMusic(i, a);

                    softToneWrite (pins[i][0], 0);
                    note_number[i] = note_number[i]+1;

                    softToneWrite (pins[i][0], (freq[song[1]+3+changes[i]][song[0]]));

                    endTime[i] = millis() + song[2];
                }
           }
        }

    }

}


int main()
{
    if (init() != 0)
    {
        printf("init failed - Exiting\n");
        return 1;
    }

    playMusic();


    return 0;
}
