#include <WiFi.h>
#include <DHT.h> // 온습도 센서 라이브러리
#include <ThingSpeak.h>
char* ssid = "KT_GiGA_2G_Wave2_79CA";
const char* password = "dx3adg9555";
WiFiClient client; //Thingspeak에 접속할 WiFi 객체 생성
unsigned long ch1_ID = 1383273; //채널ID
const char* ch1_WriteKey = "FWN377CSH5VU8WJI";
DHT dht(16, DHT11); // 온습도 객체 생성


//채널 WriteKey
void setup() {
    Serial.begin(115200); //시리얼 통신 시작
    delay(10);
    initWiFi(); //WiFi 초기화
    ThingSpeak.begin(client);
    //WiFi 객체로 Thingspeak와 통신 시작
}
void loop() {
    int temp = dht.readTemperature(); // 온습도센서에서 온도를 가져와 변수에 저장
    ThingSpeak.writeField(ch1_ID, 1, temp, ch1_WriteKey);
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println('C');
    delay(15000);
    
    int hum = dht.readHumidity(); // 온습도센서에서 습도를 가져와 변수에 저장
    ThingSpeak.writeField(ch1_ID, 2, hum, ch1_WriteKey);
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("%");
    delay(15000);
}
    void initWiFi() {
    WiFi.begin(ssid, password);
    //입력받은 ID,PASSWORD로 WiFi 시작
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println(".");
        //WiFi가 접속될때까지 Serial에 . 을 입력
    }
}
