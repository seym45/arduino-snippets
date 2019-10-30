double targetYLat;
double targetXLon;

void direction()
{
  // get target direction
  getTargetLocationAndDraw();
  
  if(reset)return;

  delay(UPDATE_DIRECTION_INTERAL);
  // update with GPS
  while (true)
  {
    // if distance = 0 break
    if (k.getKey()) // press any key to get back
    {
      reset = true;
      Serial.println("Returning from direction() loop");
      break;
    }
    updateDirection();
    delay(UPDATE_DIRECTION_INTERAL);
  }
}

void getTargetLocationAndDraw()
{
  beginDir();
  bGetKey(); // Wait untill key is pressed

  // double ty = 23.810886; // lat
  // double tx = 90.401562; // lon
  // double cy = 23.778311; // lat
  // double cx =90.396063;  // lon

  double ty = targetYLat = getLatLon(true); // lat
  if (ty == -1)
  {
    reset = true;
    return;
  }

  double tx = targetXLon = getLatLon(false); // lon
  if (tx == -1)
  {
    reset = true;
    return;
  }

  gpsLocationUpdate();

  double cy = gLat; // lat
  double cx = gLon; // lon

  double dy = ty - cy;
  double dx = tx - cx;
  double direction = atan2(dy, dx);
  double distance = distanceInKm(ty, tx, cy, cx);
  Serial.println(distance);
  Serial.println(direction);

  // relative TO north POLE
  double relativeDirection;
  double directionDegree = direction * (180 / PI);
  Serial.println("directionDegree " + String(directionDegree, 2));
  if (dx < 0 && dy >= 0) // 2nd Quadrant
  {
    relativeDirection = 360 - (directionDegree - 90);
  }
  else
  {
    relativeDirection = 90 - directionDegree;
  }

  drawDir(distance, direction, relativeDirection);
}

void updateDirection()
{

  double ty = targetYLat;
  double tx = targetXLon;

  gpsLocationUpdate();

  double cy = gLat; // lat
  double cx = gLon; // lon

  double dy = ty - cy;
  double dx = tx - cx;
  double direction = atan2(dy, dx);
  double distance = distanceInKm(ty, tx, cy, cx);
  Serial.println(distance);
  Serial.println(direction);

  // relative TO north POLE
  double relativeDirection;
  double directionDegree = direction * (180 / PI);
  Serial.println("directionDegree " + String(directionDegree, 2));
  if (dx < 0 && dy >= 0) // 2nd Quadrant
  {
    relativeDirection = 360 - (directionDegree - 90);
  }
  else
  {
    relativeDirection = 90 - directionDegree;
  }

  drawDir(distance, direction, relativeDirection);

  // delay(1000000);
}
