#define LED 14

void setup() {
    Serial.begin(112500);
    pinMode(LED, OUTPUT);
}

void loop() {
    // 전압과 저항 산출부
    float vol = float(map(analogRead(A0), 0, 4095, 0, 1023)*5)/1024; // 조도센서값을 이용하여 전압 구하기

    // 시리얼 모니터에 전압 출력
    Serial.print(vol);
    Serial.println("volt");

    if(vol > 3.5){
        digitalWrite(LED, HIGH);
        Serial.println("LED ON");
    }
    else{
        digitalWrite(LED, LOW);
        Serial.println("LED OFF");
    }

    delay(500);
}
