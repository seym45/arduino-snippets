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
  Serial.println("Display Menu");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("1. Moon\n2. Distance \n3. Direction");
  display.display();
}

/* Direction from point*/

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

void beginDir()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Enter Lat Lon\n");
  display.println("Press any key");
  display.display();
}

void updateDir(bool lat, String in)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (lat)
    display.println("Target \nLat: XX.XXXXX\n");
  else
    display.println("Target \nLon: XX.XXXXX\n");
  // display.setCursor(10, 12);
  display.println(in);
  display.display();
}

// Final Direction
// theta is in radian
void drawDir(double length, double theta, double relativeTheta)
{
  int lengthOfLine = length > .5 ? 15 : 10;

  int toX = (int)(lengthOfLine * cos(theta));
  int toY = (int)(lengthOfLine * sin(theta));

  Serial.println(toX);
  Serial.println(toY);
  drawLineAndDistance(length, relativeTheta, 0, 0, toX, toY);
}

void drawLineAndDistance(double length, double angle, int fromX, int fromY, int toX, int toY)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Distance ");
  display.setCursor(0, 10);
  display.println(String(length, 4));
  display.setCursor(0, 20);
  display.println("A: " + String(angle, 1));

  display.drawRect(64, 0, 64, 32, WHITE);
  // 128*32 dispalcy size
  // 127 - 15 = 112
  // 31  - 15 = 16
  display.drawLine(96 + fromX * 2, 16 - fromY, 96 + toX * 2, 16 - toY, WHITE);
  display.display();
}

void startDistanceDisplay()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Press A \nto start");
  display.display();
}

void updateDistanceDisplay(double time)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(String(avgLat, 6) + "," + String(avgLon, 6) + "\n");
  display.setCursor(0, 10);
  display.println("T Dis:" + String(totalDistance, 3) + " KM");
  display.setCursor(0, 20);
  // display.println("T Time:" + String(time, 1) + " m");

  display.display();
}


void finishDistance(double time)
{
  double d = totalDistance;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Finished \n");
  display.setCursor(0, 10);
  display.println("T Dis:" + String(d, 3) + " KM");
  display.setCursor(0, 20);
  // display.println("T Time:" + String(time, 1) + " m");

  display.display();
}
