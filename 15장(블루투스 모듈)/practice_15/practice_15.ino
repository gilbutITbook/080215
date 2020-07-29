#include <SoftwareSerial.h> //소프트웨어시리얼 라이브러리 추가

#define TXD 2 //TXD를 2번 핀으로 설정
#define RXD 3 //RXD를 3번 핀으로 설정

SoftwareSerial mySerial(TXD, RXD); //소프트웨어 시리얼 mySerial 객체 선언

void setup() {
  Serial.begin(9600); //시리얼 통신 동기화   
  mySerial.begin(9600); //소프트웨어 시리얼 동기화
}

void loop() { 
  if (mySerial.available()) { //앱에서 데이터가 발생되어 블루투스 모듈로 데이터가 입력되었을 때 
    Serial.write(mySerial.read()); //블루투스 모듈로 입력된 데이터를 읽어 시리얼 모니터 창에 출력
  }
  if (Serial.available()) { //시리얼 모니터에서 데이터가 발생되었을 때
    mySerial.write(Serial.read()); //입력된 데이터를 읽어 블루투스 모듈을 통해 앱으로 데이터 전송 
  }
}
