void cPrint(String text)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(1);
  display.println(text);
  display.display();
}

void dMenu()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("1. Moon\n2. Distance \n3. Direction");
  display.display();
}

/* Direction from point*/

// theta is in radian
void drawDir(double length, double theta)
{
  int lengthOfLine = length > .5 ? 15 : 10;

  int toX = (int)(lengthOfLine * cos(theta));
  int toY = (int)(lengthOfLine * sin(theta));

  Serial.println(toX);
  Serial.println(toY);
  drawLineAndDistance(length, 0, 0, toX, toY);
}
void drawLineAndDistance(double length, int fromX, int fromY, int toX, int toY)
{
  display.clearDisplay();
  display.drawRect(64, 0, 64, 32, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Distance ");
  display.setCursor(0, 10);
  display.println(String(length, 4));
  display.setCursor(10, 20);
  display.println("KM");

  // 128*32 dispalcy size
  // 127 - 15 = 112
  // 31  - 15 = 16
  display.drawLine(96 + fromX * 2, 16 - fromY, 96 + toX * 2, 16 - toY, WHITE);
  display.display();
}

/* Moon set rise time*/
void beginMoon()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Enter date please\n");
  // display.setCursor(0, 1);
  display.println("Format: YYYYMMDD");
  display.display();
}

void updateMoon(String in)
{

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Date: YYYYMMDD");
  display.setCursor(34, 12);
  display.println(in);
  display.display();
}

void finalMoon(String in)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Set, Rise");
  display.setCursor(0, 12);
  display.println(in);
  display.display();
}
