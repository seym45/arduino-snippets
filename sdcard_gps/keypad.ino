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

double getLatLon(bool lat)
{
  Serial.println(lat ? "Lat ---- " : "Lon +++++");
  double num = 0;
  int deciaml = 0;

  updateDir(lat, String(num, 6));

  while (true)
  {
    char key = bGetKey();

    if (key == 'A')
    { // done takking input
      break;
    }
    else if (key == '*')
    {
      // cancel taking input
      return -1;
    }
    else if (key == 'D' && deciaml == 0)
    {
      deciaml++;
      Serial.println("Deciaml " + String(deciaml));
    }
    else if (key == 'C') // clear 
    {
      deciaml = 0;
      num = 0;
      Serial.println("Num: " + String(num, 6));
      Serial.println("Deciaml " + String(deciaml));
    }
    else
    {

      switch (key)
      {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        float val = (float)(key - '0');
        if (deciaml == 0)
          num = num * 10 + val;
        else
        {
          for (int i = 0; i < deciaml; i++)
            val /= 10;
          num = num + val;
          deciaml++;
        }
        break;

      default:
        break;
      }
    }
    Serial.println("Num -> " + String(num, 6));
    updateDir(lat, String(num, 6));
  }
  return num;
}
