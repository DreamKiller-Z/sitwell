/* FSR simple testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
 
int fsrPin0 = A0;     // the FSR and 10K pulldown are connected to a0
int fsrPin1 = A1;
int p1;     // the analog reading from the FSR resistor divider
int p2;
int timer = 0;
int sittingtime1 = 0;
int sittingtime2 = 0;
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  
}
 
void loop(void) {
  timer++;
  
  p1 = analogRead(fsrPin0);  
  p2 = analogRead(fsrPin1);
  Serial.print("timer:");
  Serial.println(timer);

  //timer
  if (timer == 10){
    Serial.print("P1 sitting time: ");
    Serial.println(sittingtime1);
    Serial.print("P2 sitting time: ");
    Serial.println(sittingtime2);
    Serial.end();
  }
  //p1 data
  Serial.print("P1 pressure = ");
  Serial.println(p1);     // the raw analog reading
  if (p1 > 500){
    sittingtime1 ++;
    Serial.print("P1 sitting time: ");
    Serial.println(sittingtime1);
    }
  //p2 data
  Serial.print("P2 pressure = ");
  Serial.println(p2);     // the raw analog reading
  if (p2 > 500){
    sittingtime2 ++;
    Serial.print("P2 sitting time: ");
    Serial.println(sittingtime2);
    }
  Serial.println("--------------------------");
  delay(1000);
} 
