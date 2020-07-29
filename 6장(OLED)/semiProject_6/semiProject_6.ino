#include <U8glib.h> //U8glib 라이브러리 추가 
#include <DHT.h> //DHT 라이브러리 추가 
 
#define DHTPIN 2 //데이터 신호 핀 설정
#define DHTTYPE DHT11 //온습도 센서 타입 설정
// 0.96인치 128x64 OLED
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  //SSD1306 128X64 I2C 규격 선택 

DHT dht(DHTPIN, DHTTYPE); //온습도 센서 초기화 

void setup() {
  dht.begin(); //핀 설정
}

void loop() {
  float humidity, temperature, di;//습도, 온도, 불쾌지수 변수 선언
  humidity = dht.readHumidity(); //습도 데이터 읽기
  temperature = dht.readTemperature(); //온도 데이터 읽기
  di = (float)9/5*temperature-0.55*((float)1-humidity/100)*((float)9/5*temperature-26)+32; //불쾌지수 계산

  if (isnan(humidity) || isnan(temperature)) {  //데이터를 읽어오지 못했을 경우 loop() 함수 종료
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
}
