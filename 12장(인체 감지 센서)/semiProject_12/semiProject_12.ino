#define PIR_PIN 7 //7번 핀으로 동작 감지 신호 처리
#define LED_PIN 6 //6번 핀으로 LED 제어 

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_PIN, INPUT); //7번 핀을 입력으로 설정
  pinMode(LED_PIN, OUTPUT); //6번 핀을 출력으로 설정  
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(PIR_PIN); //동작 감지 신호를 value 변수에 저장
  if(value == HIGH) //동작을 감지했을 경우
  {    
    digitalWrite(LED_PIN, HIGH); //LED 점등
    delay(9000); //9초 동안 지연
  }  
  else
  {
    digitalWrite(LED_PIN, LOW); //LED 소등       
  }
}
