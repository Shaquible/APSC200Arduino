void setup()
{
    Serial.begin(9600);
    Serial.println("Hello World!");
}

void loop()
{
    Serial.println(analogRead(A0));
}