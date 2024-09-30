#include <Bounce2.h>
#include <Keyboard.h>

const int buttonPin = 2;   
const int ledMutePin = 15;
const int ledOnPin = 16;

bool isMuted = false;
Bounce debouncer = Bounce();

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledMutePin, OUTPUT);
  pinMode(ledOnPin, OUTPUT);
  
  digitalWrite(ledMutePin, LOW);     
  digitalWrite(ledOnPin, HIGH);     

  debouncer.attach(buttonPin);       
  debouncer.interval(10);         

  Keyboard.begin();                  
}

void loop() {
  debouncer.update();  

  if (debouncer.fell()) {
    
    isMuted = !isMuted;

   
    Keyboard.press(KEY_MEDIA_MUTE);
    delay(100); 
    Keyboard.release(KEY_MEDIA_MUTE);


    if (isMuted) {
      digitalWrite(ledMutePin, HIGH); 
      digitalWrite(ledOnPin, LOW); 
    } else {
      digitalWrite(ledMutePin, LOW); 
      digitalWrite(ledOnPin, HIGH);  
    }
  }
}
