#include <Adafruit_NeoPixel.h> //네오픽셀 LED 라이브러리 추가

#define TOUCH 7 //터치 이벤트를 7번 핀으로 확인
#define LED_CONTROL 9 //9번 핀으로 네오픽셀 LED 제어 
#define NUMPIXELS 12 //12픽셀 사용
unsigned long startTime; //프로그램이 실행된 후 터치 이벤트가 발생하기까지의 시간을 저장
unsigned long touchTime; //터치 이벤트가 지속적으로 발생하는 시간을 저장
int count = 0; //count 변수 0으로 초기화

//네오픽셀 LED 초기 설정
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_CONTROL, NEO_GRB + NEO_KHZ800); 

void ledOn(byte repeat); //ledOn 함수 선언
void ledOff(); //ledOff 함수 선언

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_CONTROL, OUTPUT); //9번 핀을 출력용으로 설정
  pinMode(TOUCH, INPUT); //7번 핀을 입력용으로 설정
  pixels.begin(); //핀 모드 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(TOUCH) == HIGH) //손가락으로 터치센서를 눌렀을 때 
  {
    count++; //터치 횟수 1 증가
    startTime = millis(); //터치 센서를 계속 누르기 전의 시간 저장   
    
    while(digitalRead(TOUCH) == HIGH); //손가락을 계속 누르고 있는 시간을 측정하기 위한 루프
    touchTime = millis() - startTime; //터치 센서를 계속 누른 시간을 저장
    if(touchTime >= 2000) //손가락을 2초 이상 누르고 있을 때 
    {
      ledOff(); //LED 소등
      count = 0; //count 값 0으로 초기화 
    }
  } 
 
  switch(count) //1~3단계에서는 광량이 순차적으로 증가하고 4단계에서는 LED 소등
  {
    case 1:
    case 2:      
    case 3:
      ledOn(count); //count를 매개 변수로 하여 lenOn() 함수 호출
      delay(200); //0.2초 대기 
      break;
    case 4:  
      ledOff(); //ledOff() 함수 호출
      delay(200);
      count = 0;
      break;    
  }  
}

void ledOn(byte repeat) //네오픽셀 LED 점등 기능을 구현한 ledOn() 함수 정의
{ 
  for (int q=0; q < repeat; q++) //repeat 값만큼 반복
  { 
    for (int i=0; i < pixels.numPixels(); i=i+3) //3 간격으로 반복
    { 
      pixels.setPixelColor(i+q, pixels.Color(255,255,255)); //3개 간격으로 픽셀 컬러 설정
    }
  }
  pixels.show(); //설정된 컬러 출력
}

void ledOff() //네오픽셀 LED 소등 기능을 구현한 ledOff() 함수 정의
{
  for (int i=0; i < pixels.numPixels(); i++) //픽셀의 수 만큼 반복
  {
    pixels.setPixelColor(i, pixels.Color(0,0,0)); //전 픽셀 컬러 off    
  }    
  pixels.show();
}
