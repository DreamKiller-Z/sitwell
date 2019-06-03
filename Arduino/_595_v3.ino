#include "SPI.h"
//#include "MegunoLink.h"

#define SRCLR 2
#define RCLK 8
//PrintWriter output;
//String result = "";
int sensorValue[256];
int sensor = A0;
int num = 0;

void getValue(uint8_t x,uint8_t y,boolean mode){
  uint8_t tx_buffer[4];
  if(mode){
    tx_buffer[0] = 0x01<<x;
    tx_buffer[1] = ~tx_buffer[0];
    tx_buffer[3] = 0x01<<y;
    tx_buffer[2] = ~tx_buffer[3];
  }else{
    tx_buffer[0] = 0x01<<x;
    tx_buffer[1] = 0x00;
    tx_buffer[3] = 0x01<<y;
    tx_buffer[2] = 0x00;
  }
  
  SPI.beginTransaction(SPISettings(1000000,MSBFIRST,SPI_MODE0));
  SPI.transfer(tx_buffer[0]);
  SPI.transfer(tx_buffer[1]);
  SPI.transfer(tx_buffer[2]);
  SPI.transfer(tx_buffer[3]);
  SPI.endTransaction();
  digitalWrite(RCLK,HIGH);
  digitalWrite(RCLK,LOW);
  delayMicroseconds(200);
//  for(int i=0;i!=6;i++){
  pixel = x * 8 + y + num * 64;
  sensorValue[pixel] = analogRead(A0 + num);
  result String(sensorValue[pixel]);
//  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1000000);
//  Serial.begin(115200);
  SPI.begin();
  pinMode(SRCLR,OUTPUT);
  pinMode(RCLK,OUTPUT);
  digitalWrite(SRCLR,HIGH);
  digitalWrite(RCLK,LOW);
  delay(1);
  digitalWrite(SRCLR,LOW);
  delay(1);
  digitalWrite(SRCLR,HIGH);
  delay(1);
  digitalWrite(RCLK,HIGH);
  delay(1);
  digitalWrite(RCLK,LOW);
  delay(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  String result = ""
  int i_tracker;
  int j_tracker;
  for(uint8_t i=0;i!=8;i++){
    i_tracker = i;
    for(uint8_t j=0;j!=8;j++){
      j_tracker = j
      result += getValue(i,j,true) + ',';
    }
  }
  result.erase(result.size() - 1);
  
  delay(200);
//  Serial.flush();
  Serial.print(String(num) + ":");
  Serial.println("");
  num += 1;
  if (num >3){
    num = 0;
    Serial.print(result);
    Serial.println();
    Serial.print("i_tracker: ");
    Serial.print(i_tracker);
    Serial.println();
    Serial.print("j_tracker: ");
    Serial.print(j_tracker);
    Serial.println();
    Serial.flush();
//    result = "";

//    sensor = A0;
  }
//  else{
//    sensor = sensor + num;
//
//  }
  
  delay(200);
  // Serial.println(getValue(4,4,true));

//  for(uint8_t i=0;i!=256;i++){
//    Serial.print(sensorValue[i]);
//    Serial.print(",");
//    Serial.println("");
//
////    output.println(sensorValue[i]);
////    output.flush();
//  }
  Serial.println("--------");
//  Serial.flush();

//  Serial.println(getValue(0,0,true));
}
