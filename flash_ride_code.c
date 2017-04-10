/* 
 
 The circuit:
 * LED attached from pin 11 to ground 
 * LED attached from pin 12 to ground 
 * LED attached from pin 13 to ground 
 
 * Xbee input attached to pin 2 from +5V
 * Xbee input attached to pin 3 from +5V
 * Xbee input attached to pin 4 from +5V
 * 10K resistor attached to pin 2 from ground
 * 10K resistor attached to pin 3 from ground
 * 10K resistor attached to pin 4 from ground

*/

// constants:
// set pin numbers:
const int L_buttonPin = 2;  // XBee 18
const int R_buttonPin = 3;  // XBee 19
const int C_buttonPin = 4;  // XBee 20
const int L_lightPin = 11;
const int R_lightPin = 12;
const int C_lightPin = 13;

// flash parameters
const int flash_duration = 500 - 1;  // each flash is 1/2 second
const int flash_count = 20 - 1;      // 20 flashes (10 seconds)

// variables:
int L_buttonState = 0;
int R_buttonState = 0;
int C_buttonState = 0;
int state = 0;         // 1: (R/L) light on, 0: (R/L) light off
int loopcounter = 0;   // increment each time through the loop while flashing
int flashcounter = 0;  // increment each time the light turns on or off
int L_flash = 0;       // 1: L is currently flashing
int R_flash = 0;       // 1: R is currently flashing


void setup() {
  // initialize the light pins as outputs:
  pinMode(L_lightPin, OUTPUT);      
  pinMode(R_lightPin, OUTPUT);      
  pinMode(C_lightPin, OUTPUT);      
  // initialize the button pins as inputs:
  pinMode(L_buttonPin, INPUT);     
  pinMode(R_buttonPin, INPUT);     
  pinMode(C_buttonPin, INPUT);     

  for (int i = 0; i < 3; i++) {
    digitalWrite(L_lightPin, HIGH);
    digitalWrite(R_lightPin, HIGH);
    digitalWrite(C_lightPin, HIGH);
    delay(150);
    digitalWrite(L_lightPin, LOW);
    digitalWrite(R_lightPin, LOW);
    digitalWrite(C_lightPin, LOW);
    delay(150);  
  }
  
  digitalWrite(L_lightPin, HIGH);
  delay(200);
  digitalWrite(L_lightPin, LOW);
  digitalWrite(R_lightPin, HIGH);
  delay(200);
  digitalWrite(R_lightPin, LOW);
  digitalWrite(C_lightPin, HIGH);
  delay(200);
  digitalWrite(C_lightPin, LOW);
  delay(1000);
  
//  Serial.begin(9600);
//  Serial.println("Debugging");
}



void loop(){
  // read the states of the button values:
  L_buttonState = digitalRead(L_buttonPin);
  R_buttonState = digitalRead(R_buttonPin);
  C_buttonState = digitalRead(C_buttonPin);

  if (L_flash == 0) {
    if (L_buttonState == HIGH) {     
      if (R_flash == 1) {
        R_flash = 0;
        digitalWrite(R_lightPin, LOW);
      }
      L_flash = 1;
      state = 1;
      loopcounter = 0;
      flashcounter = 0;  
      digitalWrite(L_lightPin, HIGH);  
    }
  }
//  else {   // (only runs when L_flash == 1 ?)
  if (R_flash == 0) {
    if (R_buttonState == HIGH) {     
      if (L_flash == 1) {
        L_flash = 0;
        digitalWrite(L_lightPin, LOW);
      }
      R_flash = 1;
      state = 1;
      loopcounter = 0;
      flashcounter = 0;  
      digitalWrite(R_lightPin, HIGH);  
//      }
    }
  }
  if (C_buttonState == HIGH) {
    digitalWrite(C_lightPin, HIGH);
  }
  else {
    digitalWrite(C_lightPin, LOW);
  }
  
  // Flash 'em
  if (L_flash == 1) {
    if (loopcounter == flash_duration) {
      if (flashcounter == flash_count) {
        L_flash = 0;
        state = 0;
        digitalWrite(L_lightPin, LOW);
      }
      else {
        flashcounter++;
        loopcounter = 0;
        if (state == 1) {
          state = 0;
          digitalWrite(L_lightPin, LOW);
        }
        else {
          state = 1;
          digitalWrite(L_lightPin, HIGH);
        }
      }
    }
    else {
      loopcounter++;
    }
  }
  else {
    if (R_flash == 1) {  // same as above, only for R signal
      if (loopcounter == flash_duration) {
        if (flashcounter == flash_count) {
          R_flash = 0;
          state = 0;
          digitalWrite(R_lightPin, LOW);
        }
        else {
          flashcounter++;
          loopcounter = 0;
          if (state == 1) {
            state = 0;
            digitalWrite(R_lightPin, LOW);
          }
          else {
            state = 1;
            digitalWrite(R_lightPin, HIGH);
          }
        }
      }
      else {
        loopcounter++;
      }
    }
  }
  delay(1);
}