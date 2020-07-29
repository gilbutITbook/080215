#include <Adafruit_NeoPixel.h> //네오픽셀 LED 라이브러리 추가

#define PIN            6  //6번 핀으로 네오픽셀 LED 제어
#define NUMPIXELS      12 // ①

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //네오픽셀 LED 초기 설정

int delayval = 500; // ②

void setup() {
  
  pixels.begin(); //핀 모드 설정
}

void loop() {
  for(int i=0;i<NUMPIXELS;i++)//네오픽셀의 수만큼 반복 실행
  {  
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // ③
    pixels.show(); //LED에 색깔을 출력
    delay(delayval); //0.5초 대기  
  }
}
