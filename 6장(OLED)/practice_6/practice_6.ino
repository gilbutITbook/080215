//OLED 라이브러리 추가 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1); //4개의 핀을 가진 OLED 모듈은 RESET 핀이 없으므로 -1로 처리

void setup()   {                
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // 0x3C 주소로 OLED 초기화
  display.clearDisplay(); //화면 내용 지우기
  display.setTextColor(WHITE); //텍스트 색깔 설정
  display.println("Hello Arduino"); //문자열 내용 작성  
  display.display(); //텍스트 출력  
}

void loop() {
  
}
