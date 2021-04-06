#include <DHT.h>
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
DHT dht(16, DHT11);
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
    lcd.init();        
    lcd.backlight();
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

    lcd.setCursor(0, 0);
    lcd.print("   Tempe:");
    lcd.print(temp);
    lcd.print("*c");
    lcd.setCursor(0,1);
    lcd.print("Humidity:");
    lcd.print(hum);
    lcd.print("%");
    
    delay(200);
    lcd.clear(); 
}
