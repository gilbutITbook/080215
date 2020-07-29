#define RED 9 //9번 핀으로 빨간색 LED 제어 
#define GREEN 8 //8번 핀으로 녹색 LED 제어 
#define TOUCH_STATE 7 //7번 핀으로 터치 이벤트 처리 

int count = 0; //터치 횟수를 저장하는 변수

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT); //9번 핀을 출력용으로 설정
  pinMode(GREEN, OUTPUT); //8번 핀을 출력용으로 설정
  pinMode(TOUCH_STATE, INPUT); //7번 핀을 입력용으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  int touchValue = digitalRead(TOUCH_STATE); //터치 이벤트 신호를 읽어 touch_value 변수에 저장

  if(touchValue == HIGH) //터치 이벤트가 발생했을 경우
  {
    count++; //count 변수 1 증가
  }
  
  if(count%2==1) //터치 횟수가 홀수(비상 상태) 
  {
    digitalWrite(GREEN, LOW); //초록색 LED 소등
    delay(200); //자연스럽게 LED가 소등되고 점등되도록 지연 시간 부여 
    digitalWrite(RED, HIGH); //빨간색 LED 점등
    delay(200); //점등, 소등 효과를 내기 위해 0.2초 지연
    digitalWrite(RED, LOW); //빨간색 LED 소등
    delay(200);
  }
  else //터치 횟수가 짝수(안정 상태)
  {
    digitalWrite(RED, LOW);  
    delay(200);
    digitalWrite(GREEN, HIGH);
  }      
}
