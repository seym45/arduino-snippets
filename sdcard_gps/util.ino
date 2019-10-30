void millisDelay(long ms)
{
    unsigned long x = millis();
    while ((millis() - x) < ms)
    {
        char key = k.getKey();
        if (reset)
            return;
    }
}