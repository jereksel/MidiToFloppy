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
#include "scale.h"
#include <stdbool.h>
#include <math.h>

// pin 11 = wiringPi Pin 0. Use this for motor direction.
#define dirPin 0
// pin 12 supports pwm mode but it turns out I didn't need pwm mode in the end!
// pin 12 = wiringPi Pin 1. Use this for stepper motor.
#define stepPin  1
#define buzzerPin  2


#define stepPin_2 3
#define dirPin_2  4

// Define an octave with naturals and sharps (Zz = rest)
//enum { Cn, Cs, Dn, Ds, En, Fn, Fs, Gn, Gs, An, As, Bn, Zz };

// Define another one with flats and remaining sharps
//enum { Bs, Df, Dn2, Ef, En2, Es, Gf, Gn2, Af, An2, Bf, Bn2, Zz2 };

/**
 * Frequencies in hundredths of Hz, e.g. middle A = 44000
 * 4 Octaves with 12 notes per octave, i.e. C to B
 */
/*
const long int freq[8][13] = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0},
   {13081,13859,14683,15556,16481,17461,18500,19600,20765,22000,23308,24694,0 },
   {26163,27718,29366,31113,32963,34923,36999,39200,41530,44000,46616,49388,0 },
   {52325,55437,58733,62225,65925,69846,73999,78399,83061,88000,93233,98777,0 },
   {104650,110873,117466,124451,131851,139691,147998,156798,166122,176000,186466,197553,0},
   {209300,221700,234900,248900,263700,279400,296000,313600,332200,352000,372900,395100,0}
};
*/
/**
 * Frequency (in Hz) is converted to Floppy Delay using the formula:
 *   314000 / frequency = floppy delay
 * so middle A = 314000 / 440 = 714
 *
 * Lowest realistic note is delay = 1550
 * Highest realistic note is delay = 210
 */
const int floppyConv = 31400000;

// Calculate all our floppy delays at the start
//int floppyDelay[8][13];

int freq[14][12];



// Song1 is the C major scale (note, octave, length)

int music[][3] = {{ZZ, 0, 1538}, {NOTE_G, 2, 320}, {ZZ, 0, 256}, {NOTE_C, 3, 188}, {ZZ, 0, 772}, {NOTE_GS, 2, 320}, {ZZ, 0, 256}, {NOTE_AS, 2, 188}, {ZZ, 0, 2500}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 284}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 284}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 388}, {NOTE_F, 2, 320}, {ZZ, 0, 448}, {NOTE_G, 2, 320}, {ZZ, 0, 256}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_D, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 196}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 672}, {ZZ, 0, 3168}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_D, 2, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 3076}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 1440}, {ZZ, 0, 96}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_E, 0, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_E, 0, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_F, 0, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 0, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 0, 92}, {ZZ, 0, 4}, {NOTE_D, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_B, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 2, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_B, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 0, 92}, {ZZ, 0, 4}, {NOTE_B, 0, 92}, {ZZ, 0, 4}, {NOTE_D, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_B, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 2, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_E, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_E, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 1, 1440}, {ZZ, 0, 96}, {NOTE_C, 1, 320}, {ZZ, 0, 64}, {NOTE_D, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 1, 672}, {ZZ, 0, 96}, {NOTE_D, 1, 672}, {ZZ, 0, 3168}, {NOTE_C, 1, 320}, {ZZ, 0, 64}, {NOTE_D, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 0, 188}, {ZZ, 0, 4}, {NOTE_G, 0, 320}, {ZZ, 0, 64}, {NOTE_F, 0, 188}, {ZZ, 0, 4}, {NOTE_G, 0, 1440}, {ZZ, 0, 96}, {NOTE_G, 2, 320}, {ZZ, 0, 256}, {NOTE_C, 3, 188}, {ZZ, 0, 772}, {NOTE_GS, 2, 320}, {ZZ, 0, 256}, {NOTE_AS, 2, 188}, {ZZ, 0, 2500}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 284}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 196}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 284}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 388}, {NOTE_F, 2, 320}, {ZZ, 0, 448}, {NOTE_G, 2, 320}, {ZZ, 0, 256}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 196}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_D, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 196}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 672}, {ZZ, 0, 3168}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_D, 2, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 3076}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 1440}, {ZZ, 0, 96}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_E, 0, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_E, 0, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 0, 92}, {ZZ, 0, 4}, {NOTE_F, 0, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 0, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 92}, {ZZ, 0, 4}, {NOTE_GS, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 0, 92}, {ZZ, 0, 4}, {NOTE_D, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_B, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 2, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_B, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 0, 92}, {ZZ, 0, 4}, {NOTE_B, 0, 92}, {ZZ, 0, 4}, {NOTE_D, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_B, 1, 92}, {ZZ, 0, 4}, {NOTE_D, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 2, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_E, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_E, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 1, 1440}, {ZZ, 0, 96}, {NOTE_C, 1, 320}, {ZZ, 0, 64}, {NOTE_D, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 1, 672}, {ZZ, 0, 96}, {NOTE_D, 1, 672}, {ZZ, 0, 3168}, {NOTE_C, 1, 320}, {ZZ, 0, 64}, {NOTE_D, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 0, 188}, {ZZ, 0, 4}, {NOTE_G, 0, 320}, {ZZ, 0, 64}, {NOTE_F, 0, 188}, {ZZ, 0, 4}, {NOTE_G, 0, 1440}};

