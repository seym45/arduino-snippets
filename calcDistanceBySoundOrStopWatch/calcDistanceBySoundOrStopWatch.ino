//SOund max diff
#define THRESH 600

//mode
volatile bool mode = 1;
bool prevMode = 1;
#define modeButton 3

volatile bool command = 1;
bool prevCommand = 1;

#define controlButton 2

// Variables will change:
int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = HIGH; // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

//temp
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 1
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(1);
  display.println("Starting ...");
  display.display();

  pinMode(controlButton, INPUT_PULLUP);
  pinMode(modeButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(controlButton), controlFn, FALLING);
  attachInterrupt(digitalPinToInterrupt(modeButton), modeFn, FALLING);
  millisDelay(200);
}

float temp()
{
  return dht.readTemperature();
}

// stopWatchMode
// 0 = start
// 1 = end, display distance
// 2 = reset, display to start
int stopWatchMode = 2;


boolean displayed2 = false;
boolean displayed1 = false;

void loop()
{
  // Read control button
  //  controlFn();

  // stopwatch mode selection
  if (command != prevCommand)
  {
    prevCommand = command;
    stopWatchMode++;
    stopWatchMode = stopWatchMode % 3;
  }

  if (mode != prevMode) {
    Serial.println(mode);
    prevMode = mode;
    stopWatchMode = 2;
    end_();
    display_();
  }

  switch (stopWatchMode)
  {
    case 0:
      start_();
      displayed1 = false;
      displayed2 = false;
      break;
    case 1:
      if (!displayed1)end_();
      displayed1 = true;
      displayed2 = false;
      break;
    case 2:
      if (!displayed2)display_();
      displayed1 = false;
      displayed2 = true;
      break;
    default:
      break;
  }

  //  Serial.println(stopWatchMode);
}

//void controlFn() {
//  command = !command;
//  delay(100);
//}

unsigned long startTime;
unsigned long airTime;
boolean beginTimer = false;

void end_()
{
  airTime = millis() - startTime ;
  float soundVelocity = 333.3 + 0.6 * (temp() - 10);
  float totalDisplacement = soundVelocity * ((airTime + .1) / 1000.0);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("T: " + String((airTime) / 1000.0, 2));
  display.setCursor(60, 0);
  display.println("Tmp: " + String(temp(), 2));

  display.setTextSize(2);
  display.println(String(totalDisplacement, 2) + "M");
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.println("Press to RESET");
  display.display();

  beginTimer = false; // To stop updating time in start function
}

void start_()
{
  // Two mode {begin timer, updatetimer}
  if (beginTimer == false)
  {
    startTime = millis();
    beginTimer = true; // made true in end_() function
    // Try Auto Mode
    if (mode == 0) {
      auto_();
    }
  }
  else // update display, timer
  {
    //    Serial.println("Start display");
    airTime = millis() - startTime;

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Time: " + String(airTime / 1000.0, 2));
    display.setCursor(70, 0);
    if (mode == 0)
      display.println("M: Auto");
    else
      display.println("M:Manual");

    display.setCursor(0, 8);
    display.setTextSize(1);

    int soundInt = analogRead(3);

    display.println("Sound Int: " + String(soundInt));
    display.setCursor(0, 24);
    display.setTextSize(1);
    display.println("Press to STOP!");
    display.display();
  }
}

void display_()
{
  //  Serial.println("Dispalyed Press");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  if (mode == 0)
    display.println("Mode: Auto");
  else
    display.println("Mode: Manual");
  display.setCursor(0, 16);
  display.setTextSize(1);
  display.print("Press to start!");
  display.display();
  millisDelay(10);
}

void display_failure()
{
  //  Serial.println("Dispalyed Press");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  if (mode == 0)
    display.println("Mode: Auto");
  else
    display.println("Mode: Manual");
  display.setCursor(0, 16);
  display.setTextSize(1);
  display.print("Failed to recognize");
  display.display();
  millisDelay(10);
}

void auto_() {

  int soundLevel;
  while (true) {
    airTime = millis() - startTime;
    if (airTime > 15000) { // 15 sec or 5KM around
      display_failure();
      millisDelay(5000);
      break;
    }

    soundLevel = getSoundLevel();
    if (soundLevel > THRESH) {
      break;
    }
  }

  // push to end
  stopWatchMode = 2;
}


int getSoundLevel() {

  int level = 0;
  int lastLevel = 0;
  int diff = 0;
  int mx = 0;
  for (int i = 0; i < 100; i++) {
    level = analogRead(1);
    diff = abs(level - lastLevel);
    if (diff > mx)mx = diff;
  }
  return mx;

}

static unsigned long mode_last_interrupt_time = 0;

void modeFn() {
  unsigned long mode_interrupt_time = millis();
  //  Serial.println(mode_last_interrupt_time, mode_interrupt_time);
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (mode_interrupt_time - mode_last_interrupt_time > 200)
  {
    mode = !mode;
    Serial.println("Dispalyed Mode");

  }
  mode_last_interrupt_time = mode_interrupt_time;
}
//void modeFn() {
//}

static unsigned long last_interrupt_time = 0;
void controlFn() {
  int reading = digitalRead(controlButton);
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    //    if (reading == LOW)
    command = !command;
  }
  last_interrupt_time = interrupt_time;
}

void millisDelay(long ms)
{
  unsigned long x = millis();
  while ((millis() - x) < ms)
  {
  }
}
