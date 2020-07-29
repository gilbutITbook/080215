#include "DHT.h" //DHT 센서 라이브러리 추가
#define MOTOR 6 //6번 핀으로 DC 모터 제어
#define DHTPIN 2 //데이터 신호 핀 설정
#define DHTTYPE DHT11 // 온습도 센서 타입 선택

DHT dht(DHTPIN, DHTTYPE); //DHT 센서 초기화 

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR, OUTPUT); //6번 핀 출력 용으로 설정
  Serial.begin(9600); //시리얼 통신 동기화 
  dht.begin(); //핀 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000); //측정 간 2초 대기
  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
  float di = (float)9/5*temperature-0.55*((float)1-humidity/100)*((float)9/5*temperature-26)+32; //불쾌지수를 계산하여 변수에 저장

  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 아래 메시지 출력
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if(di >= 80) //불쾌지수 데이터가 80 이상일 때(매우 높음)
  {
    analogWrite(MOTOR, 255); //최대 속도 출력
  }
  else if(di >= 75) //불쾌지수 데이터가 75 ~ 80 미만일 때(높음)
  {
    analogWrite(MOTOR, 170); //최대 속도의 2/3 속도 출력
  }
  else
  {
    analogWrite(MOTOR, 0); //모터 멈춤
  }
  Serial.print("Discomfort Index:");
  Serial.println(di,1); //소수점 첫째자리까지 불쾌지수 출력  
}
