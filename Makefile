all: floppy

floppy: floppy
	gcc -std=c99 -Wall -lwiringPi -lm -o beep RPi.c

clean:
	rm -f beep
