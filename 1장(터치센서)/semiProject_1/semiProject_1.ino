#define TOUCH 7 //7번 핀으로 터치 이벤트 처리 
#define LED 9 //9번 핀으로 LED 제어 

unsigned long startTime; //프로그램이 실행된 후 터치 이벤트가 발생하기까지의 시간을 저장
unsigned long touchTime; //터치 이벤트가 지속적으로 발생하는 시간을 저장
int count = 0; //터치 횟수를 저장하는 count 변수 초기화 

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //9번 핀을 출력용으로 설정
  pinMode(TOUCH, INPUT); //7번 핀을 입력용으로 설정  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(TOUCH) == HIGH) //손가락으로 터치센서를 눌렀을 때 
  {
    count++; //터치 횟수 1 증가
    startTime = millis(); //터치 센서를 계속 누르기 전의 시간 저장    
    while(digitalRead(TOUCH) == HIGH); //손가락을 계속 누르고 있는 시간을 측정하기 위한 루프
    touchTime = millis() - startTime; //터치 센서를 계속 누른 시간을 저장
    if(touchTime >= 2000) //손가락을 2초 이상 누르고 있을 때 
    {
      analogWrite(LED, 0); //LED 소등
      count = 0; //count 값 0으로 초기화 
    }
  } 
  
  switch(count) //1~3단계에서는 광량이 순차적으로 증가하고 4단계에서는 LED 소등
  {
    case 1:
      analogWrite(LED, 85); //1/3 광량으로 LED 점등
      break;
    case 2:      
      analogWrite(LED, 170); //2/3 광량으로 LED 점등  
      break;
    case 3:
      analogWrite(LED, 255); //최대 광량으로 LED 점등
      break;    
    case 4:  
      analogWrite(LED, 0); //LED 소등
      count = 0;
      break;    
  }  
}
