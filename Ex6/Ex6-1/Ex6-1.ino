#include "BluetoothSerial.h"
#include "LiquidCrystal_I2C.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27
#define COL 16
#define ROW 2

BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd(0x27, COL, ROW);

bool redState = false;
bool greenState = false;
bool blueState = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test");
  Serial.println("The device started, now you can pair it with bluetooth!");

  lcd.init();
  lcd.backlight();
  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
  if(SerialBT.available()) {
    String s = SerialBT.readString();
    if(s == "help"){

    }
    if(s == "RedOn"){
        redState = true;
        digitalWrite(RED_LED, HIGH);
    }
    if(s == "GreenOn"){
        greenState = true;
        digitalWrite(RED_LED, HIGH);
    }
    if(s == "BlueOn"){
        blueState = true;
        digitalWrite(RED_LED, HIGH);
    }

  }
  delay(20);
}
