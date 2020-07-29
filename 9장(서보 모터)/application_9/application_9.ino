#include <Servo.h> //Servo 헤더 파일 추가

#define TOUCH 7 //7번 핀으로 터치 이벤트 제어

Servo myservo;  // 서보 모터 제어를 위한 객체 생성

int rotateState = 0;  //1~3초 사이 터치 이벤트 횟수 저장
int pos = 0;    // 서보 모터 위치 값을 저장하는 변수 선언
unsigned long startTime; //프로그램이 실행된 후 터치 이벤트가 발생하기 전까지의 시간을 저장
unsigned long touchTime; //터치 이벤트가 지속적으로 발생한 시간을 저장

void setup() {
  myservo.attach(6);  // 서보 모터 제어를 위한 핀 설정
  pinMode(TOUCH, INPUT); //7번 핀을 INPUT 용으로 설정  
  Serial.begin(9600); //시리얼 통신 동기화
}

void loop() {
  int touchValue = digitalRead(TOUCH); //터치 이벤트 값을 touchValue에 저장

  if(touchValue == HIGH) //터치 이벤트가 발생했을 때
  {
    startTime = millis(); //터치 이벤트가 지속적으로 발행하기 전까지의 시간을 startTime 변수에 저장
    while(digitalRead(TOUCH) == HIGH); //손가락을 계속 누르고 있는 시간을 측정하기 위한 루프
    touchTime = millis() - startTime; //터치 이벤트가 지속적으로 발생한 시간을 touchTime에 저장
    
    if(touchTime >= 1000 && touchTime <= 3000) //지속적으로 터치 이벤트가 발생한 시간이 1~3초 사이 일 때
    {
      rotateState++; //rotateState 변수 1증가
    }
    Serial.print("rotateState : ");
    Serial.print(rotateState); //시리얼 모니터로 rotateState 값 확인
    Serial.print("\tcontinuous time : ");
    Serial.println(touchTime); //시리얼 모니터로 터치 이벤트 시간 확인
  }
  
  if(rotateState%2 == 1) //rotateState 변수가 홀수 일 때 서보 모터 회전
  {
    for (pos = 0; pos <= 120; pos += 1) { // 0 ~ 120까지 1씩 증가시켜 루프를 돌림 
    myservo.write(pos);              // pos 변수 값의 위치로 회전(1도 씩 회전)
    delay(15);                       // 서보 모터가 위치까지 도달할 수 있도록 15ms 대기
    }
    for (pos = 120; pos >= 0; pos -= 1) { // 120 ~ 0까지 1씩 감소시켜 루프를 돌림
    myservo.write(pos);              
    delay(15);                       
    }    
  }  
}
