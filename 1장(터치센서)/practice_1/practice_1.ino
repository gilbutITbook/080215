#define TOUCH_STATE 7 //터치 이벤트를 7번 핀으로 확인

void setup() {
  // put your setup code here, to run once:
  pinMode(TOUCH_STATE, INPUT); //7번 핀을 입력용으로 설정
  Serial.begin(9600); //시리얼 통신을 위한 초기화 
}

void loop() {
  // put your main code here, to run repeatedly:
  int touchValue = digitalRead(TOUCH_STATE); //터치 이벤트 신호를 읽어 touchValue 변수에 저장
  
  if(touchValue == HIGH) //손가락으로 터치 센서를 눌렀을 때 
  {
    Serial.println("Touched"); //시리얼 모니터에 Touched 출력
    delay(200); //0.2초 지연  
  }  
}
