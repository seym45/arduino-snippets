void millisDelay(long ms)
{
  unsigned long x = millis();
  while ((millis() - x) < ms)
  {
  }
}