void distance()
{
    // start
    startDistanceDisplay();
    char key = bGetKey();
    if (key != 'A')
    {
        return;
    }
    double minutesElapsed = 0;
    unsigned startTime = millis();
    totalDistance = 0;

    Serial.println("Start time " + String(startTime));
    updateDistanceDisplay(0);

    // update with GPS and calc distance
    while (true)
    {
        Serial.println("running sdistance() loop");

        // if distance = 0 break
        if (reset) // press any key to get back
        {
            Serial.println("Returning from distance() loop");
            break;
        }
        updateAndCalcTotalDistance(); // has delay inside
        minutesElapsed = (millis() - startTime) / (1000 * 60.0);
        updateDistanceDisplay(minutesElapsed);
    }
    minutesElapsed = abs(millis() - startTime) / (1000 * 60.0);
    finishDistance(minutesElapsed);
    bGetKey(); // wait to return
}

void updateAndCalcTotalDistance()
{
    int N_LOCATION_POINTS = 5;
    // get avg of N_LOCATION_POINTS location points
    double sumLat = 0.0, sumLon = 0;
    for (int i = 0; i < N_LOCATION_POINTS; i++)
    {
        gpsLocationUpdate();
        sumLat += gLat;
        sumLon += gLon;
        millisDelay(AVG_POINT_CALC_DELAY);
        char key = k.getKey();
        if (reset)
            return;
    }
    avgLat = sumLat / (1.0 * N_LOCATION_POINTS);
    avgLon = sumLon / (1.0 * N_LOCATION_POINTS);
    // Serial.print("avgLat ");
    // Serial.print(avgLat);
    // Serial.print("\tavgLon ");
    // Serial.println(avgLon);

    // calc distance
    totalDistance += distanceInKm(gLat, gLon, avgLat, avgLon);
}