int music_2[][3] = {{ZZ, 0, 194}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 2, 188}, {ZZ, 0, 196}, {NOTE_C, 3, 320}, {ZZ, 0, 64}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 2, 320}, {ZZ, 0, 64}, {NOTE_GS, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_GS, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 2, 1632}, {ZZ, 0, 96}, {NOTE_G, 2, 672}, {ZZ, 0, 96}, {NOTE_AS, 2, 320}, {ZZ, 0, 64}, {NOTE_F, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 196}, {NOTE_G, 1, 512}, {ZZ, 0, 64}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 196}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_F, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 672}, {ZZ, 0, 96}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 3, 320}, {ZZ, 0, 64}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 320}, {ZZ, 0, 64}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 672}, {ZZ, 0, 96}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 196}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_D, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 672}, {ZZ, 0, 96}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 2, 320}, {ZZ, 0, 64}, {NOTE_DS, 2, 320}, {ZZ, 0, 64}, {NOTE_D, 2, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 448}, {NOTE_C, 2, 320}, {ZZ, 0, 448}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 2, 188}, {ZZ, 0, 196}, {NOTE_C, 3, 320}, {ZZ, 0, 64}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 2, 320}, {ZZ, 0, 64}, {NOTE_GS, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_GS, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 2, 1632}, {ZZ, 0, 96}, {NOTE_G, 2, 672}, {ZZ, 0, 96}, {NOTE_AS, 2, 320}, {ZZ, 0, 64}, {NOTE_F, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_F, 1, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 196}, {NOTE_G, 1, 512}, {ZZ, 0, 64}, {NOTE_G, 1, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 196}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_F, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 672}, {ZZ, 0, 96}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 3, 320}, {ZZ, 0, 64}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_G, 2, 320}, {ZZ, 0, 64}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_DS, 2, 92}, {ZZ, 0, 4}, {NOTE_F, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 2, 92}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 672}, {ZZ, 0, 96}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_AS, 1, 92}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 196}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_DS, 2, 188}, {ZZ, 0, 4}, {NOTE_D, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 672}, {ZZ, 0, 96}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_DS, 2, 320}, {ZZ, 0, 64}, {NOTE_DS, 2, 320}, {ZZ, 0, 64}, {NOTE_D, 2, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_G, 1, 188}, {ZZ, 0, 4}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_E, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 448}, {NOTE_C, 2, 320}, {ZZ, 0, 448}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_F, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_G, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}, {ZZ, 0, 4}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 284}, {ZZ, 0, 4}, {NOTE_AS, 1, 188}, {ZZ, 0, 4}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_GS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_AS, 1, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 320}, {ZZ, 0, 64}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 284}, {ZZ, 0, 4}, {NOTE_C, 2, 188}};

