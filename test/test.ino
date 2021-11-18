#define O3_PIN A0    //For O3 sensor
#define SO2_PIN A1   //For SO2 sensor
#define NO2_PIN A2   //For NO2 sensor
#define Speed_PIN A3 //Speed value for potentiometer
#define LED_COUNT 10
#define LED_PIN1 10
#define LED_PIN2 9
#define LED_PIN3 8
#include <Adafruit_NeoPixel.h>
#include <math.h>
//O3, NO2, SO2/ in, out/ r,g,b
int colors[3][2][3]; //3 strips, 2 in/out colours, 3 RGB values

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(LED_COUNT, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(LED_COUNT, LED_PIN3, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  for (int i = 0 i < 3; i++)
  {
    switch (i)
    {
    case 0:
      strip1.begin();
      strip1.show();
      break;
    case 1:
      strip2.begin();
      strip2.show();
      break;
    case 2:
      strip3.begin();
      strip3.show();
      break;
    }
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
        uint32_t color = strip1.Color(colors[h][0][0] * scale, colors[h][0][1] * scale, colors[h][0][2] * scale);
        switch (h)
        {
        case 0:
          strip1.setPixelColor(j, color);
          break;
        case 1:
          strip2.setPixelColor(j, color);
          break;
        case 2:
          strip3.setPixelColor(j, color);
          break;
        }
      }
    }
    for (int h = 0; h < 3; h++)
    {
      switch (h)
      {
      case 0:
        strip1.show();
        break;
      case 1:
        strip2.show();
        break;
      case 2:
        strip3.show();
        break;
      }
    }
    delay(del);
  }
}
void breatheOut(int del)
{
  for (int i = (LED_COUNT - 1); i > -1; i++)
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
        uint32_t color = strip1.Color(colors[h][1][0] * scale, colors[h][1][1] * scale, colors[h][1][2] * scale);
        switch (h)
        {
        case 0:
          strip1.setPixelColor(j, color);
          break;
        case 1:
          strip2.setPixelColor(j, color);
          break;
        case 2:
          strip3.setPixelColor(j, color);
          break;
        }
      }
    }
    for (int h = 0; h < 3; h++)
    {
      switch (h)
      {
      case 0:
        strip1.show();
        break;
      case 1:
        strip2.show();
        break;
      case 2:
        strip3.show();
        break;
      }
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
