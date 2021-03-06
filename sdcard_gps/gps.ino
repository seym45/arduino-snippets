
void gpsTest()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial3.available())
    {
      char c = Serial3.read();
            Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial.println();
  }

  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
}

double distanceInKm(double lat1, double lon1, double lat2, double lon2)
{
  double theta = lon1 - lon2;
  double dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
  dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515;
  return (dist);
}

double deg2rad(double deg)
{
  return (deg * PI / 180.0);
}

double rad2deg(double rad)
{
  return (rad * 180.0 / PI);
}

#ifdef DEBUG_DIRECTION
#define N 9
int lata[N] = {5, 10, 10, 10, 5, 0, 0, 0, 5};
int lona[N] = {5, 0, 5, 10, 10, 10, 5, 0, 0};
int ia = 0;
#endif

#ifdef DEBUG_DISTANCE
#define N 9
int lata[N] = {5, 10, 10, 10, 5, 0, 0, 0, 5};
int lona[N] = {5, 0, 5, 10, 10, 10, 5, 0, 0};
int ia = 0;
#endif

void gpsLocationUpdate()
{
  bool newData = false;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial3.available())
    {
      char c = Serial3.read();
      // Serial.write(c);   // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    // Serial.print("LAT=");
    // Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    // Serial.print(" LON=");
    // Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    // Serial.print(" SAT=");
    // Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    // Serial.print(" PREC=");
    // Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    // Serial.println();

    lastLat = gLat = flat;
    lastLon = gLon = flon;
  }
  else
  {
    gLat = 0;
    gLon = 0;
  }

#if defined(DEBUG_DIRECTION) || defined(DEBUG_DISTANCE)
  Serial.println("DEBUG");
  gLat = lata[ia];
  gLon = lona[ia];
  ia++;
  if (ia == N)
    ia = 0;
#endif

  Serial.print("Lat: ");
  Serial.print(gLat);
  Serial.print(" Lon: ");
  Serial.print(gLon);
  Serial.println();
}

void gpsTestWithDisplay()
{

  unsigned int startTime_ = millis();

  // view gps data
  while (true)
  {
    /* code */

    char key = k.getKey();

    if (key)
    {
      Serial.println("Completed GPS test");
      break;
    }
    gpsLocationUpdate();
    unsigned int secsElapsed = abs(millis() - startTime_) / (1000);
    if(secsElapsed > 10){
      Serial.println("yol");
      break;
    }
    Serial.println("sec elapsed: ");
    Serial.println(secsElapsed);
    testDisplayGPS(secsElapsed);
    millisDelay(1000);
  }
  reset = true;
}