#include <WiFi.h>
#include <ThingSpeak.h>
char* ssid = "KT_GiGA_2G_Wave2_79CA";
const char* password = "dx3adg9555";
WiFiClient client; //Thingspeak에 접속할 WiFi 객체 생성
unsigned long ch1_ID = 1383255; //채널ID
const char* ch1_WriteKey = "9GY70T00UCHGWBEB";
//채널 WriteKey
void setup() {
    Serial.begin(115200); //시리얼 통신 시작
    delay(10);
    initWiFi(); //WiFi 초기화
    ThingSpeak.begin(client);
    //WiFi 객체로 Thingspeak와 통신 시작
}

void loop() {
    int i;
    for (i = 0; i < 4; ++i)
    {
        ThingSpeak.writeField(ch1_ID, 1, i, ch1_WriteKey);
        //Thingspeak에 데이터 전송
        //인자로는 채널ID, 보낼필드, 보내려는 값, WriteKEY
        delay(15000);
    }
}

void initWiFi() {
    WiFi.begin(ssid, password);
    //입력받은 ID,PASSWORD로 WiFi 시작
    while (WiFi.status() != WL_CONNECTED) { //와이파이가 연결되어 있지 않을 동안
        delay(500);
        Serial.println(".");
        //WiFi가 접속될때까지 Serial에 . 을 입력
    }
}
