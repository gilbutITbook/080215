#define PIEZO 6 //6번 핀으로 피에조 스피커 제어 
#define MAGNETIC 7 //7번 핀으로 마그네틱 스위치 신호 처리 
#define PIR 8 //8번 핀으로 인체 감지 센서 신호 처리 

void setup() {
  // put your setup code here, to run once:
  pinMode(PIEZO, OUTPUT); //6번 핀을 출력용으로 설정
  pinMode(MAGNETIC, INPUT_PULLUP); //7번 핀을 INPUT_PULLUP으로 설정
  pinMode(PIR, INPUT); //8번 핀은 입력으로 설정  
  Serial.begin(9600); //시리얼 통신 초기화 
}

void loop() {
  // put your main code here, to run repeatedly:
  int magneticValue = digitalRead(MAGNETIC); //마그네틱 스위치의 출력 신호를 magneticValue 변수에 저장
  int pirValue = digitalRead(PIR); //인체 감지 센서의 출력 신호를 pirValue 변수에 저장
  Serial.print("magnetic State :"); //마그네틱 스위치 상태 출력
  Serial.println(magneticValue);
  Serial.print("pir State :"); //인체 감지 센서 상태 출력
  Serial.println(pirValue);
  if(magneticValue == 1 && pirValue == 0) //현관문이 열려있고 동작이 감지되지 않았을 때 
  {
     for(int i=0;i<2;i++) //알림음을 2회 출력
    {
      tone(PIEZO, 6271, 150); //6271Hz 주파수의 음을 0.15초 출력
      delay(200); //0.2초 대기 
      tone(PIEZO, 4186, 150); //4186Hz 주파수의 음을 0.15초 출력
      delay(200);
    }
  }
  delay(1000); //1초간 대기   
}
