#include "SPI.h"
//#include "MegunoLink.h"

#define SRCLR 2
#define RCLK 8
#define Sensor A0

//import processing.serial.*;
//import java.text.*;
//import java.util.*;

//import processing.serial.*;
//Serial mySerial;
//PrintWriter output;

//Message MyCSVMessage("Data");

int getValue(uint8_t x,uint8_t y,boolean mode){
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
  delayMicroseconds(1000);
  return analogRead(Sensor);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

  //csv file setup
//  output = createWriter("595data.csv");
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue[64];
  for(uint8_t i=0;i!=8;i++){
    for(uint8_t j=0;j!=8;j++){
      sensorValue[i*8+j] = getValue(i,j,true);
//      Serial.print(sensorValue[i*8+j]);
//      Serial.print(" ");
    }
//    Serial.println();
  }
   delay(100);
  // Serial.println(getValue(4,4,true));
//  MyCSVMessage.Begin();
  for(uint8_t i=0;i!=64;i++){
    Serial.print(sensorValue[i]);
    Serial.print(",");
//    output.println(sensorValue[i]);
//    output.flush();
  }
//  MyCSVMessage.End();
  Serial.println("");
  delay(100);
}
