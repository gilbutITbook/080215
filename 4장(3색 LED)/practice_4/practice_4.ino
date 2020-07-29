#define RED_PIN 11 //11번 핀으로 RED 핀 제어 
#define GREEN_PIN 10 //10번 핀으로 GREEN 핀 제어 
#define BLUE_PIN 9 //9번 핀으로 BLUE 핀 제어 

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT); //11번 핀을 출력으로 설정
  pinMode(GREEN_PIN, OUTPUT); //10번 핀을 출력으로 설정
  pinMode(BLUE_PIN, OUTPUT); //9번 핀을 출력으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  //빨간색 출력
  analogWrite(RED_PIN, 255); 
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0); 
  delay(1000);
  //초록색 출력
  analogWrite(RED_PIN, 0); 
  analogWrite(GREEN_PIN, 255);
  analogWrite(BLUE_PIN, 0); 
  delay(1000);
  
}
