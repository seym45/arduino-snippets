void moon()
{
  beginMoon();
  String ymd = getymd();
  String r = fileContents(makeFileName(ymd));
  finalMoon(r);
  bGetKey();
  reset = true;
}
