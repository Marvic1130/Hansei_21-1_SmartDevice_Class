void setup(){
    Serial.begin(115200); // 시리얼모니터 보드레이트를 115200으로 설정
}

void loop(){
    Serial.println(analogRead(A0)); // 조도센서의 값을 읽어와서 시리얼모니터에 출력
    delay(500);
}