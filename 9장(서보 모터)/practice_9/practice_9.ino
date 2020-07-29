#include <Servo.h> //서보 모터 라이브러리 추가

Servo myservo;  // 서보 모터 제어를 위한 객체 생성

int pos = 0;    // 서보 모터 위치 값을 저장하는 변수 선언

void setup() {
  myservo.attach(6);  // 서보 모터 제어를 위한 핀 설정
}

void loop() {
  for (pos = 0; pos <= 120; pos += 1) { // 0 ~ 120까지 1씩 증가시켜 루프를 돌림 
    myservo.write(pos);              // pos 변수 값의 위치로 회전(1도 씩 회전)
    delay(15);                       // 서보 모터가 위치까지 도달할 수 있도록 15ms 대기
  }
  for (pos = 120; pos >= 0; pos -= 1) { // 120 ~ 0까지 1씩 감소시켜 루프를 돌림
    myservo.write(pos);              
    delay(15);                       
  }
  
}
