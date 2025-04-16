#include <Arduino.h>
#include <FastLED.h>
#include <IRremote.hpp>

// Pin Definitions
#define PIN_RBGLED 4         // Pin for RGB LED
#define NUM_LEDS 1           // Number of LEDs
#define PIN_Motor_PWMA 5     // Motor A (M1) PWM pin
#define PIN_Motor_AIN_1 7    // Motor A direction pin
#define PIN_Motor_STBY 3     // Standby pin for motor
#define PIN_IR_RECEIVE 9     // Pin for IR receiver (override to pin 9)

// Setup RGB LED
CRGB leds[NUM_LEDS];  // LED array

void setup() {
    Serial.begin(115200);
    while (!Serial)
        ; // Wait for Serial to become available.

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Initialize RGB LED
    FastLED.addLeds<WS2812, PIN_RBGLED, GRB>(leds, NUM_LEDS);
    leds[0] = CRGB::Black;  // Initially turn off LED
    FastLED.show();

    // Initialize motor control pins
    pinMode(PIN_Motor_PWMA, OUTPUT);
    pinMode(PIN_Motor_AIN_1, OUTPUT);
    pinMode(PIN_Motor_STBY, OUTPUT);

    // Initialize the IR receiver
    IrReceiver.begin(PIN_IR_RECEIVE, ENABLE_LED_FEEDBACK);

    // Enable motor standby (but initially off)
    digitalWrite(PIN_Motor_STBY, HIGH);  // Disable standby mode
    digitalWrite(PIN_Motor_AIN_1, HIGH); // Set direction forward
    analogWrite(PIN_Motor_PWMA, 0);      // Motor initially off

    Serial.println(F("Ready to receive IR signals"));
}

void loop() {
    // Check if IR data is available and if yes, decode it
    if (IrReceiver.decode()) {
        // Print a summary of the received data
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.resume(); // Ready to receive the next frame

        // Button 1: Turn on motor and LED (Command = 0x16)
        if (IrReceiver.decodedIRData.command == 0x16) {
            turnMotorOn();
            turnLEDOn();
        }

        // Button 2: Turn off motor and LED (Command = 0x19)
        if (IrReceiver.decodedIRData.command == 0x19) {
            turnMotorOff();
            turnLEDOff();
        }
    }
}

// Function to turn the motor on
void turnMotorOn() {
    analogWrite(PIN_Motor_PWMA, 220);  // Set motor to full speed
    Serial.println("Motor ON");
}

// Function to turn the motor off
void turnMotorOff() {
    analogWrite(PIN_Motor_PWMA, 0);    // Stop the motor
    Serial.println("Motor OFF");
}

// Function to turn the LED on (red)
void turnLEDOn() {
    leds[0] = CRGB::Red;  // Set LED to red
    FastLED.show();
    Serial.println("LED ON");
}

// Function to turn the LED off
void turnLEDOff() {
    leds[0] = CRGB::Black;  // Turn off LED
    FastLED.show();
    Serial.println("LED OFF");
}
