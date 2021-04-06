#include <DHT.h> // 온습도 센서 라이브러리
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C 라이브러리
#define COL 16 // lcd행
#define ROW 2 // lcd열

DHT dht(16, DHT11); // 온습도 객체 생성
LiquidCrystal_I2C lcd(0x27, COL, ROW); // lcd객체 생성
void setup(){
  lcd.init(); // lcd 초기화
  lcd.backlight(); // lcd backlight 켜기
  Serial.begin(115200); // 시리얼모니터 보드레이트 설정
}

void loop(){
  double temp = dht.readTemperature(); // 온습도센서에서 온도를 가져와 변수에 저장
  double hum = dht.readHumidity(); // 온습도센서에서 습도를 가져와 변수에 저장
  
  // 시리얼 모니터 출력
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println('C');
  Serial.print("Humidity: ");
  Serial.println(hum);


  // lcd출력
  lcd.setCursor(0, 0); // 문자열을 출력할 위치를 설정
  lcd.print("   Tempe:");
  lcd.print(temp);
  lcd.print("*c");
  lcd.setCursor(0,1); // 문자열을 출력할 위치를 설정
  lcd.print("Humidity:");
  lcd.print(hum);
  lcd.print("%");
    
  delay(200); // 200ms 대기
  lcd.clear();  // lcd 지우기
}
