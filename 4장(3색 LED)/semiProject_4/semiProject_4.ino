#define RED_PIN 11 //11번 핀으로 RED 핀 제어 
#define GREEN_PIN 10 //10번 핀으로 GREEN 핀 제어
#define BLUE_PIN 9 //9번 핀으로 BLUE 핀 제어

void colorPrint(int redValue, int greenValue, int blueValue); //색깔 출력 함수 선언

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT); //11번 핀을 출력으로 설정
  pinMode(GREEN_PIN, OUTPUT); //10번 핀을 출력으로 설정
  pinMode(BLUE_PIN, OUTPUT); //9번 핀을 출력으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int di=60;di<90;di+=2)
  {
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
    delay(500); //색깔 전환을 확인하기 위한 지연 시간 
  } 
}
void colorPrint(int redValue, int greenValue, int blueValue) //색깔 출력 함수 정의
{
  analogWrite(RED_PIN, redValue); 
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);  
}
