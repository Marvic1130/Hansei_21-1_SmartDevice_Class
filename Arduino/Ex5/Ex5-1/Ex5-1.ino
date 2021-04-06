#include <DHT.h>

DHT dht(22, DHT11);

void setup(){
    Serial.begin(115200);
}

void loop(){
    double temp = dht.readTemperature();
    double hum = dht.readHumidity();
    
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println('C');
    Serial.print("Humidity: ");
    Serial.println(hum);
    delay(500);
}
