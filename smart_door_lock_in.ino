
#include <Keypad.h>
#include <Servo.h>
#include <string.h>

// Keypad layout
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(
  makeKeymap(keys), rowPins, colPins, ROWS, COLS
);

Servo lockServo;

const int servoPin = 10;
const int lockedAngle = 0;
const int unlockedAngle = 90;

const char correctPassword[] = "1234";
char enteredPassword[5];
byte passwordIndex = 0;

void clearPassword() {
  passwordIndex = 0;
  enteredPassword[0] = '\0';
}

void setup() {
  Serial.begin(9600);

  lockServo.attach(servoPin);
  lockServo.write(lockedAngle);

  clearPassword();

  Serial.println("Smart Door Lock Ready");
  Serial.println("Enter password, then press #");
}

void loop() {
  char key = keypad.getKey();

  if (key == NO_KEY) {
    return;
  }

  if (key == '*') {
    clearPassword();
    Serial.println("Password cleared");
    return;
  }

  if (key == '#') {
    if (strcmp(enteredPassword, correctPassword) == 0) {
      Serial.println("Access Granted");

      lockServo.write(unlockedAngle);
      delay(5000);

      lockServo.write(lockedAngle);
      Serial.println("Door locked again");
    } else {
      Serial.println("Access Denied");
    }

    clearPassword();
    Serial.println("Enter password, then press #");
    return;
  }

  // Accept digits only; limit input to 4 characters.
  if (key >= '0' && key <= '9' && passwordIndex < 4) {
    enteredPassword[passwordIndex] = key;
    passwordIndex++;
    enteredPassword[passwordIndex] = '\0';

    Serial.println("Digit entered");
  }
}
