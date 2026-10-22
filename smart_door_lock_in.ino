#include <Keypad.h>
#include <Servo.h>

Servo doorLock;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(
  makeKeymap(keys), rowPins, colPins, ROWS, COLS
);

String password = "1234";
String enteredPassword = "";

void setup() {
  Serial.begin(9600);

  doorLock.attach(10);
  doorLock.write(0);  // Door locked

  Serial.println("Smart Door Lock System");
  Serial.println("Enter password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (enteredPassword == password) {
        Serial.println("Access Granted");
        doorLock.write(90);  // Unlock door
        delay(5000);
        doorLock.write(0);   // Lock door again
        Serial.println("Door Locked");
      } else {
        Serial.println("Wrong Password!");
      }

      enteredPassword = "";
      Serial.println("Enter password:");
    }
    else if (key == '*') {
      enteredPassword = "";
      Serial.println("Password Cleared");
    }
    else {
      enteredPassword += key;
      Serial.println("Key Pressed");
    }
  }
}
