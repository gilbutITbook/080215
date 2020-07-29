#define INPUT_PULSE 2 //2번 핀으로 입력 펄스 인가
#define OUTPUT_VOLTAGE A0 //A0 핀으로 출력 전압 입력 

float preVoltage = 0; //0~1023 범위의 출력 전압
float voltage = 0; //0~5 범위의 출력 전압
float dustDensity = 0; //미세먼지 농도 수치 
float sumDustDensity = 0; //미세먼지 농도 수치 합
float avgDustDensity = 0; //미세먼지 농도 수치 평균

void setup()   {                
  pinMode(INPUT_PULSE, OUTPUT); //2번 핀 출력으로 설정
  pinMode(OUTPUT_VOLTAGE, INPUT); //A0 핀 입력으로 설정
  Serial.begin(9600); //시리얼 통신 동기화 
} 

void loop() {
  sumDustDensity = 0; //미세먼지 농도 수치 합을 초기화 
  for(int i=0;i<30;i++) //미세먼지 농도 수치 30회 측정
  {
    digitalWrite(INPUT_PULSE, LOW); //입력 펄스 인가
    delayMicroseconds(280); //0.28ms 대기
    preVoltage = analogRead(OUTPUT_VOLTAGE); //A0 핀으로부터 데이터를 읽어 preVoltage에 저장
    delayMicroseconds(40); //0.04ms 대기
    digitalWrite(INPUT_PULSE, HIGH); //입력 펄스 종료  
    delayMicroseconds(9680); //9.68ms 대기
    voltage = preVoltage * 5.0 / 1024.0; //0~5 범위 전압 값으로 변환 후 voltage에 저장
    dustDensity = (voltage-0.3)/0.005; //미세먼지 농도 수치 dustDensity에 저장
    sumDustDensity += dustDensity; //미세먼지 농도 수치 합계
    delay(10); //데이터 계산 간 10ms 대기
  }
  avgDustDensity = sumDustDensity / 30.0; //미세먼지 농도 수치의 평균 값을 avgDustDensity에 저장
  Serial.print("dustDensity : "); //미세먼지 농도 수치 출력
  Serial.println(avgDustDensity);
  delay(1000);  //1초 대기
}

