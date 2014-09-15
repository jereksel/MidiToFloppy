REQUIREMENTS
============
1. Connected Floppy Drives (http://www.instructables.com/id/How-to-Make-Musical-Floppy-Drives/?ALLSTEPS)
2. RaspberryPi with WiringPi installed (http://wiringpi.com/download-and-install/)
3. Computer (it can be RaspberryPi from point 2) with python (https://www.python.org/) and miditocsv installed (http://www.fourmilab.ch/webtools/midicsv/)
4. Midi file
5. MidiToFloppy

INSTALLATION
============
1. Convert your midi using miditocsv
2. Place csv file in MidiToFloppy directory
3. Open cvsToFloppy.py and change filename
4. Run cvsToFloppy.py
5. Create song.h file (you can use template)
6. Copy content from file "notes" to notes.h
7. Change song.h file (see comments in template file).
8. Place RPi.c, song.h, scale.h and Makefile in one folder (on RaspberryPi)
9. make
10. run program (sudo ./beep)
11. Enjoy


PREVIEW
============
https://www.youtube.com/watch?v=IVcf36hw8bQ&index=1&list=PLm7SWesXMQWdmczY84AmFVOV8gD-ynW_j
