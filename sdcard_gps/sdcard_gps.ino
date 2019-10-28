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

  // pinMode(CS_pin, OUTPUT); //declaring CS pin as output pin
  // if (SD.begin())
  // {
  //   Serial.println("SD card is initialized and it is ready to use");
  // }
  // else
  // {
  //   Serial.println("SD card is not initialized");
  //   return;
  // }

  // GPS
  Serial3.begin(9600);

  // keypad
  pinMode(ledPin, OUTPUT);         // Sets the digital pin as output.
  digitalWrite(ledPin, HIGH);      // Turn the LED on.
  k.addEventListener(keypadEvent); // Add an event listener for this keypad

  cPrint("Press *");
}

bool reset = false;
void loop()
{

  //  gpsTest();
  // menu();
  // moon();

  double ty = 23.810886;
  double tx = 90.401562;
  double cy = 23.778311;
  double cx =90.396063;


  double dy = ty - cy;
  double dx = tx - cx;
  double direction = atan2(dy, dx);
  double distance = distanceInKm(ty, tx, cy, cx);
  Serial.println(distance);
  Serial.println(direction);
  drawDir(distance, direction);
  
  delay(1000000);
}

void menu()
{
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
