#include "SPI.h"
//#include "MegunoLink.h"

#define SRCLR 2
#define RCLK 8
//PrintWriter output;
//String result = "";
//int sensorValue[256];
//int sensor = A0;
//int num = 0;

int getValue(uint8_t pin, uint8_t x, uint8_t y, boolean mode){
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

//  pixel = x * 8 + y + pin * 64;
  return analogRead(pin);
//  Serial.flush();
//  result += ("[" + String(pin) + ", " + String(row) ", " + String(col) + "]") + String(sensorValue[x*8+y+num*64]) + ",";
//  }
}

void setup() {
  
  // put your setup code here, to run once:
//  Serial.begin(1000000);
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

}

void loop() {
  // put your main code here, to run repeatedly:
  
  boolean mode = true;
  int sensorValue[64] = {0};
  for (uint8_t pin = 0; pin != 4; pin ++) {
    String result = "";
    uint8_t row = 0;
    uint8_t col = 0;
    for(row = 0; row != 8; row ++){
      for(col = 0; col !=8 ; col ++){
        
        sensorValue[row*8+col]  = getValue(pin, row, col, mode);
//        result += String(getValue(pin, row, col, mode)) + ",";
//          Serial.print(getValue(pin,row,col,mode));
//          Serial.print(",");
//          Serial.flush();


//        result += ("[" + String(pin) + ", " + String(row) + ", " + String(col) + "]") + getValue(pin, row, col, mode) + ",";
      }
//      result += "\n";
    }
    for(uint8_t i=0;i!=64;i++){
        Serial.print(sensorValue[i]);
        Serial.print(",");
        Serial.flush();
      }
    
//    result.remove(result.length() - 1);
  
//    Serial.print("Pin: " + String(pin));
//    Serial.println();
//    Serial.print("row: " + String(row));
//    Serial.println();
//    Serial.print("col: " + String(col));
//    Serial.println();
//    Serial.print(result);
    
//    Serial.println();
  }
  
//  delay(2000);
  // Serial.println(getValue(4,4,true));

//  Serial.print("-");
//  Serial.println();
  Serial.print("\r\n");
//  Serial.println();
  
//  Serial.flush();
//  Serial.println(getValue(0,0,true));

}
