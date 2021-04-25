#include "WiFi.h"
#include "DHT.h"

WiFiClient client;
const char* server = "api.thingspeak.com";
String apiKey = "***************"; // Write API Key
char* ssid = "*********"; // WiFi ssid
const char* password = "************"; // WiFi password

int sent = 0;
int pin = 17;

DHT dht(pin, DHT11);
void setup() 
{
    Serial.begin(115200);
    delay(10);
    Serial.println("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(300);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
}

void loop(){
    String temp, humi;
    
    temp = String(dht.readTemperature());
    humi = String(dht.readHumidity());
    Serial.print("temerature: ");
    Serial.print(temp);
    Serial.println("C");
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.println("%");

    if(client.connect(server, 80)){
        Serial.println("WiFi Client connected");
        Serial.print(String(sent)+" Temperature: ");
        Serial.print(temp);
        Serial.println("C");
        Serial.print(String(sent)+" Humidity: ");
        Serial.print(humi);
        Serial.println("%");
        String postStr = apiKey;
        postStr += "&field1=";
        postStr += String(temp);
        postStr += "\r\n\r\n";
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
        delay(1000);
    }
    delay(15000);
    client.stop();
    if (client.connect(server, 80)){
        String humidStr = apiKey;
        humidStr += "&field2=";
        humidStr += String(humi);
        humidStr += "\r\n\r\n";
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(humidStr.length());
        client.print("\n\n");
        client.print(humidStr);
        delay(1000);
    }

    sent++;
    delay(15000);
    client.stop();
}
