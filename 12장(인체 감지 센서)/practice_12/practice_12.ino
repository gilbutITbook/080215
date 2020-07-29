#define PIR_PIN 7 //동작 감지 신호 처리 핀

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_PIN, INPUT); //7번 핀을 입력으로 설정
  Serial.begin(9600); //시리얼 통신 초기화
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(PIR_PIN); //동작 감지 신호를 value 변수에 저장
  if(value == HIGH) //동작을 감지했을 경우
  {
    Serial.println("Detected"); //시리얼 모니터에 Detected 메시지 출력
  }
  else //동작을 감지하지 못했을 경우
  {
    Serial.println("Not detected"); //시리얼 모니터에 Not detected 메시지 출력
  }
  delay(1000); //1초간 지연
}
