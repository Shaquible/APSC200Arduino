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
  for (int i = 0; i < 3; i++)
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
  changeO3();
  changeSO2();
  changeNO2();
  breatheIn();
  breatheOut();
}

int d_time(int del)
{
  return map(del, 80, 1023, 50, 175);
}
void breatheIn(void)
{
  for (int i = LED_COUNT - 1; i >= 0; i--)
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
        uint32_t color;
        if (j >= i)
          color = strip1.Color(colors[h][0][0] * scale, colors[h][0][1] * scale, colors[h][0][2] * scale);
        else
          color = strip1.Color(colors[h][1][0] * scale, colors[h][1][1] * scale, colors[h][1][2] * scale);
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
    delay(d_time(analogRead(Speed_PIN)));
  }
}
void breatheOut(void)
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
        uint32_t color;
        if (j <= i)
          color = strip1.Color(colors[h][1][0] * scale, colors[h][1][1] * scale, colors[h][1][2] * scale);
        else
          color = strip1.Color(colors[h][0][0] * scale, colors[h][0][1] * scale, colors[h][0][2] * scale);
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
    delay(d_time(analogRead(Speed_PIN)));
  }
}

void changeO3()
{
  int o3Value = analogRead(O3_PIN);

  colors[0][0][0] = 200;
  colors[0][0][1] = 0;
  colors[0][0][2] = 200;

  if (o3Value < 400)
  {
    colors[0][1][0] = 200;
    colors[0][1][1] = 0;
    colors[0][1][2] = 0;
  }
  else
  {
    colors[0][1][0] = 200;
    colors[0][1][1] = 200;
    colors[0][1][2] = 200;
  }
}

void changeNO2()
{
  int no2Value = analogRead(NO2_PIN);

  colors[1][0][0] = 0;
  colors[1][0][1] = 200;
  colors[1][0][2] = 200;

  if (no2Value < 400)
  {
    colors[1][1][0] = 200;
    colors[1][1][1] = 0;
    colors[1][1][2] = 0;
  }
  else
  {
    colors[1][1][0] = 200;
    colors[1][1][1] = 200;
    colors[1][1][2] = 200;
  }
}

void changeSO2()
{
  int so2Value = analogRead(SO2_PIN);

  colors[2][0][0] = 0;
  colors[2][0][1] = 200;
  colors[2][0][2] = map(so2Value, 80, 1023, 20, 50);

  if (so2Value < 400)
  {
    colors[2][1][0] = 200;
    colors[2][1][1] = 0;
    colors[2][1][2] = 0;
  }
  else
  {
    colors[2][1][0] = 200;
    colors[2][1][1] = 200;
    colors[2][1][2] = 200;
  }
}
