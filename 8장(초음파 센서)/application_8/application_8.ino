#define ECHO 2 //2번 핀을 Echo로 설정
#define TRIG 3 //3번 핀을 Trig로 설정
#define RED 11 //11번 핀을 RED 핀으로 설정
#define GREEN 10 //10번 핀을 GREEN 핀으로 설정 
#define BLUE 9 //9번 핀을 BLUE 핀으로 설정

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT); //Trig 핀 출력용으로 설정
  pinMode(ECHO, INPUT);  //Echo 핀 입력용으로 설정
  pinMode(RED, OUTPUT); //RED 핀 출력용으로 설정
  pinMode(GREEN, OUTPUT); //GREEN 핀 출력용으로 설정
  pinMode(BLUE, OUTPUT); //BLUE 핀 출력용으로 설정  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG, HIGH); //펄스파 발생
  delayMicroseconds(10); //10마이크로초 지연
  digitalWrite(TRIG, LOW);  //펄스파 종료

  long duration = pulseIn(ECHO, HIGH); //Echo핀이 HIGH가 된 이후 지연된 펄스의 시간을 duration 변수에 저장

  if(duration == 0) //시간이 0이면 종료 
  {
    return;
  }

  long distance = duration / 58; //총 걸리는 시간을 58로 나눠 거리를 측정
  if(distance <= 15) //주차 공간에 자동차가 있을 때(빨간색 점등)
  {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
  }
  else //주차 공간에 자동차가 없을 때(녹색 점등)
  {
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
  }
  delay(2000); //2초 간격으로 거리 데이터 계산
}
