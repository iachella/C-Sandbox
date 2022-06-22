// Libraries

// Constants
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int PLAYER_1_BTN = 2;
const int PLAYER_2_BTN = 3;

const int COLOUR_RED = 1;
const int COLOUR_GREEN = 2;

// Variables
bool nextGame = true;

unsigned long interval = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int ledColour;

int player1BtnState = LOW;
int player2BtnState = LOW;

int scorePlayer1 = 0;
int scorePlayer2 = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(PLAYER_1_BTN, INPUT);
  pinMode(PLAYER_2_BTN, INPUT);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop()
{
  if (nextGame){generateGame();}
  
  if (!nextGame){updateLed();}
  
  
  player1BtnState = digitalRead(PLAYER_1_BTN);
  player2BtnState = digitalRead(PLAYER_2_BTN);
  if (player1BtnState == HIGH && ledColour == COLOUR_RED){scorePlayer1--;}
  if (player2BtnState == HIGH && ledColour == COLOUR_RED){scorePlayer2--;}
  
  if (player1BtnState == HIGH && ledColour == COLOUR_GREEN){scorePlayer1++;}
  if (player2BtnState == HIGH && ledColour == COLOUR_GREEN){scorePlayer2++;}
  
  if (scorePlayer1 == 3){Serial.println("player 1 wins");}
  if (scorePlayer2 >= 3){Serial.println("player 2 wins");}
  delay(10);
}
  
void generateGame()
{
  interval = random(1, 3000);	// Random milliseconds (to turn on LED)
  ledColour = random(1, 2); // Random colour (red or green)
  nextGame = false;			// Avoid generating new games until this one is done
}
  
void updateLed()
{
  currentMillis = millis(); // Store current time value
 
  // Handles case where more than interval time has passed since last game
  if (currentMillis - previousMillis >= interval) 
  {
    // save the last time LED blinked
    previousMillis = currentMillis;
    // Handles case where LED should go RED
    if (ledColour == COLOUR_RED) 
    {
      // Set led to RED value
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
    } 
    // Handles case where LED should go GREEN
    else if (ledColour == COLOUR_GREEN);
    {
      // Set led to GREEN value
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(RED_PIN, LOW);
    }
    nextGame = true; // Now we can generate a new game
  }
}
