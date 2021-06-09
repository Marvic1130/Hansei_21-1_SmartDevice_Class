#include <WiFi.h>
#include <DHT.h>

DHT dht(16, DHT11);
char* ssid = "KT_GiGA_2G_Wave2_79CA";
const char* password = "dx3adg9555";
WiFiServer server(80);
String header;

unsigned long currentTime = millis();

unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup(){
    Serial.begin(115200);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // WiFi 연결 후 IP 주소 출력
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop(){
    WiFiClient client = server.available();

    if (client) {                             // 만약 접속이 감지되면
        currentTime = millis();                 // 프로그램 실행 후 지난 시간을 얻어온다
        previousTime = currentTime;
        Serial.println("New Client.");          // 시리얼 모니터에 출력
        String currentLine = "";                // 클라이언트에서 들어오는 데이터를 저장할 문자열 생성
        while (client.connected() && currentTime - previousTime <= timeoutTime) {  // 클라이언트가 접속해있을 때 반복
            currentTime = millis();
            if (client.available()) {             // 만약 클라이언트에서 읽을 바이트가 있다면
                char c = client.read();             // 바이트를 읽고
                Serial.write(c);                    // 그 바이트를 시리얼 모니터에 출력
                header += c;
                if (c == '\n') {                    // 만약 바이트가 '\n'일 경우
                // 현재 행이 비어있을 경우
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        float temp = dht.readTemperature();
                        float humid = dht.readHumidity();
                        float fahre = 1.8*temp+32;

                        client.println("<!DOCTYPE html><html lang=\"kr\"><head>");
                        client.println("<meta charset=\"UTF-8\">");
                        client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                        client.println("<title>ESP32 Web Server</title>");
                        client.println("<style>*{text-align: center; background-color: #333333; color: white; margin: 20px auto;}");
                        client.println("th{text-align: left;}</style></head>");
                        client.println("<body><h1>ESP32 Web Server</h1>");
                        client.println("<h1>Reading sensor value </h1>");
                        client.println("<h2>DHT11</h2>");
                        client.println("<h3>Hansei Uni. Smart Device Lab</h3>");
                        client.println("<table><tr>");
                        client.println("<th><h4>MEASUREMENT</h4></th>");
                        client.println("<th><h4>VALUE</h4></th></tr>");
                        client.println("<tr><th>Temp.Celsius</th>");
                        client.println("<th>" + String(temp) + "*C</th></tr>");
                        client.println("<tr><th>Temp.Fahrenheit</th>");
                        client.println("<th>" + String(fahre) + " *F</th></tr>");
                        client.println("<tr><th>Humidity</th>");
                        client.println("<th>" + String(humid) + "%</th></tr></table>");
                        client.println("</body></html>");

                        client.println();
                        break;
                    }
                    else {
                        currentLine = "";
                    }
                }
                else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
    }
}

