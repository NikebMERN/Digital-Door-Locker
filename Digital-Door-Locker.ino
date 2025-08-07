#include <IRremote.hpp>
#include <Servo.h>

#define IR_RECEIVE_PIN 2
#define SERVO_PIN 9
#define RED_LED 10
#define GREEN_LED 11

Servo lockServo;

String enteredCode = "";
String correctCode = "1234";
unsigned long lastInputTime = 0;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready");

  lockServo.attach(SERVO_PIN);
  lockServo.write(0); // Locked

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);   // RED on = locked
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t irValue = IrReceiver.decodedIRData.decodedRawData;  // Use raw value
    Serial.print("IR Code Received: 0x");
    Serial.println(irValue, HEX);

    char key = getKeyFromIR(irValue);

    // Always print current entered code
    Serial.print("Entered Code: ");
    Serial.println(enteredCode);

    if (key != 0) {
      if (key == 'O') {  // Confirm
        Serial.print("🔐 Checking code: ");
        Serial.println(enteredCode);

        if (enteredCode == correctCode) {
          unlockDoor();
        } else {
          wrongCode();
        }
        enteredCode = "";
      } else {
        enteredCode += key;
        lastInputTime = millis();
      }
    }

    IrReceiver.resume();
  }

  // Timeout handling
  if (enteredCode.length() > 0 && (millis() - lastInputTime > 10000)) {
    Serial.println("⌛ Code timed out. Resetting...");
    enteredCode = "";
  }
}

char getKeyFromIR(uint32_t val) {
  switch (val) {
    case 0xFF00BF00: return 'O';  // Power button
    case 0xEF10BF00: return '1';
    case 0xEE11BF00: return '2';
    case 0xED12BF00: return '3';
    case 0xEB14BF00: return '4';
    case 0xEA15BF00: return '5';
    case 0xE916BF00: return '6';
    case 0xE718BF00: return '7';
    case 0xE619BF00: return '8';
    case 0xE51ABF00: return '9';
    case 0xF30CBF00: return '0';
    default: return 0;
  }
}


void unlockDoor() {
  Serial.println("✅ Code Correct. Door Unlocked!");
  lockServo.write(90);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  delay(5000);
  lockServo.write(0);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}

void wrongCode() {
  Serial.println("❌ Wrong Code!");
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED_LED, LOW);
    delay(200);
    digitalWrite(RED_LED, HIGH);
    delay(200);
  }
}
