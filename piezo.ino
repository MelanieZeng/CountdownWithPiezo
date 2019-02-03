// This #include statement was automatically added by the Particle IDE.
#include "pitches.h"

int buttonPin = D3;
int buttonState;

int speakerPin = D2;

int countdown = 300000; //for the purpose of a quick demo, I changed it to 3 minutes in the demo

bool state = false; //timer is off

// create an array for the notes in the melody:
//C4,G3,G3,A3,G3,0,B3,C4
int melody[] = {1908,2551,2551,2273,2551,0,2024,1908}; 

// create an array for the duration of notes.
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4,8,8,4,4,4,4,4 };


void setup() {
  pinMode( speakerPin, OUTPUT );
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW){ //when button has been pressed
      state =! state; //start the timer
      if (state == true){ //when timer is on
          playNotes();
      }
  }  
  if (state == true){ //when timer is on
      if (countdown > 0){ //start counting down
          countdown = countdown - 1000;
          delay(1000);
      }
      if (countdown == 240000 or countdown == 180000 or countdown == 120000 or countdown == 60000){
          tone(speakerPin, NOTE_FS6, 500);
      }
      if (countdown <= 15000 and countdown > 0){
          tone(speakerPin, NOTE_FS6, 500);
          delay(500);
      }
      if(countdown == 0){
          state =! state; //turn of timer
          playNotes(); //indicate it's time
      }
  }
}

void playNotes()
{
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000/noteDurations[thisNote];
      tone(speakerPin, melody[thisNote],noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(speakerPin);
    }
}