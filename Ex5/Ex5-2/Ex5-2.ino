// Hello world 출력하기

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // LiquidCrystal_I2C 객체 생성

void setup(){
  lcd.init(); // lcd초기화
  lcd.backlight(); // backlight 켜기
}

void loop(){
  lcd.setCursor(0, 0); // 문자열을 출력할 위치를 (0, 0)으로 설정
  lcd.print("Hello, World!"); // 문자열 출력
  delay(1000); // 1초 대기
  lcd.clear(); // lcd지우기
  lcd.setCursor(0,1); // 문자열을 출력할 위치를 (1, 0)으로 설정
  lcd.print("Hello, World!"); // 문자열 출력
  delay(1000); // 1초 대기
  lcd.clear(); // lcd지우기
}