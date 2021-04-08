#include <BluetoothSerial.h>

BluetoothSerial BT;
int led;

void setup(){
    Serial.begin(115200);
    BT.begin("ESP32Test");
    Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop(){
    if(Serial.available())
        BT.write(Serial.read());

    if(BT.available()){
        char txt = BT.read();
        Serial.write(txt);
        if(txt == 'o' || txt == 'O'){
            digitalWrite(led, HIGH);
        }
        else if(txt == 'x' || txt == 'X'){
            digitalWrite(led, LOW);
        }
    }
}
