#include "SoftwareSerial.h"
#include "MP3FLASH16P.h"
MP3FLASH16P myPlayer;


const int switchButtonPin = 12;    // the number of the switch pin
int lastButtonState = LOW;
long lastChangeTime = 0;
long debounceDelay = 3;    // the debounce time; increase if the output flickers
int debouncedMoveState = LOW;   // the previous reading from the input pin

const int NUM_OF_SONGS = 19;
int songIndex = 2;

void setup() {
  // Init the player with the busy pin connected to Arduino pin 3
  myPlayer.init(3);

  pinMode(switchButtonPin, INPUT);

//  Serial.begin(9600);       // use the serial port

}

void loop() {

  int reading = digitalRead(switchButtonPin);

  if (reading != lastButtonState) {
    lastChangeTime = millis();

  }

  if ((millis() - lastChangeTime) > debounceDelay) {
    if (debouncedMoveState == LOW && reading == HIGH) {
      myPlayer.playFileAndWait(1, 30);


      if(songIndex > NUM_OF_SONGS){
        songIndex = 2;
      }
  
      //Serial.println(songIndex);
      myPlayer.playFileAndWait(songIndex++, 30);
      
    }
    debouncedMoveState = reading;
  }

  lastButtonState = reading;

}
