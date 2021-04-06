#include <DHT.h> // 온습도 센서 라이브러리

DHT dht(22, DHT11); // 온습도 객체 생성

void setup(){
    Serial.begin(115200); // 시리얼 모니터 보드레이트 설정
}

void loop(){
    double temp = dht.readTemperature(); // 온습도센서에서 온도를 가져옴
    double hum = dht.readHumidity(); // 온습도센서에서 습도를 가져옴
    
    // 시리얼 모니터 출력
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println('C');
    Serial.print("Humidity: ");
    Serial.println(hum);
    delay(500); // 500ms 대기
}
