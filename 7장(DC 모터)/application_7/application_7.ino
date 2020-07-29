#define MOTOR 6 //6번 핀으로 DC 모터 제어 
#define TOUCH 2 //2번 핀으로 터치 이벤트 처리 

int count = 0; //터치 이벤트 횟수 저장

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR, OUTPUT); //6번 핀 출력 용으로 설정
  pinMode(TOUCH, INPUT);  //2번 핀 입력 용으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(TOUCH); //터치 이벤트 값을 value에 저장
  delay(200); //터치 이벤트 사이 0.2초 대기 
  
  if(value == HIGH) //터치센서를 눌렀을 때 
  {
    count++; //count 변수 1 증가
    switch(count)
    {
      case 1: //1회 터치 시 
        analogWrite(MOTOR, 85); //최대 속도의 1/3 속도 출력
        break;
      case 2: //2회 터치 시 
        analogWrite(MOTOR, 170); //최대 속도의 2/3 속도 출력
        break;
      case 3: //3회 터치 시 
        analogWrite(MOTOR, 255); //최대 속도 출력
        break;
      case 4:
        analogWrite(MOTOR, 0); //모터 멈춤
        count = 0; //count 변수 0으로 초기화 
        break;      
    }
  }  
}
