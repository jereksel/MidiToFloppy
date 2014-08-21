'''
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
'''

#!/usr/bin/env python
import argparse, csv


def buildBeep():
    csvFile = csv.reader(open('samurai.csv', 'rb'))
    notes = 'const int music[][3] = {'
    ilosc_danych = 0
    timing_temp = -1
    myList = ['NOTE_C','NOTE_CS','NOTE_D','NOTE_DS','NOTE_E','NOTE_F','NOTE_FS','NOTE_G','NOTE_GS','NOTE_A','NOTE_AS','NOTE_B','ZZ']
    dubel = 0
    tempo = 2
    for row in csvFile:
        if (ilosc_danych >=0):
            if "4" in row[0]:                                                       # Double/Triple notes TODO: Choose center
                if ((('Note_on_c' in row[2]) or ('Note_off_c' in row[2]))) and not (int(row[1]) == int(timing_temp)):
                    if (dubel):
                        dubel = 0
                        timing_2 = int(row[1]) - int(timing_temp)
                        notes += str(timing_2 * tempo)
                        notes += "}, "
                        timing_temp = int(float(row[1]))
                    else:
                        # Delete later
                        notes += "{"

                        notes += myList[12]
                        notes += ", "
                        notes += "0"
                        notes += ", "

                        timing_2 = int(row[1]) - int(timing_temp)
                        notes += str(timing_2 * tempo)
                        notes += "}, {"

                        timing_temp = int(float(row[1]))
                        notes += myList[int(float(row[4])) % 12]
                        notes += ", "
                        notes += str((int(float(row[4]))) // 12)
                        notes += ", "
                        dubel = 1
                    ilosc_danych = ilosc_danych + 1

    notes = notes[:-2]
    notes += '};'
    f1 = open('./notes', 'w+')
    f1.write(notes)
    return


buildBeep()
