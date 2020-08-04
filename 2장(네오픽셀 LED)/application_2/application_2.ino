#include <Adafruit_NeoPixel.h> //네오픽셀 LED 라이브러리 추가

#define PIN            6  //6번 핀으로 네오픽셀 LED 제어
#define NUMPIXELS      12 //LED 픽셀 개수 설정

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //네오픽셀 LED 초기 설정

void colorWipe(uint32_t color, uint8_t wait);  //두 개(32비트, 8비트)의 매개변수를 가진 colorWipe 함수 선언
void theaterChase(uint32_t color, uint8_t wait); //두 개(32비트, 8비트)의 매개변수를 가진 theaterChase 함수 선언
uint32_t Wheel(byte WheelPos); //한 개의 8비트 매개변수와 32비트 int형을 반환하는 Wheel 함수 선언
void rainbow(uint8_t wait); //한 개의 8비트 매개변수를 가진 rainbow 함수 선언


void setup() 
{
  pixels.begin(); //핀 모드 설정 
  
}

void loop() 
{    
    colorWipe(pixels.Color(255,0,0),50); //빨간색
    colorWipe(pixels.Color(0,255,0),50); //초록색
    colorWipe(pixels.Color(0,0,255),50); //파란색

    theaterChase(pixels.Color(255, 255, 255),50); //흰색
    theaterChase(pixels.Color(255, 0, 0), 50);  //빨간색
    theaterChase(pixels.Color(0, 0, 255), 50);  //파란색

    rainbow(20);    
}

//하나의 컬러로 픽셀을 순차적으로 채우고 다른 색깔로 전환
void colorWipe(uint32_t color, uint8_t wait) 
{
  for(int i=0; i<pixels.numPixels(); i++) 
  {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}

//3개 간격으로 픽셀에 색깔이 출력
void theaterChase(uint32_t color, uint8_t wait) 
{
  for (int j=0; j<10; j++) //전체 동작 10회 반복
  {  
    for (int q=0; q < 3; q++) //아래 컬러 설정을 3회 반복 
    { 
      for (int i=0; i < pixels.numPixels(); i=i+3) 
      { 
        pixels.setPixelColor(i+q, color);    //3개 간격으로 픽셀 컬러 설정
      }
      pixels.show();
      delay(wait);
    
      for (int i=0; i < pixels.numPixels(); i=i+3) 
      {
        pixels.setPixelColor(i+q, 0);        //3개 간격으로 픽셀 컬러 off
      }
    }
  }
}

//RGB 값을 반환
uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);  //파란색 ~ 빨간색 사이의 RGB 값 반환
  }
  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);  //초록색 ~ 파란색 사이의 RGB 값 반환
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);  //빨간색 ~ 초록색 사이의 RGB 값 반환
}

//전체 픽셀이 무지개 컬러를 순차적으로 출력
void rainbow(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<pixels.numPixels(); i++) 
    {
      pixels.setPixelColor(i, Wheel((i+j) & 255)); //Wheel 함수에서 반환되는 RGB 값으로 컬러 설정
    }
    pixels.show();
    delay(wait);
  }
}
