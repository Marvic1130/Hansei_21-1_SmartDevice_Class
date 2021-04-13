#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define LED2 27

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test");
  Serial.println("The device started, now you can pair it with bluetooth!");
  
  pinMode(LED2, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
  if (SerialBT.available()) {
    char txt = SerialBT.read();
    Serial.write(txt);
    if(txt == 'o'){
        digitalWrite(LED2, HIGH);
    } else if(txt == 'x'){
        digitalWrite(LED2, LOW);
    }
  }
  delay(20);
}
