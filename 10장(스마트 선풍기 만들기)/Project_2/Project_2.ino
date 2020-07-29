#include <Servo.h> //서보 모터 라이브러리 추가
#include <U8glib.h> //U8glib 라이브러리 추가 
#include <DHT.h> //DHT 센서 라이브러리 추가 

#define TRIG 2 //2번 핀을 Trig로 설정
#define ECHO 3 //3번 핀을 Echo로 설정
#define DHT_OUT 4 //4번 핀을 온습도센서 out으로 설정
#define DC_MOTOR 5 //5번 핀으로 DC 모터 제어 
#define SERVO 6 //6번 핀으로 서보 모터 제어 
#define TOUCH 7 //7번 핀으로 터치 이벤트 처리
#define BLUE_PIN 9 //9번 핀으로 BLUE 제어 
#define GREEN_PIN 11 //11번 핀으로 GREEN 제어
#define RED_PIN 10 //10번 핀으로 RED 제어
#define DHTTYPE DHT11 //DHTTYPE을 DHT11로 설정

// 0.96인치 128x64 OLED
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  //SSD1306 128X64 I2C 규격 선택 
DHT dht(DHT_OUT, DHTTYPE); //DHT 센서 초기화
Servo myservo; // 서보 모터 제어를 위한 객체 생성

int motorStep = 0; //DC 모터의 단계를 저장하는 변수
int tempStep; //불쾌지수가 높음 단계 이상이고 사람과의 거리가 50cm 이하일 때 모터 속도 설정을 위한 임시 변수
int rotateState = 0;  //서보 모터 회전 여부를 결정하는 변수 
int autoState = 0; //자동 운전에 대한 여부를 저장하는 변수
int pos = 0;    // 서보 모터 위치 값을 저장하는 변수 선언
unsigned long startTime; //프로그램이 실행된 후 터치 이벤트가 발생하기 전까지의 시간을 저장
unsigned long touchTime; //터치 이벤트가 지속적으로 발생한 시간을 저장

