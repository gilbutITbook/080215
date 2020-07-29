#include <SoftwareSerial.h> //소프트웨어 시리얼 라이브러리 추가 
#include <DHT.h> //온습도 센서 라이브러리 추가

#define TXD 2 //TXD를 2번 핀으로 설정
#define RXD 3 //RXD를 3번 핀으로 설정
#define DHTPIN 4  //온습도 센서 out 4번 핀으로 설정
#define DC_MOTOR 6 //6번 핀으로 DC 모터 제어
#define PULSE 7 //7번 핀으로 입력 펄스 인가
#define ROOM_LED 12 //12번 핀으로 방 LED 제어 
#define LIVINGROOM_LED 13 //13번 핀으로 거실 LED 제어 
#define OUTPUT_VOLTAGE A0 //A0 핀으로 출력 전압 입력
#define DHTTYPE DHT11   // 온습도 센서 타입 선택

DHT dht(DHTPIN, DHTTYPE); //DHT 센서 초기화
SoftwareSerial mySerial(TXD, RXD); //소프트웨어 시리얼 mySerial 객체 선언

void ledControl(int pin,int count); //매개 변수로 제어 핀과 count 횟수를 가진 ledControl() 함수 선언
void motor_Control(byte dcStep); //DC 모터 동작과 관련된 motor_Control 함수 선언

int LivingroomLedCount = 0; //거실 LED 제어 시 발생한 스위칭 횟수를 저장
int roomLedCount = 0; //방 LED 제어 시 발생한 스위칭 횟수를 저장
byte motorStep = 0; //모터 속도 단계를 저장
float preVoltage = 0; //0~1023 범위의 출력 전압
float voltage = 0; //0~5 범위의 출력 전압
float dustDensity = 0; //미세먼지 농도 수치 
float sumDustDensity = 0; //미세먼지 농도 수치 합
float avgDustDensity = 0; //미세먼지 농도 수치 평균

void setup() {
  dht.begin(); //온습도 센서 동기화 
  mySerial.begin(9600); //소프트웨어 시리얼 동기화
  pinMode(OUTPUT_VOLTAGE, INPUT); //A0 핀 입력으로 설정
  pinMode(DC_MOTOR, OUTPUT); //6번 핀 출력으로 설정
  pinMode(PULSE, OUTPUT); //7번 핀 출력으로 설정
  pinMode(ROOM_LED, OUTPUT); //12번 핀 출력으로 설정
  pinMode(LIVINGROOM_LED, OUTPUT); //13번 핀 출력으로 설정
}

void loop() { 
  delay(1000);
  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 loop() 함수 종료
    return;
  }
  
  sumDustDensity = 0; //미세먼지 농도 수치 합을 초기화 
  for(int i=0;i<30;i++) //미세먼지 농도 수치 30회 측정
  {
    digitalWrite(PULSE, LOW); //입력 펄스 인가
    delayMicroseconds(280); //0.28ms 대기
    preVoltage = analogRead(OUTPUT_VOLTAGE); //A0 핀으로부터 데이터를 읽어 preVoltage에 저장
    delayMicroseconds(40); //0.04ms 대기
    digitalWrite(PULSE, HIGH); //입력 펄스 종료  
    delayMicroseconds(9680); //9.68ms 대기
    voltage = preVoltage * 5.0 / 1024.0; //0~5 범위 전압 값으로 변환 후 voltage에 저장
    dustDensity = (voltage-0.3)/0.005; //미세먼지 농도 수치 dustDensity에 저장
    sumDustDensity += dustDensity; //미세먼지 농도 수치 합계
    delay(10); //데이터 계산 간 10ms 대기
  }
  avgDustDensity = sumDustDensity / 30.0; //미세먼지 농도 수치의 평균 값을 avgDustDensity에 저장  
  
  mySerial.print(temperature,1); //소수점 첫째자리까지 온도 데이터 출력  
  mySerial.print(" "); //각 데이터를 공백으로 구분
  mySerial.print(humidity,1); //소수점 첫째자리까지 습도 데이터 출력
  mySerial.print(" "); //각 데이터를 공백으로 구분
  mySerial.println(avgDustDensity,1); //소수점 첫째자리까지 미세먼지 데이터 출력  
  
  if(mySerial.available()) //앱에서 데이터가 발생되어 블루투스 모듈로 데이터가 입력되었을 때 
  {    
    byte input = mySerial.read();//데이터를 읽어 input 변수에 저장      
    
    if(input >= 30) //DC 모터 제어와 관련된 데이터 발생 시 
    {
      motorStep = input%10; //모터 속도를 나타내는 단계 처리
      input = input/10; //모터 제어와 관련된 고유 번호 3 처리 
    }    
              
    switch(input) //input 변수의 값에 맞는 case 문 실행 
    {
      case 1:
        LivingroomLedCount++; //1이 발생될 때마다 LivingroomLedCount 변수 1증가
        ledControl(LIVINGROOM_LED,LivingroomLedCount); //거실 LED 제어 핀과 LivingroomLedCount 값을 매개 변수로하여 ledControl()함수 호출
        break;
      case 2:
        roomLedCount++; //2가 발생될 때마다 roomLedCount 변수 1증가
        ledControl(ROOM_LED,roomLedCount); //방 LED 제어 핀과 roomLedCount 값을 매개 변수로하여 ledControl()함수 호출
        break;
      case 3:
        motor_Control(motorStep); //모터 속도 단계를 매개 변수로하여 motor_Contorl() 함수 호출       
        break;        
    }           
  }  
}

void ledControl(int pin,int count) //ledControl() 함수 정의
{
  if(count%2==1) //count 값이 홀수일 때 
  {
    digitalWrite(pin, HIGH); //LED를 제어하는 핀에 HIGH 신호를 발생시켜 LED 점등
  }
  else //count 값이 짝수일 때
  {
    digitalWrite(pin, LOW); //LED를 제어하는 핀에 LOW 신호를 발생시켜 LED 소등
  }
}
void motor_Control(byte dcStep) //motor_Control 함수 정의
{
  switch(dcStep) //현재 DC 모터 속도 단계
  {
    case 0: //0 단계
      analogWrite(DC_MOTOR, 0); //모터 멈춤
      break;
    case 1: //1 단계
      analogWrite(DC_MOTOR, 32); //1/8 속도로 DC 모터 출력
      break;
    case 2: //2 단계
      analogWrite(DC_MOTOR, 64); //2/8 속도로 DC 모터 출력
      break;
    case 3: //3 단계
      analogWrite(DC_MOTOR, 96); //3/8 속도로 DC 모터 출력      
      break;      
  }
}
