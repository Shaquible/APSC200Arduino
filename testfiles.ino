void flow(int del, int red, int green, int blue)

{
    for (int i = 0; i < LED_COUNT; i++)
    {
        for (int j = 0; j < LED_COUNT; j++)
        {
            float scale = abs(i - j);
            if (scale > 0)
            {
                scale = 1 / scale;
            }
            else
                scale = 1;
            uint32_t color = strip.Color(red * scale, green * scale, blue * scale);
            strip.setPixelColor(j, color);
        }
        strip.show();
        delay(del);
    }
    for (int i = (LED_COUNT - 2); i > 0; i--)
    {
        for (int j = 0; j < LED_COUNT; j++)
        {
            float scale = abs(i - j);
            if (scale > 0)
            {
                scale = 1 / scale;
            }
            else
                scale = 1;
            uint32_t color = strip.Color(red * scale, green * scale, blue * scale);
            strip.setPixelColor(j, color);
        }
        strip.show();
        delay(del);
    }
}