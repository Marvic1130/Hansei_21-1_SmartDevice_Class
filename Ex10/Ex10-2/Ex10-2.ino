#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h> 

DHT dht(16, DHT11);
const char* ssid = "ssid"; // 와이파이 ssid
const char* password = "*********"; // 와이파이 passworld
// 본인의 IP주소를 사용해야한다.
String serverName = "http://172.30.1.56:1880/update-sensor";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable),it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay){
    if(WiFi.status()== WL_CONNECTED){
        // 온습도 값 가져오기
        int temp = dht.readTemperature();
        int hum = dht.readHumidity(); 
        HTTPClient http;
        // 온습도 값을 문자열로 변환한다.
        String serverPath = serverName + "?temperature="+String(temp)+"&humidity="+String(hum);
        http.begin(serverPath.c_str());

        int httpResponseCode = http.GET();
        if (httpResponseCode>0){
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
        }
        else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    }
    else {
        Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
