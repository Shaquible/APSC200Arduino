#define Light_PIN A0
#define LED_COUNT 10
#define LED_PIN 10
#include <Adafruit_NeoPixel.h>
#include <math.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
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
  Serial.println(light);
  if (light > 0)
  {
    red = 175 + (light / 1024) * 50;
    blue = light * 50 / 1024;
  }
  if (light > 200)
  {
    blue = 175 + (light / 1024) * 50;
    red = 0;
  }
  int delay = 100;
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
