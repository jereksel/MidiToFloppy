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


#define ZZ 69

#define NOTE_A  0
#define NOTE_AS 1
#define NOTE_B  2
#define NOTE_C  3
#define NOTE_CS 4
#define NOTE_D  5
#define NOTE_DS 6
#define NOTE_E  7
#define NOTE_F  8
#define NOTE_FS 9
#define NOTE_G  10
#define NOTE_GS 11


#include <limits.h>

//const PROGMEM uint16_t music_1[] = {ZZ, 0, 1537, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_A, 5, 64, ZZ, 0, 128, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_A, 5, 64, ZZ, 0, 320, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 192, ZZ, 0, 96, NOTE_A, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_A, 5, 64, ZZ, 0, 128, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_A, 5, 64, ZZ, 0, 320, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_E, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 64, ZZ, 0, 32, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_E, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 64, ZZ, 0, 32, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_E, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 64, ZZ, 0, 32, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_E, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_G, 5, 64, ZZ, 0, 32, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_G, 5, 64, ZZ, 0, 32, NOTE_A, 5, 128, ZZ, 0, 64, NOTE_A, 5, 128, ZZ, 0, 256, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_E, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 64, ZZ, 0, 32, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_E, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 64, ZZ, 0, 32, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_E, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_C, 6, 128, ZZ, 0, 64, NOTE_A, 5, 64, ZZ, 0, 32, NOTE_AS, 5, 64, ZZ, 0, 32, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_DS, 7, 308, ZZ, 0, 76, NOTE_DS, 7, 308, ZZ, 0, 76, NOTE_DS, 7, 308, ZZ, 0, 76, NOTE_DS, 6, 308, ZZ, 0, 12364, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 12544, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 240, ZZ, 0, 48, NOTE_C, 6, 240, ZZ, 0, 48, NOTE_B, 5, 240, ZZ, 0, 48, NOTE_A, 5, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 240, ZZ, 0, 48, NOTE_C, 6, 240, ZZ, 0, 48, NOTE_B, 5, 240, ZZ, 0, 48, NOTE_A, 5, 192, ZZ, 0, 8, NOTE_A, 5, 120, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 10816, NOTE_DS, 7, 308, ZZ, 0, 76, NOTE_DS, 7, 308, ZZ, 0, 76, NOTE_DS, 7, 308, ZZ, 0, 76, NOTE_DS, 6, 308, ZZ, 0, 268, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 240, ZZ, 0, 48, NOTE_C, 6, 240, ZZ, 0, 48, NOTE_B, 5, 240, ZZ, 0, 48, NOTE_A, 5, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_A, 6, 240, ZZ, 0, 48, NOTE_G, 6, 240, ZZ, 0, 48, NOTE_F, 6, 240, ZZ, 0, 48, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 200, ZZ, 0, 184, NOTE_E, 6, 240, ZZ, 0, 48, NOTE_D, 6, 240, ZZ, 0, 48, NOTE_C, 6, 240, ZZ, 0, 48, NOTE_B, 5, 240, ZZ, 0, 48, NOTE_A, 5, 192, ZZ, 0, 8, NOTE_A, 5, 120, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 13888, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_E, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_B, 4, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_G, 4, 128, ZZ, 0, 64, NOTE_D, 5, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_A, 4, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_F, 4, 128, ZZ, 0, 64, NOTE_C, 5, 128, ZZ, 0, 64, NOTE_B, 4, 256, -2, 0, 0};
const PROGMEM uint16_t music_1[] = {ZZ, 0, 194, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_AS, 2, 188, ZZ, 0, 196, NOTE_C, 3, 320, ZZ, 0, 64, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_AS, 2, 320, ZZ, 0, 64, NOTE_GS, 2, 188, ZZ, 0, 4, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_GS, 2, 188, ZZ, 0, 4, NOTE_AS, 2, 1632, ZZ, 0, 96, NOTE_G, 2, 672, ZZ, 0, 96, NOTE_AS, 2, 320, ZZ, 0, 64, NOTE_F, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_G, 1, 92, ZZ, 0, 4, NOTE_F, 1, 92, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_G, 1, 92, ZZ, 0, 4, NOTE_F, 1, 92, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 196, NOTE_G, 1, 512, ZZ, 0, 64, NOTE_G, 1, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_F, 2, 188, ZZ, 0, 4, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 196, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_F, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_C, 2, 672, ZZ, 0, 96, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_DS, 3, 320, ZZ, 0, 64, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_G, 2, 320, ZZ, 0, 64, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_G, 2, 92, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_C, 2, 672, ZZ, 0, 96, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_AS, 1, 92, ZZ, 0, 4, NOTE_AS, 1, 92, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 196, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_D, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_C, 2, 672, ZZ, 0, 96, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_DS, 2, 320, ZZ, 0, 64, NOTE_DS, 2, 320, ZZ, 0, 64, NOTE_D, 2, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 448, NOTE_C, 2, 320, ZZ, 0, 448, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_AS, 2, 188, ZZ, 0, 196, NOTE_C, 3, 320, ZZ, 0, 64, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_AS, 2, 320, ZZ, 0, 64, NOTE_GS, 2, 188, ZZ, 0, 4, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_GS, 2, 188, ZZ, 0, 4, NOTE_AS, 2, 1632, ZZ, 0, 96, NOTE_G, 2, 672, ZZ, 0, 96, NOTE_AS, 2, 320, ZZ, 0, 64, NOTE_F, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_G, 1, 92, ZZ, 0, 4, NOTE_F, 1, 92, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_G, 1, 92, ZZ, 0, 4, NOTE_F, 1, 92, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 196, NOTE_G, 1, 512, ZZ, 0, 64, NOTE_G, 1, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_F, 2, 188, ZZ, 0, 4, NOTE_G, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 196, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_F, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_C, 2, 672, ZZ, 0, 96, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_DS, 3, 320, ZZ, 0, 64, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_G, 2, 320, ZZ, 0, 64, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_DS, 2, 92, ZZ, 0, 4, NOTE_F, 2, 92, ZZ, 0, 4, NOTE_G, 2, 92, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_C, 2, 672, ZZ, 0, 96, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_AS, 1, 92, ZZ, 0, 4, NOTE_AS, 1, 92, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 196, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_DS, 2, 188, ZZ, 0, 4, NOTE_D, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_C, 2, 672, ZZ, 0, 96, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_DS, 2, 320, ZZ, 0, 64, NOTE_DS, 2, 320, ZZ, 0, 64, NOTE_D, 2, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_G, 1, 188, ZZ, 0, 4, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_E, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 448, NOTE_C, 2, 320, ZZ, 0, 448, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_F, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_G, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, ZZ, 0, 4, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 284, ZZ, 0, 4, NOTE_AS, 1, 188, ZZ, 0, 4, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_GS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_AS, 1, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 320, ZZ, 0, 64, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 284, ZZ, 0, 4, NOTE_C, 2, 188, -2, 0, 0};


