void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT); //6번 핀 출력 용으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(6, HIGH); //HIGH 신호 인가
  delay(3000); //3초 간 모터 동작
  digitalWrite(6, LOW); //LOW 신호 인가 
  delay(1000); //1초 간 모터 멈춤   
}