void colorPrint(int red, int green, int blue); //3색 LED 색깔 출력과 관련된 colorPrint 함수 선언
void motor_Control(int dcStep); //DC 모터 동작과 관련된 motor_Control 함수 선언

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT); //TRIG 제어 핀 출력용으로 설정
  pinMode(ECHO, INPUT); //ECHO 제어 핀 입력용으로 설정
  pinMode(DC_MOTOR, OUTPUT); //DC 모터 제어 핀 출력용으로 설정
  pinMode(SERVO, OUTPUT); //서보 모터 제어 핀 출력용으로 설정
  pinMode(TOUCH, INPUT); //터치 센서 제어 핀 입력용으로 설정
  pinMode(RED_PIN, OUTPUT); //RED 핀 출력용으로 설정
  pinMode(GREEN_PIN, OUTPUT); //GREEN 핀 출력용으로 설정
  pinMode(BLUE_PIN, OUTPUT); //BLUE 핀 출력용으로 설정 
  myservo.attach(SERVO); // 서보 모터 제어를 위한 핀 설정
  dht.begin(); //DHT 제어 핀 설정
  Serial.begin(9600); //시리얼 통신 동기화
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG, HIGH); //초음파를 발사 
  delayMicroseconds(10); //2마이크로초 유지 
  digitalWrite(TRIG, LOW);  //전압을 LOW로 설정
  long duration = pulseIn(ECHO, HIGH); //ECHO 핀이 HIGH로 유지된 시간을 duration 변수에 저장

  if(duration == 0) //시간이 0이면 종료 
  {
    return;
  }
  long distance = duration / 58; //시간을 58로 나눠 cm 단위의 거리를 distance에 저장

  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
  float di = (float)9/5*temperature-0.55*((float)1-humidity/100)*((float)9/5*temperature-26)+32; //불쾌지수를 계산하여 변수에 저장

  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 loop() 함수 종료
    return;
  }
  
  u8g.firstPage(); //picture loop의 시작
  do {
    u8g.setFont(u8g_font_fub14); //온도, 습도 폰트지정
    u8g.setPrintPos(5, 20); //온도 데이터 출력 커서 설정

    u8g.print(temperature,1); //온도 데이터(소수점 첫째 자리) 출력
    u8g.print("\xb0""C"); //온도 기호(°C) 출력 
    u8g.setPrintPos(70, 20); //습도 데이터 출력 커서 설정
    u8g.print(humidity,1); //습도 데이터(소수점 첫째 자리) 출력
    u8g.print("%"); //습도 기호(%) 출력
    u8g.setFont(u8g_font_fub20); //불쾌지수 폰트지정
    u8g.setPrintPos(40, 55); //불쾌지수 데이터 출력 커서 설정
    u8g.print(di,1); //불쾌지수 데이터(소수점 첫째 자리) 출력
  } while(u8g.nextPage()); //picture loop의 끝  

  //불쾌지수 단계에 따라 3색 LED 제어 
  if(di >= 80) //매우 높음 단계일 때 
  {
    colorPrint(255,0,0); //빨간색 출력
  }
  else if(di >= 75) //높음 단계일 때 
  {
    colorPrint(255,10,0); //주황색 출력
  }
  else if(di >= 68) //보통 단계일 때 
  {
    colorPrint(0,255,0); //초록색 출력
  }
  else //낮음 단계일 때 
  {
    colorPrint(0,0,255); //파란색 출력
  }
   
  int touchValue = digitalRead(TOUCH); //터치 이벤트 값을 touchValue에 저장
  delay(200); //터치 이벤트 사이 0.2초 지연 시간 부여 
  
  if(touchValue == HIGH) //터치 이벤트가 발생했을 때
  {
    motorStep++; //motorStep 1 증가
    
    motor_Control(motorStep); //motor_Control() 함수 호출
    startTime = millis(); //터치 이벤트가 지속적으로 발행하기 전까지의 시간을 startTime 변수에 저장
    while(digitalRead(TOUCH) == HIGH); //손가락을 계속 누르고 있는 시간을 측정하기 위한 루프
    touchTime = millis() - startTime; //터치 이벤트가 지속적으로 발생한 시간을 touchTime에 저장
    
    if(touchTime >= 1000 && touchTime <= 3000) //지속적으로 터치 이벤트가 발생한 시간이 1~3초 사이일 때 회전
    {
      rotateState++; //회전 여부를 결정하는 rotateState 변수 1 증가
    }    
    else if(touchTime > 3000) //터치 이벤트가 3초가 초과할 때 
    {
      autoState++; //자동 운전 여부를 결정하는 autoState 변수 1 증가
    }
  }
  if((rotateState%2 == 1) && (motorStep != 0)) //rotateState 변수가 홀수이고 motorStep이 0이 아닐 때 실행
  {
    for (pos = 10; pos <= 60; pos += 1) { // 10 ~ 60°까지 1씩 증가시켜 루프를 돌림 
    motor_Control(motorStep);  
    myservo.write(pos);              // pos 변수 값의 위치로 회전(1도 씩 회전)
    delay(15);                       // 서보 모터가 위치까지 도달할 수 있도록 15ms 대기
    }
    for (pos = 60; pos >= 10; pos -= 1) { // 60 ~ 10°까지 1씩 감소시켜 루프를 돌림
    motor_Control(motorStep);  
    myservo.write(pos);              
    delay(15);                       
    }           
  } 
  else if(rotateState%2 == 0) //회전을 하지 않을 때 
  {
    myservo.write(30); //30°로 서보모터 이동(정방향 동작)
  }
 
  if(autoState%2 == 1) //autoState가 홀수 일 때 자동 운전
  {
    //불쾌지수가 매우 높음 단계이고 사람과의 거리가 50cm 이하일 때 
    if(di >= 80 && distance <= 50) 
    {   
      motorStep = 3; //DC 모터 속도를 3단계로 설정
      motor_Control(motorStep); //최대 속도 출력    
    }
    //불쾌지수가 높음 단계이고 사람과의 거리가 50cm 이하일 때
    else if(di >= 75 && distance <= 50) 
    {
      tempStep = 2; //DC 모터 속도를 2단계로 설정
      if(motorStep > tempStep) //현재 DC 모터의 속도가 3단계일 때 
      {
        motor_Control(motorStep); //현재 속도로 DC 모터 출력
      }
      else //현재 DC 모터의 속도가 2단계 이하일 때 
      {
        motorStep = tempStep; //DC 모터의 속도를 2단계로 설정
        motor_Control(motorStep); //2단계 속도로 DC 모터 출력
      }            
    }
    else //불쾌지수가 75 미만이거나 사람과의 거리가 50cm 초과할 때 
    {
      motorStep = 4; //모터 단계 4로 설정
      motor_Control(motorStep); //모터 멈춤
    }
  }
  Serial.print("touch count:");
  Serial.print(motorStep); //시리얼 모니터로 현재 DC 모터 단계 확인
  Serial.print("\tcontinuous time : ");
  Serial.print(touchTime); //시리얼 모니터로 이벤트 시간 확인
  Serial.print("\tdistance : ");
  Serial.println(distance); //시리얼 모니터로 거리 확인
}

void colorPrint(int red, int green, int blue) //colorPrint 함수 정의
{
  analogWrite(RED_PIN, red); //RED 핀 PWM 출력
  analogWrite(GREEN_PIN, green); //GREEN 핀 PWM 출력
  analogWrite(BLUE_PIN, blue); //BLUE 핀 PWM 출력
}

void motor_Control(int dcStep) //motor_Control 함수 정의
{
  switch(dcStep) //현재 DC 모터 속도 단계
  {
    case 1: //1단계
      analogWrite(DC_MOTOR, 85); //최대 속도의 1/3 속도 출력
      break;
    case 2: //2단계
      analogWrite(DC_MOTOR, 170); //최대 속도의 2/3 속도 출력
      break;
    case 3: //3단계
      analogWrite(DC_MOTOR, 255); //최대 속도 출력
      break;
    case 4:
      analogWrite(DC_MOTOR, 0); //모터 멈춤
      motorStep = 0; //motorStep 변수 0으로 초기화 
      break;      
  }
}
