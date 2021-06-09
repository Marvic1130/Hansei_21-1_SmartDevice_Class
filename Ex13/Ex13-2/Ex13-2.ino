#include <WiFi.h>
#include <DHT.h>

const char* ssid = "iptime";
const char* password = NULL;

WiFiServer server(80);

String header;
DHT dht(16, DHT11);

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

                        client.println("<!DOCTYPE html><html lang=\"kr\"><head>");
                        client.println("<meta charset=\"UTF-8\">");
                        client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                        client.println("<title>ESP32 Web Server</title>");
                        client.println("<link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">");
                        client.println("<style> html{");
                        client.println("font-family: Arial;");
                        client.println("display: inline-block;");
                        client.println("margin: 0px auto;");
                        client.println("text-align: center;}");
                        client.println("h2 {font-size: 3.0rem;}");
                        client.println("p {font-size: 3.0rem;}");
                        client.println(".units {font-size: 1.2rem;}");
                        client.println(".dht-labels{");
                        client.println("font-size: 1.5rem;");
                        client.println("vertical-align:middle;");
                        client.println("padding-bottom: 15px;}</style>");
                        client.println("</head><body><h2>ESP32 DHT Server</h2>");
                        client.println("<p><i class=\"fas fa-thermometer-half\" style=\"color:#059e8a;\"></i>");
                        client.println("<span class=\"dht-labels\">Temperature</span> ");
                        client.println("<span id=\"temperature\">" + String(temp) + "</span>");
                        client.println("<sup class=\"units\">&deg;C</sup></p>");
                        client.println("<p><i class=\"fas fa-tint\" style=\"color:#00add6;\"></i>");
                        client.println("<span class=\"dht-labels\">Humidity</span>");
                        client.println("<span id=\"humidity\">" + String(humid) + "</span>");
                        client.println("<sup class=\"units\">&percnt;</sup></p>");
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
