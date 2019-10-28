// blockingGetKey()
char bGetKey()
{
  while (true)
  {
    char key = k.getKey();
    if (key)
    {
      Serial.print("Pressed: ");
      Serial.println(key);
      return key;
    }
  }
}

void dgetymd()
{
}

String getymd()
{
  String res = "";
  while (res.length() != 8)
  {
    char key = bGetKey();
    res += String(key);
    Serial.println(res);
    updateMoon(res);
  }

  return res;
}

char getMenuOption()
{
  return bGetKey();
}
