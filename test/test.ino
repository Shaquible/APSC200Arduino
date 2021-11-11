#define Temp_Pin A0
#define LED_COUNT 10
#define LED_PIN 13
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
void setup()
{
  Serial.begin(9600);

  strip.begin();
  strip.show();
}

void loop(void)
{

  for (int i = 0; i < 10; i++)
  {
    uint32_t blue = strip.Color(0, 0, 10);
    strip.fill(blue, 0, 10);
    strip.setPixelColor(i, 0, 0, 128);
    strip.setPixelColor(i - 1, 0, 0, 70);
    strip.setPixelColor(i + 1, 0, 0, 70);
    strip.show();
    delay(100);
  }
}
