// 4주차 스마트디바이스
// 외부 led 점멸 실습1

int led = 22;

void setup()
{
    pinMode(led, OUTPUT);
}

void loop()
{
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
}