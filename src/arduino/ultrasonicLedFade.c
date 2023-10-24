// This program uses a ultrasonic HC-SR04 sensor to detect distance
// It then sets the "fade" value of a led according to the distance

// CONSTANTS
const float SOUND_SPEED = 0.0343; // cm/microsecond
const int MIN_DISTANCE = 2; // min distance in cm measurable by HC-SR04
const int MAX_DISTANCE = 40; // max distance in cm chosen according to use case (max possible: 400cm)

const int trigPin = 7; // Pin used for trigger signal
const int echoPin = 8; // Pin used for echo signal
const int ledPin = 9; // Pin used for led

// VARIABLES
// duration of signal pulse to get to object and back to HC-SR04
// distance between HC-SR04 and object
// Fade value of led
long duration, distance, fadeValue;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // Send signal pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Register duration of travelling pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance using duration
  distance = microsecondsToCentimeters(duration);
  
  // If distance is lower or equal than maximum specified
  if (distance <= MAX_DISTANCE) {
    // set fadeValue using distance
    fadeValue = centimetersToFadeValue(distance);
  }
  else {
    // otherwise turn off the led
    fadeValue = 0;
  }
  
  // update led with fade value
  analogWrite(ledPin, fadeValue);
  
  delay(100);
}

// This method takes a duration in microseconds as parameter 
// Returns the distance in centimeters covered by sound in that time, divided by 2)
long microsecondsToCentimeters(long microseconds)
{
  return SOUND_SPEED * microseconds / 2;
}

// This method takes a distance in centimeters as parameter
// Maps the distance inversely to a fade value from 255 to 0
// i.e., greater distance, smaller fade value
// Returns a fade value from 0 to 255 which will be used to light the led
long centimetersToFadeValue(long cm)
{
  return map(cm, MIN_DISTANCE, MAX_DISTANCE, 255, 0);
}
                        
