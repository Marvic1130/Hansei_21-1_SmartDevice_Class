 // 4주차 스마트 디바이스 실습
// 외부LED 점멸 실습2

int led1 = 27;
int led2 = 25;

void setup()
{
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}

void loop()
{
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(500);
}
