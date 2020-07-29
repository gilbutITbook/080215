#include <SoftwareSerial.h> //소프트웨어 시리얼 라이브러리 추가 
#include <DHT.h> //온습도 센서 라이브러리 추가 

#define TXD 2 //TXD를 2번 핀으로 설정
#define RXD 3 //RXD를 3번 핀으로 설정
#define INPUT_PULSE 4 //4번 핀으로 입력 펄스 인가
#define MOTOR 6 //6번 핀으로 DC 모터 제어 
#define DHTPIN 7  //온습도 센서 out 7번 핀으로 설정
#define LED 8 //LED 제어 8번 핀으로 설정
#define DHTTYPE DHT11   // 온습도 센서 타입 선택
#define OUTPUT_VOLTAGE A0 //A0 핀으로 출력 전압 입력

SoftwareSerial mySerial(TXD, RXD); //소프트웨어 시리얼 mySerial 객체 선언
DHT dht(DHTPIN, DHTTYPE); //DHT 센서 초기화

float preVoltage = 0; //0~1023 범위의 출력 전압
float voltage = 0; //0~5 범위의 출력 전압
float dustDensity = 0; //미세먼지 농도 수치 
float sumDustDensity = 0; //미세먼지 농도 수치 합
float avgDustDensity = 0; //미세먼지 농도 수치 평균

void setup() {
  mySerial.begin(9600); //소프트웨어 시리얼 동기화
  dht.begin(); //온습도 센서 핀 설정
  pinMode(INPUT_PULSE, OUTPUT); //4번 핀 출력으로 설정
  pinMode(OUTPUT_VOLTAGE, INPUT); //A0 핀 입력으로 설정
  pinMode(MOTOR, OUTPUT); //6번 핀 출력으로 설정
  pinMode(LED, OUTPUT); //8번 핀 출력으로 설정
}

void loop() { 

  delay(2000); //측정 간 2초 대기

  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
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
  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 loop() 함수 종료
    return;
  }
  
  if(mySerial.available()) //앱에서 데이터가 발생되어 블루투스 모듈로 데이터가 입력되었을 때 
  {
    char input = (char)mySerial.read();//데이터를 읽어 char형으로 형 변환 후 input 변수에 저장   
          
    switch(input) //input 변수의 값에 맞는 case 문 실행 
    {
      case '1':
        digitalWrite(LED, HIGH); //LED 점등
        break;
      case '2':
        digitalWrite(LED, LOW); //LED 소등
        break;
      case '3':
        analogWrite(MOTOR, 64); //1/4 속도로 DC 모터 출력
        break;
      case '4':
        analogWrite(MOTOR, 128); //2/4 속도로 DC 모터 출력
        break;
      case '5':
        analogWrite(MOTOR, 192); //3/4 속도로 DC 모터 출력
        break;
       case '6':
        analogWrite(MOTOR, 0); //DC 모터 정지 
        break;        
    }       
  }
  mySerial.print(humidity,1); //소수점 첫째자리까지 습도 데이터 출력
  mySerial.print("%\t"); //습도 단위 출력 후 탭 만큼 커서 이동
  mySerial.print(temperature,1); //소수점 첫째자리까지 온도 데이터 출력  
  mySerial.print("C\t"); //온도 단위 출력 후 탭 만큼 커서 이동
  mySerial.print(avgDustDensity,1); //소수점 첫째자리까지 미세먼지 데이터 출력  
  mySerial.println("ug/m3"); //미세먼지 단위 출력
}