int music_3[][3] = {{ZZ, 0, 1538}, {NOTE_C, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 196}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_C, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 188}, {ZZ, 0, 4}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 5, 1632}, {ZZ, 0, 96}, {NOTE_AS, 5, 672}, {ZZ, 0, 96}, {NOTE_C, 6, 320}, {ZZ, 0, 5248}, {NOTE_G, 5, 92}, {ZZ, 0, 4}, {NOTE_AS, 5, 92}, {ZZ, 0, 4}, {NOTE_C, 6, 188}, {ZZ, 0, 4}, {NOTE_AS, 5, 188}, {ZZ, 0, 4}, {NOTE_F, 6, 92}, {ZZ, 0, 4}, {NOTE_DS, 6, 92}, {ZZ, 0, 4}, {NOTE_C, 6, 188}, {ZZ, 0, 4}, {NOTE_F, 6, 320}, {ZZ, 0, 64}, {NOTE_DS, 6, 188}, {ZZ, 0, 4}, {NOTE_AS, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 6, 320}, {ZZ, 0, 64}, {NOTE_F, 6, 92}, {ZZ, 0, 4}, {NOTE_DS, 6, 92}, {ZZ, 0, 4}, {NOTE_F, 6, 92}, {ZZ, 0, 4}, {NOTE_G, 6, 92}, {ZZ, 0, 4}, {NOTE_G, 5, 188}, {ZZ, 0, 4}, {NOTE_AS, 5, 188}, {ZZ, 0, 4}, {NOTE_C, 6, 672}, {ZZ, 0, 3168}, {NOTE_C, 5, 672}, {ZZ, 0, 96}, {NOTE_G, 5, 672}, {ZZ, 0, 96}, {NOTE_F, 5, 320}, {ZZ, 0, 64}, {NOTE_DS, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 196}, {NOTE_AS, 4, 512}, {ZZ, 0, 64}, {NOTE_C, 5, 320}, {ZZ, 0, 64}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_D, 5, 320}, {ZZ, 0, 64}, {NOTE_AS, 4, 320}, {ZZ, 0, 64}, {NOTE_G, 4, 1440}, {ZZ, 0, 96}, {NOTE_C, 5, 672}, {ZZ, 0, 96}, {NOTE_G, 5, 672}, {ZZ, 0, 96}, {NOTE_F, 5, 672}, {ZZ, 0, 96}, {NOTE_GS, 5, 284}, {ZZ, 0, 4}, {NOTE_G, 5, 284}, {ZZ, 0, 4}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 320}, {ZZ, 0, 64}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_D, 5, 320}, {ZZ, 0, 64}, {NOTE_C, 5, 1440}, {ZZ, 0, 96}, {NOTE_D, 5, 672}, {ZZ, 0, 96}, {NOTE_F, 5, 672}, {ZZ, 0, 96}, {NOTE_DS, 5, 672}, {ZZ, 0, 96}, {NOTE_G, 5, 672}, {ZZ, 0, 96}, {NOTE_GS, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 320}, {ZZ, 0, 64}, {NOTE_GS, 5, 320}, {ZZ, 0, 64}, {NOTE_AS, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 1440}, {ZZ, 0, 96}, {NOTE_C, 6, 320}, {ZZ, 0, 448}, {NOTE_C, 6, 320}, {ZZ, 0, 448}, {NOTE_AS, 5, 320}, {ZZ, 0, 64}, {NOTE_GS, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 5, 188}, {ZZ, 0, 196}, {NOTE_F, 5, 512}, {ZZ, 0, 64}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 320}, {ZZ, 0, 64}, {NOTE_GS, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 1440}, {ZZ, 0, 96}, {NOTE_C, 5, 672}, {ZZ, 0, 96}, {NOTE_DS, 5, 512}, {ZZ, 0, 64}, {NOTE_C, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 188}, {ZZ, 0, 196}, {NOTE_F, 5, 864}, {ZZ, 0, 96}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 4}, {NOTE_AS, 4, 320}, {ZZ, 0, 64}, {NOTE_G, 4, 188}, {ZZ, 0, 4}, {NOTE_C, 5, 1440}, {ZZ, 0, 96}, {NOTE_C, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 196}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_C, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 188}, {ZZ, 0, 4}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 5, 1632}, {ZZ, 0, 96}, {NOTE_AS, 5, 672}, {ZZ, 0, 96}, {NOTE_C, 6, 320}, {ZZ, 0, 5248}, {NOTE_G, 5, 92}, {ZZ, 0, 4}, {NOTE_AS, 5, 92}, {ZZ, 0, 4}, {NOTE_C, 6, 188}, {ZZ, 0, 4}, {NOTE_AS, 5, 188}, {ZZ, 0, 4}, {NOTE_F, 6, 92}, {ZZ, 0, 4}, {NOTE_DS, 6, 92}, {ZZ, 0, 4}, {NOTE_C, 6, 188}, {ZZ, 0, 4}, {NOTE_F, 6, 320}, {ZZ, 0, 64}, {NOTE_DS, 6, 188}, {ZZ, 0, 4}, {NOTE_AS, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 6, 320}, {ZZ, 0, 64}, {NOTE_F, 6, 92}, {ZZ, 0, 4}, {NOTE_DS, 6, 92}, {ZZ, 0, 4}, {NOTE_F, 6, 92}, {ZZ, 0, 4}, {NOTE_G, 6, 92}, {ZZ, 0, 4}, {NOTE_G, 5, 188}, {ZZ, 0, 4}, {NOTE_AS, 5, 188}, {ZZ, 0, 4}, {NOTE_C, 6, 672}, {ZZ, 0, 3168}, {NOTE_C, 5, 672}, {ZZ, 0, 96}, {NOTE_G, 5, 672}, {ZZ, 0, 96}, {NOTE_F, 5, 320}, {ZZ, 0, 64}, {NOTE_DS, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 196}, {NOTE_AS, 4, 512}, {ZZ, 0, 64}, {NOTE_C, 5, 320}, {ZZ, 0, 64}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_D, 5, 320}, {ZZ, 0, 64}, {NOTE_AS, 4, 320}, {ZZ, 0, 64}, {NOTE_G, 4, 1440}, {ZZ, 0, 96}, {NOTE_C, 5, 672}, {ZZ, 0, 96}, {NOTE_G, 5, 672}, {ZZ, 0, 96}, {NOTE_F, 5, 672}, {ZZ, 0, 96}, {NOTE_GS, 5, 284}, {ZZ, 0, 4}, {NOTE_G, 5, 284}, {ZZ, 0, 4}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 320}, {ZZ, 0, 64}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_D, 5, 320}, {ZZ, 0, 64}, {NOTE_C, 5, 1440}, {ZZ, 0, 96}, {NOTE_D, 5, 672}, {ZZ, 0, 96}, {NOTE_F, 5, 672}, {ZZ, 0, 96}, {NOTE_DS, 5, 672}, {ZZ, 0, 96}, {NOTE_G, 5, 672}, {ZZ, 0, 96}, {NOTE_GS, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 320}, {ZZ, 0, 64}, {NOTE_GS, 5, 320}, {ZZ, 0, 64}, {NOTE_AS, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 1440}, {ZZ, 0, 96}, {NOTE_C, 6, 320}, {ZZ, 0, 448}, {NOTE_C, 6, 320}, {ZZ, 0, 448}, {NOTE_AS, 5, 320}, {ZZ, 0, 64}, {NOTE_GS, 5, 188}, {ZZ, 0, 4}, {NOTE_G, 5, 188}, {ZZ, 0, 196}, {NOTE_F, 5, 512}, {ZZ, 0, 64}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 320}, {ZZ, 0, 64}, {NOTE_GS, 5, 320}, {ZZ, 0, 64}, {NOTE_G, 5, 1440}, {ZZ, 0, 96}, {NOTE_C, 5, 672}, {ZZ, 0, 96}, {NOTE_DS, 5, 512}, {ZZ, 0, 64}, {NOTE_C, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 188}, {ZZ, 0, 196}, {NOTE_F, 5, 864}, {ZZ, 0, 96}, {NOTE_DS, 5, 320}, {ZZ, 0, 64}, {NOTE_F, 5, 188}, {ZZ, 0, 4}, {NOTE_DS, 5, 188}, {ZZ, 0, 4}, {NOTE_D, 5, 188}, {ZZ, 0, 4}, {NOTE_AS, 4, 320}, {ZZ, 0, 64}, {NOTE_G, 4, 188}, {ZZ, 0, 4}, {NOTE_C, 5, 1440}};

bool is_floppy[3] = {true, true, true};

int pins[][2] = {{dirPin, stepPin},{dirPin_2, stepPin_2},{6,5}};

int changes[] = {-1,-1,-4};

int devices = 3;

int endTime[] = {0,0,0};
int pauseTime[] = {0,0,0};
int note_number[] = {-1,-1,-1};
int dir[] = {0,0,0};
int pause_a[] = {0,0,0};


int * getMusic(int i, int number)
{
    if (i == 0) {
        return music[number];
    } else if (i == 1) {
        return music_2[number];
    } else if (i == 2) {
        return music_3[number];
    }

    return NULL;
}

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

//    softToneCreate(buzzerPin);

    printf("TEST");

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

                    softToneWrite (buzzerPin, 0);
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
