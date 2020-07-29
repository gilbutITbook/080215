#include "DHT.h" //DHT 센서 라이브러리 추가 

#define ECHO 2 //2번 핀으로 Echo 설정
#define TRIG 3 //3번 핀으로 Trig 설정
#define DHTPIN 4 //4번 핀을 데이터 신호 처리 설정
#define MOTOR 6 //6번 핀으로 DC 모터 제어
#define DHTTYPE DHT11 // 온습도 센서 타입 선택

DHT dht(DHTPIN, DHTTYPE); //DHT 센서 초기화 

void setup() {
  // put your setup code here, to run once:
  pinMode(ECHO, INPUT);   //2번 핀 입력용으로 설정
  pinMode(TRIG, OUTPUT);  //3번 핀 출력용으로 설정
  pinMode(MOTOR, OUTPUT); //6번 핀 출력용으로 설정
  Serial.begin(9600); //시리얼 통신 동기화 
  dht.begin(); //핀 설정
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(TRIG, HIGH); //펄스파 발생
  delayMicroseconds(10); //10마이크로초 지연
  digitalWrite(TRIG, LOW);  //펄스파 종료
  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
  float di = (float)9/5*temperature-0.55*((float)1-humidity/100)*((float)9/5*temperature-26)+32; //불쾌지수를 계산하여 변수에 저장
  long duration = pulseIn(ECHO, HIGH); //Echo핀이 HIGH가 된 이후 지연된 펄스의 시간을 duration 변수에 저장

  if(duration == 0) //시간이 0이면 종료 
  {
    return;
  }
  long distance = duration / 58; //총 걸리는 시간을 58로 나눠 거리를 측정

  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 아래 메시지 출력
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if(di >= 80 && distance <= 50) //불쾌지수 데이터가 80 이상(매우 높음)이고 초음파 센서와 사람 간의 거리가 50cm 이하일 때
  {
    analogWrite(MOTOR, 255); //최대 속도 출력
  }
  else if(di >= 75 && distance <= 50) //불쾌지수 데이터가 75 ~ 80 미만(높음)이고 초음파 센서와 사람 간의 거리가 50cm 이하일 때
  {
    analogWrite(MOTOR, 170); //최대 속도의 2/3 속도 출력
  }
  else
  {
    analogWrite(MOTOR, 0); //모터 멈춤
  }
  Serial.print("Discomfort Index:");
  Serial.print(di,1); //소수점 첫째자리까지 불쾌지수 출력  
  Serial.print("\tDistance :");
  Serial.print(distance,1); //소수점 첫째자리까지 거리 출력   
  Serial.println("cm");
  delay(2000); //불쾌지수,거리 데이터를 2초간 마다 출력
}
