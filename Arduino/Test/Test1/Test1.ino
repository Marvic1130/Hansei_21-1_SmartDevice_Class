// WiFi.h 로드하기
#include <WiFi.h>

// WiFi Ssid, Password
char* ssid = "KT_GiGA_2G_Wave2_79CA";
const char* password = "dx3adg9555";

// 웹서버의 포트 넘버를 80으로 설정
WiFiServer server(80);

// HTTP 요청을 저장할 변수 선언
String header;

// led핀 번호 지정
const int red = 25;
const int green = 26;
const int blue = 27;
// led의 상태를 저장할 변수 선언 및 초기화
String redState = "off";
String greenState = "off";
String blueState = "off";


// 프로그램을 실행한 후 지난 ms 를 반환하는 변수를 생성
unsigned long currentTime = millis();

unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  // 시리얼 모니터 보드레이트를 115200으로 설정
  Serial.begin(115200);

  //핀 모드설정 && led끄기
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  // Set outputs to LOW
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);

  // WiFi연결
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
  WiFiClient client = server.available();   // 접속 감지

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
            // HTTP 헤더는 항상 응답코드(ex: HTTP/1.1 200 OK)로 시작한다
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // led 동작코드
            if (header.indexOf("GET /Red/on") >= 0) {
              Serial.println("GPIO Red on");
              redState = "on";
              digitalWrite(red, HIGH);
            } 
            else if (header.indexOf("GET /Red/off") >= 0) {
              Serial.println("GPIO Red off");
              redState = "off";
              digitalWrite(red, LOW);
            }
            else if (header.indexOf("GET /Green/on") >= 0) {
              Serial.println("GPIO Green on");
              greenState = "on";
              digitalWrite(green, HIGH);
            } 
            else if (header.indexOf("GET /Green/off") >= 0) {
              Serial.println("GPIO Green off");
              greenState = "off";
              digitalWrite(green, LOW);
            } 
            else if (header.indexOf("GET /Blue/on") >= 0) {
              Serial.println("GPIO Blue on");
              blueState = "on";
              digitalWrite(blue, HIGH);
            } 
            else if (header.indexOf("GET /Blue/off") >= 0) {
              Serial.println("GPIO Blue off");
              blueState = "off";
              digitalWrite(blue, LOW);
            }
            
            // HTML5
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<title>ESP32 Web Server</title>");
            // CSS
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>ESP32 Web Server</h1>");

            client.println("<p>GPIO Red - State " + redState + "</p>");
            if (redState=="off") {
              client.println("<p><a href=\"/Red/on\"><button class=\"button\">ON</button></a></p>");
            } 
            else {
              client.println("<p><a href=\"/Red/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            client.println("<p>GPIO Green - State " + greenState + "</p>");
            if (greenState=="off") {
              client.println("<p><a href=\"/Green/on\"><button class=\"button\">ON</button></a></p>");
            } 
            else {
              client.println("<p><a href=\"/Green/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
 
            client.println("<p>GPIO Blue - State " + blueState + "</p>");     
            if (blueState=="off") {
              client.println("<p><a href=\"/Blue/on\"><button class=\"button\">ON</button></a></p>");
            }
            else {
              client.println("<p><a href=\"/Blue/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            client.println();
            break;
          } 
          else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = ""; // 헤더 초기화
    // 서버 닫기
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
