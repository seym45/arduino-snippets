String makeFileName(String ymd)
{
  String y = ymd.substring(0, 4);
  String m = ymd.substring(4, 6);
  String d = ymd.substring(6, 8);

  String filename = y + "/" + m + "/" + d + ".csv";
  Serial.println("Filename: " + filename);
  return filename;
}

String fileContents(String name)
{

  sdcard_file = SD.open(name);
  String buffer = "Not found";

  if (sdcard_file)
  {
    int currentLine = 0;
    if (sdcard_file.available())
    {
      buffer = sdcard_file.readStringUntil(';');
      Serial.println("Contents: " + buffer); //Printing for debugging purpose
    }
    sdcard_file.close();
  }
  else
  {
    Serial.println("Failed to open the file");
  }
  return buffer;
}

String fileContentsByLine(String name, int line)
{

  sdcard_file = SD.open(name);
  if (sdcard_file)
  {
    int currentLine = 0;
    while (sdcard_file.available())
    {
      String buffer;
      currentLine++;
      buffer = sdcard_file.readStringUntil('\n');

      if (currentLine == line && buffer.length())
      {
        return buffer;
      }
      //      Serial.println(buffer); //Printing for debugging purpose
    }
    sdcard_file.close();
  }
  else
  {
    Serial.println("Failed to open the file");
  }

  return "Not found";
}

//
//  Serial.println("SD card is not initialized 00000");
//  Serial.println(fileContentsByLine("2019/10.csv", 0));
//
//
//  Serial.println("SD card is not initialized11111");
//
//  Serial.println(fileContentsByLine("2019/10.csv", 1));
//
//
//  Serial.println("SD card is not initialized222222");
//
//  Serial.println(fileContentsByLine("2019/10.csv", 2));
//
//
//
//  Serial.println("SD card is not initialized3333333");
//
//  Serial.println(fileContentsByLine("2019/10.csv", 3));
//  Serial.println("SD card is not initialized3333334");
//
//  Serial.println(fileContentsByLine("2019/10.csv", 4));

/*
20210503
20241208
20350101
20360305
20360913
20450721
20460129
20460726
20460809
20461105
20470104
20501106
20540429
20630929
20670802
20710223
20710323
*/