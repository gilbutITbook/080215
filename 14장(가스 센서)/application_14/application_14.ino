#define A_OUT A0 //가스 센서의 아날로그 출력을 A0 핀으로 제어
#define PIEZO 6 //피에조 스피커 제어를 6번 핀으로 설정
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT); //A0 핀을 입력으로 설정
  pinMode(PIEZO, OUTPUT); //6번 핀을 출력으로 설정
  Serial.begin(9600); //시리얼 통신 동기화 
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0); //아날로그 데이터를 읽어 value 변수에 저장
  if(value >= 250) //가스가 누출될 때 
  {
    for(int i=0;i<5;i++) //경고음을 5회 출력
    {
      tone(PIEZO, 2093, 250); //2093Hz 주파수의 음을 0.25초 출력
      delay(200); //0.2초 대기 
      tone(PIEZO, 1567, 250); //1567Hz 주파수의 음을 0.25초 출력
      delay(200);      
    }    
  }
  Serial.print("Gas data :"); //시리얼 모니터로 데이터 출력
  Serial.println(value);  
  delay(1000); //1초 간 대기
}
