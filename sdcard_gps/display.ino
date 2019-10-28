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
