#define UPDATE_DIRECTION_INTERAL 1000
#define AVG_POINT_CALC_DELAY 100

// #define DEBUG_DISTANCE // ENABLE to test 'direction' option with hardcoded value
// #define DEBUG_DIRECTION // ENABLE to test 'direction' option with hardcoded value

#include <SD.h>
#include <SPI.h>
#include <math.h>
File sdcard_file;
int CS_pin = 53;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 1
Adafruit_SSD1306 display(OLED_RESET);

#include <TinyGPS.h>
TinyGPS gps;
double gLat, gLon;       // global current location
double lastLat, lastLon; // last known location
double avgLat, avgLon;   // last valid avg location
double totalDistance = 0;

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {35, 33, 31, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {27, 25, 23, 37}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad k = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
byte ledPin = 13;

boolean blink = false;
boolean ledPin_state;

void setup()
{

  // Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  cPrint("Starting...");
  Serial.begin(9600); //Setting baudrate at 9600

  pinMode(CS_pin, OUTPUT); //declaring CS pin as output pin
  if (SD.begin())
  {
    Serial.println("SD OK");
  }
  else
  {
    Serial.println("SD FAILED");
    return;
  }

  // GPS
  Serial3.begin(9600);

  // keypad
  pinMode(ledPin, OUTPUT);         // Sets the digital pin as output.
  digitalWrite(ledPin, HIGH);      // Turn the LED on.
  k.addEventListener(keypadEvent); // Add an event listener for this keypad

  // cPrint("Press *");
}

// void loop()
// {
//   gpsTest();
//   millisDelay(1000);
// }

bool reset = true;
void loop()
{

  //  gpsTest();
  // menu();
  // moon();
  char key = k.getKey();

  if (key)
  {
    Serial.println(key);
  }
  if (blink)
  {
    digitalWrite(ledPin, !digitalRead(ledPin)); // Change the ledPin from Hi2Lo or Lo2Hi.
    delay(100);
  }

  if (reset)
  {
    reset = false;
    dMenu();
    switch (getMenuOption())
    {
    case '1':
      moon();
      break;
    case '2':
      distance();
      break;
    case '3':
      direction();
      break;
    case '4':
      gpsTestWithDisplay();
      break;
    default:
      reset = true; // open main menu again
      break;
    }
  }
}

void menu()
{
  if (blink)
  {
    digitalWrite(ledPin, !digitalRead(ledPin)); // Change the ledPin from Hi2Lo or Lo2Hi.
    delay(100);
  }

  if (reset)
  {
    reset = false;
    dMenu();
    switch (getMenuOption())
    {
    case '1':
      moon();
      break;
    case '2':
      distance();
      break;
    case '3':
      direction();
      break;
    default:
      reset = true; // open main menu again
      break;
    }
  }
}
// Taking care of some special events.
void keypadEvent(KeypadEvent key)
{
  switch (k.getState())
  {
  case HOLD:
    if (key == '*')
    {
      reset = true;
      blink = true; // Blink the LED when holding the * key.
    }

    break;
  }
}
