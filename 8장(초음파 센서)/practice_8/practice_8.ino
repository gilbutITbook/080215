#define ECHO 2 //2번 핀을 Echo로 설정
#define TRIG 3 //3번 핀을 Trig로 설정

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);  //Trig핀 출력용으로 설정
  pinMode(ECHO, INPUT);   //Echo핀 입력용으로 설정
  Serial.begin(9600); //시리얼 통신 초기화 
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
  Serial.print("Distance : "); //시리얼 모니터로 거리 데이터 출력
  Serial.print(distance);  
  Serial.println("cm");
  delay(2000); //거리 데이터를 2초간 마다 출력
}
