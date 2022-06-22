// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)

// Libraries
#include <Adafruit_NeoPixel.h>

// Constants
const int US_TRIG_PIN = 2;		// Ultrasonic sensor trigger pin
const int US_ECHO_PIN = 3;		// Ultrasonic sensor echo pin
const int STRIP_LED_PIN = 8;	// NeoPixel strip led pin
const int STANDARD_LED_PIN = 9;	// Standard led pin used to indicate no more available leds in strip
const int SPEAKER_PIN = 13;		// Speaker pin used together with standard led pin

const double SOUND_SPEED = 0.034;	// Speed of sound in cm/ms
const int MIN_DIST = 3;			    // Minimum distance measured accurately by US sensor in cm
const int MAX_DIST = 300;			// Maximum distance measured accurately by US sensor in cm
const int LED_NO = 12; 		 		// Amount of LEDs in NeoPixel strip
const int MEASUREMENT_INTERVAL = 500;	// Interval of 500ms between measurements
// Variables
long duration;		// Used for travel time in US distance measurements
int distance;		// Used for storing distance in US distance measurements
int ledsToGlow;		// Indicates how many LEDs to turn on


// Create new instance of NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NO, STRIP_LED_PIN, NEO_GRB + NEO_KHZ800);

// Colours
const uint32_t BLUE = strip.Color(0, 0, 255);	// RGB value of colour blue
const uint32_t RED = strip.Color(255, 0, 0);	// RGB value of colour red

void setup()
{
  Serial.begin(9600);             // Start serial communication
  pinMode(US_TRIG_PIN, OUTPUT);   // Set trigger pin as output
  pinMode(US_ECHO_PIN, INPUT);    // Set echo pin as input
  pinMode(STANDARD_LED_PIN, OUTPUT); // Set standard led as output
  pinMode(SPEAKER_PIN, OUTPUT);		 // Set speaker pin as output
  
  strip.begin();				  // Set NeoPixel strip as output
  strip.show();					  // Initialize all LEDs off
}

void loop()
{
  // Read current distance and update distance variable
  distance = readDistance();
  
  // Use map function to return how many LEDs to turn on
  ledsToGlow = map(distance, MIN_DIST, MAX_DIST, 1, LED_NO);
  
  // Update leds on strip, standard led, and speaker
  updateOutputs(ledsToGlow);
  
  // Turn all LEDs off
  strip.clear();	
  
  delay(MEASUREMENT_INTERVAL);
}

// Credits:
// Ultrasonic sensor code by Dejan Nedelkovski, www.HowToMechatronics.com
// This method reads the distance of the object and returns the distance variable
int readDistance()
{
  // Clear trigger pin
  digitalWrite(US_TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Set trigger pin on HIGH state for 10 micro seconds
  digitalWrite(US_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG_PIN, LOW);
  // Read echo pin, value returned is sound wave travel time in microseconds
  duration = pulseIn(US_ECHO_PIN, HIGH);
  
  // Distance = (Time x Speed) / 2
  distance = (duration * SOUND_SPEED) / 2;
  
  return distance;
}

// This method takes the amount of LEDs to glow as parameter
// And uses it to update the NeoPixel strip, the standard led pin
// and the speaker state
void updateOutputs(int ledsToGlow)
{
  Serial.println(ledsToGlow);
  // Handles case where more than available LEDs should be turned on
  if (ledsToGlow > LED_NO)
  {
    strip.fill(BLUE, 0, LED_NO);			// Turn on first LED with colour red
    digitalWrite(STANDARD_LED_PIN, HIGH);	// Turn on standard LED since all available LEDs are used
    digitalWrite(SPEAKER_PIN, HIGH);		// Turn on speaker since all available LEDs are used
  }
  // Handles case where available LEDs should be turned on
  else
  {
    strip.fill(BLUE, 0, ledsToGlow);  		// Turn on LEDs from index 0 to ledsToGlow with colour blue
  	digitalWrite(STANDARD_LED_PIN, LOW); 	// Turn off standard LED when not necessary
    digitalWrite(SPEAKER_PIN, LOW);		    // Turn off speaker when not necessary
  }
  strip.show();		// Update LEDs on strip
}
