#define RED_PIN 11 //11번 핀으로 RED 핀 제어 
#define GREEN_PIN 10 //10번 핀으로 GREEN 핀 제어
#define BLUE_PIN 9 //9번 핀으로 BLUE 핀 제어
#define TOUCH_STATE 7 //터치 이벤트를 7번 핀으로 확인

void colorPrint(int redValue, int greenValue, int blueValue); //색깔 출력 함수 선언

int count = 0; //터치 이벤트 횟수 저장

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT); //11번 핀을 출력으로 설정
  pinMode(GREEN_PIN, OUTPUT); //10번 핀을 출력으로 설정
  pinMode(BLUE_PIN, OUTPUT); //9번 핀을 출력으로 설정
  pinMode(TOUCH_STATE, INPUT); //7번 핀을 입력으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  int touchValue = digitalRead(TOUCH_STATE); //터치 이벤트 신호를 읽어 touchValue 변수에 저장 

  if(touchValue == HIGH) //손가락으로 터치센서를 눌렀을 때 
  {
    count++; //count 변수 1 증가
    delay(300); //색깔이 전환되기 전 지연 시간 부여 
    switch(count) //count 값에 따라 해당 case 문 실행
    {
      case 1:
        colorPrint(255,255,255); //흰색 출력
        break;
      case 2:
        colorPrint(255,0,0); //빨간색 출력
        break;
      case 3:
        colorPrint(0,255,0); //녹색 출력
        break;
      case 4:
        colorPrint(0,216,255); //하늘색 출력
        break;
      case 5:
        colorPrint(95,0,255); //보라색 출력        
        break;      
      default : 
        colorPrint(0,0,0); //LED off
        count = 0; //count 변수 0으로 초기화
    } 
  }  
}
void colorPrint(int redValue, int greenValue, int blueValue) // 색깔을 출력하는 함수 정의
{
  analogWrite(RED_PIN, redValue); 
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);    
}
