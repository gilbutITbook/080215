//OLED 라이브러리 추가
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1); //4개의 핀을 가진 OLED 모듈은 RESET 핀이 없으므로 -1로 처리

void setup()   {                
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // 0x3C 주소로 OLED 초기화
  display.clearDisplay(); //화면 내용 지우기
  display.setTextColor(WHITE); //텍스트 색깔 설정
  display.setCursor(0,0); //텍스트 출력 위치 설정
  display.println("Hello world!"); //출력 메시지 작성
  display.setTextColor(BLACK, WHITE); // 배경을 흰색, 텍스트를 검은색으로 설정
  display.println(123456789); //숫자 내용 작성
  display.setTextSize(2); //텍스트 크기 설정
  display.setCursor(0,32); // y가 32인 위치를 출력 위치로 설정
  display.setTextColor(WHITE);
  display.println("OLED");
  display.display(); //텍스트 출력
  delay(2000); //2초 동안 내용 출력 유지
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0); //x가 10인 위치를 출력 위치로 설정
  display.println("Hello");
  display.println("Arduino");
  display.display();   
  display.startscrollright(0x00, 0x07); //오른쪽으로 문자열이 이동하면서 출력
  delay(2000);
  display.stopscroll(); //스크롤 정지
  delay(1000);
  display.startscrollleft(0x00, 0x07); //왼쪽으로 문자열이 이동하면서 출력
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07); //왼쪽 아래에서 오른쪽 중간 방향으로 문자열이 이동하면서 출력
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07); //오른쪽 중간에서 왼쪽 위 방향으로 문자열이 이동하면서 출력
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Arduino World");
  display.display();
  display.startscrollright(0x00, 0x00); //왼쪽에서 오른쪽으로 문자열이 계속적으로 지나가는 형태로 출력
}

void loop() {
  
}
