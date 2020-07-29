#define A_OUT A0 //가스 센서의 아날로그 출력을 A0 핀으로 제어 
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT); //A0 핀을 입력으로 설정
  Serial.begin(9600); //시리얼 통신 동기화 
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0); //아날로그 데이터를 읽어 value 변수에 저장
  Serial.print("Gas data :"); //시리얼 모니터로 데이터 출력
  Serial.println(value);
  delay(1000); //1초간 지연
}
