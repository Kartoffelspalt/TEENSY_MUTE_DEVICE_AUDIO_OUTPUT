#include <Bounce2.h>
#include <Keyboard.h>

const int buttonPin = 2;   // Pin für den Button
const int ledMutePin = 15;  // Pin für die Lampe bei Stummschaltung
const int ledOnPin = 16;    // Pin für die Lampe bei aktivem Ton

bool isMuted = false;      // Statusvariable für die Stummschaltung
Bounce debouncer = Bounce();  // Bounce-Objekt für das Entprellen erstellen

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Pull-up-Widerstand für den Button aktivieren
  pinMode(ledMutePin, OUTPUT);       // Lampe für Stummschaltung (Pin 3) als Ausgang definieren
  pinMode(ledOnPin, OUTPUT);         // Lampe für aktiv (Pin 4) als Ausgang definieren
  
  // Anfangszustand der LEDs (Ton nicht stumm, also LED an Pin 4 an)
  digitalWrite(ledMutePin, LOW);     // Stummschaltlampe aus
  digitalWrite(ledOnPin, HIGH);      // Aktive Lampe an

  debouncer.attach(buttonPin);       // Pin dem Bounce-Objekt zuweisen
  debouncer.interval(10);            // Entprell-Intervall auf 10ms setzen

  Keyboard.begin();                  // Start der Keyboard-Funktion
}

void loop() {
  debouncer.update();  // Button Status aktualisieren

  // Wenn der Button gedrückt wird (Wechsel von HIGH zu LOW):
  if (debouncer.fell()) {
    // Stummschaltungsstatus umkehren
    isMuted = !isMuted;

    // Mute-Befehl senden (entspricht der Mute-Taste auf der Tastatur)
    Keyboard.press(KEY_MEDIA_MUTE);
    delay(100);  // Kurzer Delay, damit der Befehl registriert wird
    Keyboard.release(KEY_MEDIA_MUTE);

    // Je nach Stummschaltungsstatus die entsprechende Lampe einschalten
    if (isMuted) {
      digitalWrite(ledMutePin, HIGH);  // Lampe bei Stummschaltung an (Pin 3)
      digitalWrite(ledOnPin, LOW);     // Lampe bei aktivem Ton aus (Pin 4)
    } else {
      digitalWrite(ledMutePin, LOW);   // Lampe bei Stummschaltung aus (Pin 3)
      digitalWrite(ledOnPin, HIGH);    // Lampe bei aktivem Ton an (Pin 4)
    }
  }
}
