#define MAGNETIC 7 //7번 핀으로 마그네틱 스위치 신호 처리
#define PIR 8 //8번 핀으로 인체 감지 센서 신호 처리 
#define GREEN_PIN 12 //12번 핀으로 GREEN 핀 제어
#define RED_PIN 13 //13번 핀으로 RED 핀 제어

bool occupied = false; //화장실 사용 여부를 판단하는 변수 

void setup() {
  // put your setup code here, to run once:
  pinMode(MAGNETIC, INPUT_PULLUP); //7번 핀을 INPUT_PULLUP으로 설정
  pinMode(PIR, INPUT); //8번 핀은 입력으로 설정
  pinMode(GREEN_PIN, OUTPUT); //12번 핀을 출력으로 설정
  pinMode(RED_PIN, OUTPUT); //13번 핀을 출력으로 설정
  Serial.begin(9600); //시리얼 통신 초기화 
}

void loop() {
  // put your main code here, to run repeatedly:
  int magneticValue = digitalRead(MAGNETIC); //마그네틱 스위치의 출력 신호를 magneticValue 변수에 저장
  int pirValue = digitalRead(PIR); //인체 감지 센서의 출력 신호를 pirValue 변수에 저장
  Serial.print("magnetic State :"); //마그네틱 스위치 상태 출력
  Serial.println(magneticValue);
  Serial.print("pir State :"); //인체 감지 센서 상태 출력
  Serial.println(pirValue);
  if(magneticValue == 0 && pirValue == 1) //화장실 문이 닫혀있고 동작이 감지되었을 때(화장실 내 사람이 있을 때)
  {
    occupied = true; //화장실을 사용하고 있다는 의미로 true 설정
  }
  else if(magneticValue == 1 && pirValue == 1) //화장실 문이 열려있고 동작이 감지되었을 때(화장실 내 사람이 없을 때)
  {   
       occupied = false; //화장실을 사용하고 있지 않다는 의미로 false 설정    
  }
  if(occupied == true) //화장실을 사용하고 있을 때 
  {
    digitalWrite(GREEN_PIN, LOW); //초록색 소등
    digitalWrite(RED_PIN, HIGH); //빨간색 점등
  }
  else //화장실을 사용하고 있지 않을 때 
  {
    digitalWrite(RED_PIN, LOW); //빨간색 소등
    digitalWrite(GREEN_PIN, HIGH); //초록색 점등
  }    
}
