/*
	This example plays a random file (001 to 010) forever
	It uses the playFileAndWait() command so no extra code is needed, it will play another file as soon as the previous one finishes
	If it doesn't work, try reversing the RX/TX wires as that's probably going to be the most common mistake
	Also check that the player's BUSY line is connected to Arduino pin 3
	Finally check that the player has a speaker connected as well as ground and VCC
*/

#include "SoftwareSerial.h"
#include "MP3FLASH16P.h"
MP3FLASH16P myPlayer;


const int switchButtonPin = 12;    // the number of the pushbutton pin
int lastButtonState = LOW;
long lastChangeTime = 0;
long debounceDelay = 5;    // the debounce time; increase if the output flickers
int debouncedMoveState = LOW;   // the previous reading from the input pin

const int NUM_OF_SONGS = 10;
int songIndex = 2;

void setup() {
	// Init the player with the busy pin connected to Arduino pin 3
	myPlayer.init(3);

	pinMode(switchButtonPin, INPUT);

	//Serial.begin(9600);       // use the serial port

}

void loop() {

	int reading = digitalRead(switchButtonPin);

	if (reading != lastButtonState) {
		lastChangeTime = millis();

	}

	if ((millis() - lastChangeTime) > debounceDelay) {
		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:

		// if the button state has changed:

		if (debouncedMoveState == LOW && reading == HIGH) {
      myPlayer.playFileAndWait(1, 30);


      if(songIndex > NUM_OF_SONGS){
        songIndex = 2;
      }
  
			// Plays random files from those named 001 to 010
			myPlayer.playFileAndWait(songIndex++, 30);
		}
		debouncedMoveState = reading;
	}

	lastButtonState = reading;

}
