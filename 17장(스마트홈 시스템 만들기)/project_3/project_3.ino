#include <SoftwareSerial.h> //소프트웨어 시리얼 라이브러리 추가
#include <U8glib.h> //u8g 라이브러리 추가 
#include <DHT.h> //온습도 센서 라이브러리 추가
#include <Servo.h> //서보 모터 라이브러리 추가 

#define TXD 2 //TXD를 2번 핀으로 설정
#define RXD 3 //RXD를 3번 핀으로 설정
#define DHTPIN 4  //온습도 센서 out 4번 핀으로 설정
#define SERVO 5 //서보 모터 각도 제어 5번 핀으로 설정
#define DC_MOTOR 6 //DC 모터 제어 6번 핀으로 설정
#define PULSE 7 //미세먼지 센서 입력 펄스를 7번 핀으로 인가
#define PIR 8 //인체 감지 센서 out 8번 핀으로 설정
#define PIEZO 9 //피에조 스피커 +극 9번 핀으로 설정
#define DOOR_LED 10 //현관 LED 등 제어 10번 핀으로 설정
#define MAGNETIC 11 //마그네틱 스위치 제어 11번 핀으로 설정
#define ROOM_LED 12 //방 LED 제어 12번 핀으로 설정
#define LIVINGROOM_LED 13 //거실 LED 제어 13번 핀으로 설정
#define OUTPUT_VOLTAGE A0 //미세먼지 센서 출력 전압 A0 핀으로 설정
#define GAS_OUT A1 //가스 센서 아날로그 출력 A1으로 설정
#define DHTTYPE DHT11   // 온습도 센서 타입 선택

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  //SSD1306 128X64 I2C 규격 선택 
DHT dht(DHTPIN, DHTTYPE); //DHT 센서 초기화
SoftwareSerial mySerial(TXD, RXD); //소프트웨어 시리얼 mySerial 객체 선언
Servo myservo; //서보 모터 객체 선언

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
  Serial.begin(9600); //시리얼 통신 동기화
  mySerial.begin(9600); //소프트웨어 시리얼 동기화
  myservo.attach(SERVO); // 서보 모터 제어를 위한 핀 설정
  myservo.write(80); //가스 배관과 일직선 상에 위치
  pinMode(DC_MOTOR, OUTPUT); //6번 핀 출력으로 설정
  pinMode(PULSE, OUTPUT); //7번 핀 출력으로 설정
  pinMode(PIR, INPUT); //8번 핀을 입력으로 설정
  pinMode(PIEZO, OUTPUT); //9번 핀을 출력으로 설정  
  pinMode(DOOR_LED, OUTPUT); //10번 핀을 출력으로 설정
  pinMode(MAGNETIC, INPUT_PULLUP); //11번 핀을 INPUT_PULLUP으로 설정
  pinMode(ROOM_LED, OUTPUT); //12번 핀 출력으로 설정
  pinMode(LIVINGROOM_LED, OUTPUT); //13번 핀 출력으로 설정
  pinMode(OUTPUT_VOLTAGE, INPUT); //A0 핀 입력으로 설정
  pinMode(GAS_OUT, INPUT); //A1 핀 입력으로 설정
}

void loop() { 
  delay(1000);
  int pirValue = digitalRead(PIR); //동작 감지 신호를 value 변수에 저장
  int magneticValue = digitalRead(MAGNETIC); //마그네틱 스위치의 출력 신호를 magneticValue 변수에 저장
  int gasValue = analogRead(GAS_OUT); //아날로그 데이터를 읽어 value 변수에 저장
  Serial.print("Pir state :"); //인체 감지 센서 상태 확인
  Serial.print(pirValue);
  Serial.print("\t");
  Serial.print("magnetic state :"); //마그네틱 스위치 상태 확인
  Serial.print(magneticValue);
  Serial.print("\t");
  Serial.print("gas value :"); //가스 센서 데이터 확인
  Serial.println(gasValue);
  
  if(pirValue == HIGH) //동작을 감지했을 경우
  {    
    digitalWrite(DOOR_LED, HIGH); //LED 점등
    delay(5000); //3초 동안 지연
  }  
  else
  {
    digitalWrite(DOOR_LED, LOW); //LED 소등       
  }
  if(magneticValue == 1 && pirValue == 0) //현관문이 열려있고 동작이 감지되지 않았을 때 
  {
     for(int i=0;i<2;i++) //알림음을 2회 출력
    {
      tone(PIEZO, 6271, 150); //6271Hz 주파수의 음을 0.15초 출력
      delay(200); //0.2초 대기 
      tone(PIEZO, 4186, 150); //4186Hz 주파수의 음을 0.15초 출력
      delay(200);
    }
  }
  if(gasValue >= 250) //가스가 누출되는 상황일 때 
  {
    for(int i=0;i<5;i++) //경고음을 5회 출력
    {
      tone(PIEZO, 2093, 250); //2093Hz 주파수의 음을 0.25초 출력
      delay(200); //0.2초 대기 
      tone(PIEZO, 1567, 250); //1567Hz 주파수의 음을 0.25초 출력
      delay(200);      
    }    
    myservo.write(170); //가스 배관과 90도 방향이 되도록 회전
    delay(200); // 서보 모터가 위치까지 도달할 수 있도록 0.2초 대기
    myservo.detach(); //서보 모터 출력 신호 정지
  }
  
  
  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 아래 메시지 출력
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
  
  u8g.firstPage(); //picture loop의 시작
  do {
    u8g.setFont(u8g_font_fub14); //온도, 습도 폰트지정
    u8g.setPrintPos(5, 20); //온도 데이터 출력 커서 설정
    u8g.print(temperature,1); //온도 데이터(소수점 첫째 자리) 출력
    u8g.print("\xb0""C"); //온도 기호(°C) 출력 
    u8g.setPrintPos(70, 20); //습도 데이터 출력 커서 설정
    u8g.print(humidity,1); //습도 데이터(소수점 첫째 자리) 출력
    u8g.print("%"); //습도 기호(%) 출력
    u8g.setFont(u8g_font_fub20); //미세먼지 농도 수치 폰트지정
    u8g.setPrintPos(40, 55); //미세먼지 농도 수치 출력 커서 설정
    u8g.print(avgDustDensity,1); //미세먼지 농도 수치(소수점 첫째 자리) 출력
  } while(u8g.nextPage()); //picture loop의 끝  
  
  mySerial.print(temperature,1); //소수점 첫째 자리까지 온도 데이터 출력  
  mySerial.print(" "); //각 데이터를 공백으로 구분
  mySerial.print(humidity,1); //소수점 첫째 자리까지 습도 데이터 출력
  mySerial.print(" "); //각 데이터를 공백으로 구분
  mySerial.println(avgDustDensity,1); //소수점 첫째 자리까지 미세먼지 데이터 출력  
  
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
    case 0: //0단계
      analogWrite(DC_MOTOR, 0); //모터 멈춤
      break;
    case 1: //1단계
      analogWrite(DC_MOTOR, 32); //1/8 속도로 DC 모터 출력
      break;
    case 2: //2단계
      analogWrite(DC_MOTOR, 64); //2/8 속도로 DC 모터 출력
      break;
    case 3: //3단계
      analogWrite(DC_MOTOR, 96); //3/8 속도로 DC 모터 출력      
      break;      
  }
}