long int endTime = 0;

/* Timer reload value, globally available */
unsigned int tcnt2;

/* Keep track of when each note needs to be switched */
int count = 0;

int number = 0;

int buttonPin = 2;


unsigned int coundEnd = 0;
unsigned long int bigCountEnd = 0;

const PROGMEM uint16_t freq[] =
{
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

int freqSecond[11 * 12];

//Setup Function will run once at initialization
void setup()
{

  Serial.begin(9600);


  for (int i = 0; i < 11 * 12; i++)
  {
    double temp = (15625) / (2 * pgm_read_word_near(freq + i));
    freqSecond[i] = (int) temp;
    //   Serial.println(freqSecond[i]);

  }

  //	Serial.println("Udało się");

  //		song[0] = 0;
  //		song[1] = 3;


  //DDRB = B1100;
  pinMode(10, OUTPUT);
  pinMode(buttonPin, INPUT);

  //  coundEnd = freqSecond[66];

  coundEnd = INT_MAX;

  //Kanged from http://www.jeremyblum.com/2010/09/05/driving-5-speakers-simultaneously-with-an-arduino/

  //Configure I/O Pin Directions

  /* First disable the timer overflow interrupt*/
  TIMSK2 &= ~(1 << TOIE2);

  /* Configure timer2 in normal mode (no PWM) */
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  TCCR2B &= ~(1 << WGM22);

  /* Select clock source: internal I/O clock */
  ASSR &= ~(1 << AS2);

  /* Disable Compare Match A interrupt (only overflow) */
  TIMSK2 &= ~(1 << OCIE2A);

  /* Configure the prescaler to CPU clock divided by 128 */
  TCCR2B |= (1 << CS22)  | (1 << CS20); // Set bits
  TCCR2B &= ~(1 << CS21);           // Clear bit

  /* We need to calculate a proper value to load the counter.
  * The following loads the value 248 into the Timer 2 counter
  * The math behind this is:
  * (Desired period) = 64us.
  * (CPU frequency) / (prescaler value) = 125000 Hz -> 8us.
  * (desired period) / 8us = 8.
  * MAX(uint8) - 8 = 248;
  */
  /* Save value globally for later reload in ISR */
  tcnt2 = 248;

  /* Finally load end enable the timer */
  TCNT2 = tcnt2;
  TIMSK2 |= (1 << TOIE2);


}

/* Install the Interrupt Service Routine (ISR) for Timer2.  */
ISR(TIMER2_OVF_vect)
{
  /* Reload the timer */
  TCNT2 = tcnt2;

  count++;

  if (count == coundEnd)
  {
    PORTB ^= B1100;
    count = 0;
  }

}


void loop()
{


  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (endTime <= millis())
  {

    unsigned long int song[] = {0, 0, 0};

    song[0] = pgm_read_word_near(music_1 + (3 * number));
    song[1] = pgm_read_word_near(music_1 + (3 * number) + 1);
    song[2] = pgm_read_word_near(music_1 + (3 * number) + 2);

    noInterrupts();

    if (song[0] == 69)
    {
      coundEnd = INT_MAX;
    }
    else
    {
      //coundEnd = (15625) / (2 * pgm_read_word_near(freq + ((song[1] - 1) * 12 + song[0])));
      coundEnd = freqSecond[((song[1] + 3) * 12 + song[0])];
    }
    interrupts();

    Serial.println(coundEnd);

    endTime = millis() + song[2];

    Serial.println(song[2]);
    Serial.println("");


    count = 0;

    number++;
  }

  //Do whatever else you want to do with your arduino!
}
