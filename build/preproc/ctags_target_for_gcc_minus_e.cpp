# 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
# 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"






# 8 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino" 2
# 9 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino" 2

# 9 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
//O3, NO2, SO2/ in, out/ r,g,b
int colors[3][2][3]; //3 strips, 2 in/out colours, 3 RGB values

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 10, ((1 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/);

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 3; i++)
  {
    strip.begin();
    strip.show();
  }
}

void loop(void)
{
  int delay = analogRead(A1 /*Speed value for potentiometer*/);
  delay = map(delay, 80, 1023, 50, 175);
  changeO3();
  breatheIn(delay);
  breatheOut(delay);
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

void breatheIn(int del)
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
      for (int h = 0; h < 3; h++)
      {
        uint32_t color = strip.Color(colors[h][0][0] * scale, colors[h][0][1] * scale, colors[h][0][2] * scale);
        strip.setPixelColor(j, color);
      }
    }
    for (int h = 0; h < 3; h++)
    {
    }
    delay(del);
  }
}
void breatheOut(int del)
{
  for (int i = (10 - 1); i < -1; i--)
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
      for (int h = 0; h < 3; h++)
      {
        uint32_t color = strip.Color(colors[h][0][0] * scale, colors[h][0][1] * scale, colors[h][0][2] * scale);
        strip.setPixelColor(j, color);
      }
    }
    for (int h = 0; h < 3; h++)
    {
      strip.show();
    }
    delay(del);
  }
}

void changeO3()
{
  int o3Value = analogRead(A0 /*For O3 sensor*/);

  colors[0][0][0] = map(o3Value, 80, 1023, 20, 200);
  colors[0][0][1] = 0;
  colors[0][0][2] = map(o3Value, 80, 1023, 20, 200);

  if (o3Value < 400)
  {
    colors[0][1][0] = map(o3Value, 80, 1023, 20, 50);
    colors[0][1][1] = 0;
    colors[0][1][2] = 0;
  }
  else
  {
    colors[0][1][0] = map(o3Value, 80, 1023, 20, 200);
    colors[0][1][1] = map(o3Value, 80, 1023, 20, 200);
    colors[0][1][2] = map(o3Value, 80, 1023, 20, 200);
  }
}

void changeNO2()
{
}

void changeSO2()
{
}