#include <Arduino.h>
#line 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
#line 1 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
#define Light_PIN A0
#define LED_COUNT 10
#define LED_PIN 10
#include <Adafruit_NeoPixel.h>
#include <math.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#line 7 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void setup();
#line 14 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void loop(void);
#line 32 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
void flow(int del, int red, int green, int blue);
#line 7 "c:\\Users\\skell\\Documents\\APSC200Arduino\\test\\test.ino"
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
  int light = analogRead(Light_PIN);
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

