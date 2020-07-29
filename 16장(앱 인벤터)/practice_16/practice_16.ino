#include <SoftwareSerial.h>//소프트웨어 시리얼 라이브러리 추가

#define TXD 2 //TXD를 2번 핀으로 설정
#define RXD 3 //RXD를 3번 핀으로 설정

SoftwareSerial mySerial(TXD, RXD); //소프트웨어 시리얼 mySerial 객체 선언

void setup() {
  mySerial.begin(9600); //소프트웨어 시리얼 동기화
}

void loop() { 
  
}
