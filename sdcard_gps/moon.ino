void moon()
{
  beginMoon();
  String ymd = getymd();
  finalMoon(fileContents(makeFileName(ymd)));
}
