# 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
# 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"



# 5 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino" 2
# 6 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino" 2

# 6 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 10, ((1 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/);
void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop(void)
{
  int red = 0;
  int blue = 0;
  int green = 0;
  int light = analogRead(A0);
  if (light > 0)
  {
    red = 175 + (light / 1024) * 50;
  }
  if (light > 70)
  {
    blue = 170 + (light / 1024) * 50;
  }
  int delay = 75;
  flow(delay, red, green, blue);
}

void flow(int del, int red, int green, int blue)

{
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      float scale = ((i - j)>0?(i - j):-(i - j));
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
  for (int i = (10 - 2); i > 0; i--)
  {
    for (int j = 0; j < 10; j++)
    {
      float scale = ((i - j)>0?(i - j):-(i - j));
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
