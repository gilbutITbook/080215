#include "DHT.h" //DHT 센서 라이브러리 추가 

#define DHTPIN 2 //데이터 신호 핀 설정
#define DHTTYPE DHT11 // 온습도 센서 타입 선택
#define RED 11   //11번 핀으로 RED 핀 제어 
#define GREEN 10 //10번 핀으로 GREEN 핀 제어 
#define BLUE 9  //9번 핀으로 BLUE 핀 제어 

DHT dht(DHTPIN, DHTTYPE); //DHT 센서 초기화 

void colorPrint(int redValue, int greenValue, int blueValue); //색깔 출력 함수 선언

void setup() {
  pinMode(RED, OUTPUT); //11번 핀 출력용으로 설정
  pinMode(GREEN, OUTPUT); //10번 핀 출력용으로 설정
  pinMode(BLUE, OUTPUT); //9번 핀 출력용으로 설정
  Serial.begin(9600); //시리얼 통신 동기화 
  dht.begin(); //핀 설정
}

void loop() {
  delay(2000); //측정 간 2초 대기

  float humidity = dht.readHumidity(); //습도 데이터를 읽어와 변수에 저장
  float temperature = dht.readTemperature(); //온도 데이터를 읽어와 변수에 저장
  float di = (float)9/5*temperature-0.55*((float)1-humidity/100)*((float)9/5*temperature-26)+32; //불쾌지수를 계산하여 변수에 저장

  if (isnan(humidity) || isnan(temperature)) { //데이터를 읽어오지 못했을 경우 loop() 함수 종료
    return;
  }

  if(di >= 80) //불쾌지수 데이터가 80 이상일 때(매우 높음)
  {
    colorPrint(255,0,0);  //빨간색 점등
  }
  else if(di >= 75) //불쾌지수 데이터가 75 ~ 80 미만일 때(높음)
  {
    colorPrint(255,128,0); //주황색 점등   
  }
  else if(di >= 68) //불쾌지수 데이터가 68 ~ 75 미만일 때(보통)
  {
    colorPrint(0,255,0); //녹색 점등
  }
  else //불쾌지수 데이터가 68 미만일 때(낮음)
  {
    colorPrint(0,0,255); //파란색 점등   
  }  
  Serial.print("Humidity:");
  Serial.print(humidity,1); //소수점 첫째자리까지 습도 출력
  Serial.print("%\t");
  Serial.print("Temperature:");
  Serial.print(temperature,1); //소수점 첫째자리까지 온도 출력
  Serial.print("C\t");
  Serial.print("Discomfort Index:");
  Serial.println(di,1); //소수점 첫째자리까지 불쾌지수 출력

}
void colorPrint(int redValue, int greenValue, int blueValue) //색깔 출력 함수 정의
{
  analogWrite(RED, redValue); 
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);  
}
