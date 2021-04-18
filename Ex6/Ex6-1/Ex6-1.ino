#include "BluetoothSerial.h" //블루투스 시리얼 헤더 추가

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

BluetoothSerial SerialBT; // 블루투스 시리얼 객체 생성

//led의 상태를 나타내는 변수 생성
bool redState = false;
bool greenState = false;
bool blueState = false;

void setup() {
  Serial.begin(115200); // 시리얼 모니터 보드레이트 설정
  SerialBT.begin("ESP32test"); // 블루투스 이름 설정
  Serial.println("The device started, now you can pair it with bluetooth!"); // 시리얼 모니터에 문자열 출력
  
  //핀모드 설정
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // 모든 led끄기
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void loop() {
  if (Serial.available()) { // 시리얼에 연결되었을때
    SerialBT.write(Serial.read());
  }
  
  if (SerialBT.available()) { // 블루투스가 연결되었을 때
    char txt = SerialBT.read(); // 블루투스 터미널에서 문자를 입력받는다
    Serial.write(txt);
    if(txt == 'o' || txt == 'O'){ // 만약 입력된 문자가 'o'or'O' 라면 모든 led를 켠다 
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      // led 상태를 true로 변경
      redState = true;
      greenState = true;
      blueState = true;
    } 
    else if(txt == 'x' || txt == 'X'){ // 만약 입력된 문자가 'x'or'X' 라면 모든 led를 끈다
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      // led 상태를 false로 변경
      redState = false;
      greenState = false;
      blueState = false;
    }
    else if(txt == 'r' || txt == 'R'){ // 만약 입력된 문자가 'r'or'R'일 때
      if(redState) { // 만약 red led가 켜져있다면 led를 끈다
        digitalWrite(RED_LED, LOW);
        redState = false;
      } else{ // red led가 꺼져있다면 led를 켠다
        digitalWrite(RED_LED, HIGH);
        redState = true;
      }
    }
    else if(txt == 'g' || txt == 'G'){ // 만약 입력된 문자가 'g'or'G'일 때
      if(greenState) { // 만약 green led가 켜져있다면 led를 끈다
        digitalWrite(GREEN_LED, LOW);
        greenState = false;
      } else{ // green led가 꺼져있다면 led를 켠다
        digitalWrite(GREEN_LED, HIGH);
        greenState = true;
      }
    }
    else if(txt == 'b' || txt == 'B'){ // 만약 입력된 문자가 'b'or'B'일 때
      if(blueState) { // 만약 blue led가 켜져있다면 led를 끈다
        digitalWrite(BLUE_LED, LOW);
        blueState = false;
      } else{ // blue led가 꺼져있다면 led를 켠다
        digitalWrite(BLUE_LED, HIGH);
        blueState = true;
      }
    }
  }
  delay(20);
}
