
#include <Adafruit_NeoPixel.h> //네오픽셀 LED 라이브러리 추가

#define PIN            6  //6번 핀으로 네오픽셀 LED 제어 
#define NUMPIXELS      12 //12개 픽셀 사용

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //네오픽셀 LED 초기 설정

void ledOn(byte repeat); //ledOn 함수 선언
void ledOff(); //ledOff 함수 선언

int count = 1; //count 변수를 1로 초기화 

void setup() 
{
  pixels.begin(); //핀 모드 설정
}

void loop() 
{
    switch(count) //count 변수가 1~3일 때 LED 불이 켜지고 4일 때 LED 불이 꺼짐
    {
      case 1:
      case 2:
      case 3: 
        ledOn(count); //count를 매개 변수로 하여 ledOn() 함수 호출
        delay(2000); //LED 불빛의 변화를 확인하기 위해 2초간 대기
        count++; //count 변수 1증가 
        break;
      case 4:
        ledOff(); //count 변수가 4일 때 호출
        delay(2000);
        count=1; //count 변수를 1로 초기화 
        break;      
    }    
}
//count 값을 매개변수로 받아 LED 제어
void ledOn(byte repeat) //네오픽셀 LED 점등 기능을 구현한 ledOn() 함수 정의
{ 
  for (int q=0; q < repeat; q++) //repeat 값만큼 반복
  { 
    for (int i=0; i < pixels.numPixels(); i=i+3) //3 간격으로 반복
    { 
      pixels.setPixelColor(i+q, pixels.Color(255,255,255)); //3개 간격으로 픽셀 컬러 설정
    }
  }
  pixels.show(); //픽셀에 설정된 색깔 출력
}

void ledOff() //네오픽셀 LED 소등 기능을 구현한 ledOff() 함수 정의
{
  for (int i=0; i < pixels.numPixels(); i++) //픽셀의 수 만큼 반복
  {
    pixels.setPixelColor(i, pixels.Color(0,0,0)); //전 픽셀 컬러 off    
  }    
  pixels.show();
}
    
     
