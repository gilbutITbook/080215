#define PIR_PIN 7 //동작 감지 신호 처리 핀
#define PIEZO 6 //피에조 스피커 제어 핀 

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_PIN, INPUT); //7번 핀을 입력으로 설정
  pinMode(PIEZO, OUTPUT); //6번 핀을 출력으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(PIR_PIN); //동작 감지 신호를 value 변수에 저장
  if(value == HIGH) //동작을 감지했을 경우
  {
    for(int i=0;i<20;i++) //20회 소리 출력
    {
      tone(PIEZO,523,250); //523Hz 대역의 음을 0.25초 출력 
      delay(200); //음 전환을 위해 0.2초 대기 
      tone(PIEZO,783,250); //783Hz 대역의 음을 0.25초 출력 
      delay(200);
    }
  }  
}
