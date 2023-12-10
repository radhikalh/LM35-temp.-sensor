							   #include <TimerOne.h>

const int lm35Pin = A0;    // LM35 analog pin
const int ledPin = 13;     // Onboard LED pin

const int belowThresholdBlinkInterval = 250;  // Blink interval when below 30°C
const int aboveThresholdBlinkInterval = 500;  // Blink interval when above 30°C

int ledState = LOW;        // Current state of the LED
int currentState = 0;      // 0 for below 30°C, 1 for above 30°C

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  Timer1.initialize(1000);  // Initialize Timer1 with 1-second period
  Timer1.attachInterrupt(timerCallback);
}

void loop() {
  // Read the temperature from LM35 sensor
  int sensorValue = analogRead(lm35Pin);
  float temperature = (sensorValue * 5.0 / 1024.0) * 100.0;

  // Check temperature and update the state
  currentState = (temperature < 30.0) ? 0 : 1;

  // Print temperature to serial monitor (optional)
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}

void timerCallback() {
  // Control LED blink based on the current state
  int interval = (currentState == 0) ? belowThresholdBlinkInterval : aboveThresholdBlinkInterval;

  // If the LED is off, turn it on; if it's on, turn it off
  ledState = (ledState == LOW) ? HIGH : LOW;

  // Update the LED state
  digitalWrite(ledPin, ledState);
}