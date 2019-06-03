#include "SPI.h"
//#include "MegunoLink.h"

#define SRCLR 2
#define RCLK 8
//PrintWriter output;
//String result = "";
//int sensorValue[256];
//int sensor = A0;
//int num = 0;

String getValue(int pin, int x, int y, boolean mode){
  int pixel;
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
  
  SPI.beginTransaction(SPISettings(10000000,MSBFIRST,SPI_MODE0));
  SPI.transfer(tx_buffer[0]);
  SPI.transfer(tx_buffer[1]);
  SPI.transfer(tx_buffer[2]);
  SPI.transfer(tx_buffer[3]);
  SPI.endTransaction();
  digitalWrite(RCLK,HIGH);
  digitalWrite(RCLK,LOW);
  delayMicroseconds(200);
//  for(int i=0;i!=6;i++){

  pixel = x * 8 + y + pin * 64;
  return String(analogRead(pixel));
//  Serial.flush();
//  result += String(sensorValue[x*8+y+num*64]) + ",";
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
//  String temp = "";
  String result = "";
  int pin = 0;
  int row = 0;
  int col = 0;
  boolean mode = true;
  
  for (pin = 0; pin != 8; pin ++) {
    for(row = 0; row != 8; row ++){
      for(col = 0; col !=8 ; col ++){
        result += ("[" + String(pin) + ", " + String(row) + ", " + String(col) + "]") + getValue(pin, row, col, mode) + ", ";
      }
    }    
  }
  
//  result.remove(result.length() - 1);
  
  Serial.print("Pin: " + String(pin));
  Serial.println();
  Serial.print("row: " + String(row));
  Serial.println();
  Serial.print("col: " + String(col));
  Serial.println();
  Serial.print("Result:");
  Serial.println();
  Serial.print(result);
  Serial.println();
  Serial.print("DONE");
  Serial.println();
////  Serial.flush();

//
//  Serial.print(
//  num =num + 1;
//  if (num >3){
//    num = 0;
////    Serial.print(result);
//    Serial.println();
////    result = "";
////    sensor = A0;e
////    sensor = sensor + num;
//    for(uint8_t i=0;i!=256;i++){
//      Serial.print(sensorValue[i]);
//      Serial.print(",");
//      Serial.println("");
//      Serial.flush();
      
  //    output.println(sensorValue[i]);
  //    output.flush();
//   }
//  }
//  else{
//    sensor = sensor + num;
//  }
  
  delay(1000);
  // Serial.println(getValue(4,4,true));

  Serial.print("--------");
  Serial.println();
//  Serial.flush();
//  Serial.println(getValue(0,0,true));

}
