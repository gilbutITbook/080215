#include "DHT.h" //DHT 센서 라이브러리 추가 

#define DHTPIN 2 //데이터 신호 핀 설정
#define DHTTYPE DHT11 // 온습도 센서 타입 선택

DHT dht(DHTPIN, DHTTYPE); //DHT 센서 초기화 

void setup() {
  Serial.begin(9600); //시리얼 통신 동기화 
  dht.begin(); //핀 설정
}

void loop() {
  delay(2000); //측정 간 2초 대기

  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
  float di = (float)9/5*temperature-0.55*((float)1-humidity/100)*((float)9/5*temperature-26)+32; //불쾌지수를 계산하여 변수에 저장

  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 loop() 함수 출력
    return;
  }
  
  Serial.print("Discomfort Index:");
  Serial.println(di,1); //소수점 첫째자리까지 불쾌지수 출력

}
