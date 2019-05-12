int latchPin = 8;  //ST_CP
int clockPin = 12; // SH_CP
int dataPin = 11;  //DS
int reset = 2;
int ser = A0;

byte data1;
byte data2;
byte dataArray1[8];
byte dataArray2[8];

//int numOfRegisters = 4;
//byte* registerState;
//
//long effectId = 0;
//long prevEffect = 0;
//long effectRepeat = 0;
//long effectSpeed = 30;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  Serial.begin(9600);

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArray1[0] = 0xFF; //11111111
  dataArray1[1] = 0xFE; //11111110
  dataArray1[2] = 0xFC; //11111100
  dataArray1[3] = 0xF8; //11111000
  dataArray1[4] = 0xF0; //11110000
  dataArray1[5] = 0xE0; //11100000
  dataArray1[6] = 0xC0; //11000000
  dataArray1[7] = 0x80; //10000000


  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArray2[0] = 0xFF; //11111111
  dataArray2[1] = 0x7F; //01111111
  dataArray2[2] = 0x3F; //00111111
  dataArray2[3] = 0x1F; //00011111
  dataArray2[4] = 0x0F; //00001111
  dataArray2[5] = 0x07; //00000111
  dataArray2[6] = 0x03; //00000011
  dataArray2[7] = 0x01; //00000001

  

//
//  //set pins to output so you can control the shift register
//  pinMode(latchPin, OUTPUT);
//  pinMode(clockPin, OUTPUT);
//  pinMode(dataPin, OUTPUT);
  pinMode(reset, OUTPUT);
  digitalWrite(reset, HIGH);
  delay(1);
  digitalWrite(reset, LOW);
  delay(1);
  digitalWrite(reset, HIGH);
  delay(100);

}

void loop() {
   
   delay(1000);
   for (int j = 0; j < 8; j++) {
    for (int i =0; i <8; i++){
      
      
      }
    //load the light sequence you want from array
//    data1 = dataArray1[j];
//    data2 = dataArray2[j];
//    //ground latchPin and hold low for as long as you are transmitting
//    digitalWrite(latchPin, 0);
//    //move 'em out
//    shiftOut(dataPin, clockPin, data2);   
//    shiftOut(dataPin, clockPin, data1);
//    //return the latch pin high to signal chip that it 
//    //no longer needs to listen for information
//    digitalWrite(latchPin, 1);
//    Serial.println(analogRead(A0));
  }
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }
    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}
