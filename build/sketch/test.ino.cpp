#include <Arduino.h>
#line 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
#line 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
#define O3_PIN A0    //For O3 sensor
#define Speed_PIN A1 //Speed value for potentiometer
#define NO2_PIN A2   //For NO2 sensor
#define SO2_PIN A3   //For SO2 sensor
#define LED_COUNT 10
#define LED_PIN1 10
#include <Adafruit_NeoPixel.h>
#include <math.h>
//O3, NO2, SO2/ in, out/ r,g,b
int colors[3][2][3]; //3 strips, 2 in/out colours, 3 RGB values

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);

#line 14 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void setup();
#line 24 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void loop(void);
#line 33 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void flow(int del, int red, int green, int blue);
#line 72 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void breatheIn(int del);
#line 97 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void breatheOut(int del);
#line 124 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void changeO3();
#line 146 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void changeNO2();
#line 150 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void changeSO2();
#line 14 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
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
  int delay = analogRead(Speed_PIN);
  delay = map(delay, 80, 1023, 50, 175);
  changeO3();
  breatheIn(delay);
  breatheOut(delay);
}

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

void breatheIn(int del)
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
  for (int i = (LED_COUNT - 1); i < -1; i--)
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
  int o3Value = analogRead(O3_PIN);

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

