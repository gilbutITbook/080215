#include <Servo.h> //서보 모터 라이브러리 추가 

#define TOUCH 7 //7번 핀으로 터치 이벤트 처리 
#define DC_MOTOR 5 //5번 핀으로 DC 모터 제어 

Servo myservo;  // 서보 모터 제어를 위한 객체 생성

int motorStep = 0; //DC 모터의 단계를 저장하는 변수
int rotateState = 0;  //1~3초 사이 터치 이벤트 횟수 저장
int pos = 0;    // 서보 모터 위치 값을 저장하는 변수 선언
unsigned long startTime; //프로그램이 실행된 후 터치 이벤트가 발생하기 전까지의 시간을 저장
unsigned long touchTime; //터치 이벤트가 지속적으로 발생한 시간을 저장

void motor_Control(int dcStep); //DC 모터 출력과 관련된 함수 선언

void setup() {
  myservo.attach(6);  // 서보 모터 제어를 위한 핀 설정
  pinMode(TOUCH, INPUT); //7번 핀을 INPUT 용으로 설정  
  Serial.begin(9600); //시리얼 통신 동기화  
}

void loop() {
  int touchValue = digitalRead(TOUCH); //터치 이벤트 값을 touchValue에 저장
  delay(200); //터치 이벤트 사이 0.2초 지연 시간 부여

  if(touchValue == HIGH) //터치 이벤트가 발생했을 때
  {
    motorStep++; //motorStep 변수 1 증가
    Serial.print("touch count:");
    Serial.print(motorStep); //시리얼 모니터로 현재 DC 모터 단계 확인
    motor_Control(motorStep); //motor_Control() 함수 호출
    startTime = millis(); //터치 이벤트가 지속적으로 발행하기 전까지의 시간을 startTime 변수에 저장
    while(digitalRead(TOUCH) == HIGH); //손가락을 계속 누르고 있는 시간을 측정하기 위한 루프
    touchTime = millis() - startTime; //터치 이벤트가 지속적으로 발생한 시간을 touchTime에 저장
    Serial.print("\tcontinuous time : ");
    Serial.println(touchTime); //시리얼 모니터로 이벤트 시간 확인
    if(touchTime >= 1000 && touchTime <= 3000) //지속적으로 터치 이벤트가 발생한 시간이 1~3초 사이일 때 회전
    {
      rotateState++; //1~3초 사이 터치 이벤트 횟수 1증가
    }    
  }
  
  if((rotateState%2 == 1) && (motorStep != 0)) //rotateState 변수가 홀수이고 motorStep이 0이 아닐 때 실행
  {
    for (pos = 0; pos <= 120; pos += 1) { // 0 ~ 120까지 1씩 증가시켜 루프를 돌림 
    motor_Control(motorStep);  
    myservo.write(pos);              // pos 변수 값의 위치로 회전(1도 씩 회전)
    delay(15);                       // 서보 모터가 위치까지 도달할 수 있도록 15ms 대기
    }
    for (pos = 120; pos >= 0; pos -= 1) { // 120 ~ 0까지 1씩 감소시켜 루프를 돌림
    motor_Control(motorStep);  
    myservo.write(pos);              
    delay(15);                       
    }           
  } 
}
void motor_Control(int dcStep) //DC 모터 출력과 관련된 함수 정의
{
  switch(dcStep)
  {
    case 1: //1회 터치 시 
      analogWrite(DC_MOTOR, 85); //최대 속도의 1/3 속도 출력
      break;
    case 2: //2회 터치 시 
      analogWrite(DC_MOTOR, 170); //최대 속도의 2/3 속도 출력
      break;
    case 3: //3회 터치 시 
      analogWrite(DC_MOTOR, 255); //최대 속도 출력
      break;
    case 4:
      analogWrite(DC_MOTOR, 0); //모터 멈춤
      motorStep = 0; //motorStep 변수 0으로 초기화 
      break;      
  }
}
