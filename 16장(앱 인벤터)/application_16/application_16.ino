#include <SoftwareSerial.h> //소프트웨어 시리얼 라이브러리 추가 

#define TXD 2 //TXD를 2번 핀으로 설정
#define RXD 3 //RXD를 3번 핀으로 설정
#define LED 13 //13번 핀으로 LED 제어 

SoftwareSerial mySerial(TXD, RXD); //소프트웨어 시리얼 mySerial 객체 선언

void ledControl(int pin,int count); //매개 변수로 제어 핀과 count 횟수를 가진 ledControl() 함수 선언

int ledCount = 0; //LED 제어 이벤트 발생 횟수를 count하는 변수 0으로 초기화 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); //소프트웨어 시리얼 동기화
  pinMode(LED, OUTPUT); //13번 핀 출력으로 설정
}

void loop() { 

  if(mySerial.available()) //앱에서 데이터가 발생되어 블루투스 모듈로 데이터가 입력되었을 때 
  {
    byte input = mySerial.read();//byte형의 데이터를 input 변수에 저장   

    switch(input) //input 변수의 값에 맞는 case 문 실행 
    {
      case 1:
        ledCount++; //1이 발생될 때마다 ledCount 변수 1증가
        ledControl(LED,ledCount); //LED 제어 핀과 ledCount 값을 매개변수로 하여 ledControl()함수 호출
        break;
    }       
  }  
}

void ledControl(int pin,int count) //매개 변수로 제어 핀과 count 횟수를 가진 ledControl() 함수 정의
{
  if(count%2==1) //count 값이 홀수일 때 
  {
    digitalWrite(pin, HIGH); //LED를 제어하는 핀에 HIGH 신호를 발생시켜 LED 점등
  }
  else //count 값이 짝수일 때
  {
    digitalWrite(pin, LOW); //LED를 제어하는 핀에 LOW 신호를 발생시켜 LED 소등
  }
}
