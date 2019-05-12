
int fsrPin0 = A0;     // the FSR and 10K pulldown are connected to a0
int fsrPin1 = A1;
int p1;     // the analog reading from the FSR resistor divider
int p2;
int sec = 0;
int minute = 0;
int hour = 0;

int sit_temp_sec1 = 0;
int sit_temp_minute1 = 0;
int sit_temp_hour1 = 0;

int sit_temp_sec2 = 0;
int sit_temp_minute2 = 0;
int sit_temp_hour3 = 0;

int sit_temp_sec2 = 0;
int sit_temp_minute2 = 0;
int sit_temp_hour2 = 0;

int standup_sec1 = 0;
int standup_minute1 = 0;
int standup_hour1 = 0;

int standup_sec2 =0;
int standup_minute2 = 0;
int standup_hour2 = 0;

int sit_total1 = 0;
int sit_total2 = 0;
String sum_standup1;
String sum_standup2;
String sum_sit_total1;
String sum_sit_total2;
String sitting1;
String sitting2;
String timer;
String sum_sit_temp1;
String sum_sit_temp2;
String current1;
String current2;
String prev1;
String prev2;
void setup(void) {
  Serial.begin(9600);  
}
 
void loop(void) {
  sec++;
  if (sec == 60){
    minute ++;
    sec = 0;
    }
  if (minute==60){
    hour ++;
    minute = 0;
    }
  timer = String(hour)+":"+String(minute)+":"+String(sec);
  p1 = analogRead(fsrPin0);  
  p2 = analogRead(fsrPin1);

  //p1 data
  //P1 has pressure
  if (p1 >= 100){
    if (sit_temp_sec1 >2){
      current1 = "sit";
      standup_sec1 = 0;
      sit_total_sec1 ++;
      if (sit_temp_sec1 == 60){
        sit_temp_minute1 ++;
        sit_temp_sec1 = 0;
        }
      if (sit_temp_minute1 == 60){
        sit_temp_hour1 ++;
        sit_temp_minute1 = 0;
        }
      sum_sit_temp1 = String(sit_temp_hour1)+":"+String(sit_temp_minute1)+":"+String(sit_temp_sec1);
      }   
    sit_temp_sec1 ++;
  }
  //P1 no pressure
  else if (p1 < 100){
    if(standup_sec1 > 2){
      current1 = "stand";
      if (standup_sec1 == 60){
        standup_minute1 ++;
        standup_sec1 = 0;
        }
      if (standup_minute1==60){
        standup_hour1 ++;
        standup_minute1 = 0;
        }
      sum_standup1 = String(standup_hour1) + ":" + String(standup_minute1) + ":"+String(standup_sec1);
      sit_temp_sec1 = 0; 
      }
//    Serial.print(standup2);
    standup_sec1 ++;  
    }
  //p1 sits down
  if (current1 == "sit" && prev1 =="stand"){
    Serial.print("timer:");
    Serial.println(timer);
    Serial.print("P1 just stood up for: ");
    Serial.println(sum_standup1);
    Serial.println("--------------------------");
    }
  //p1 stands up
  else if (current1 == "stand" && prev1 == "sit"){
    Serial.print("timer:");
    Serial.println(timer);
    Serial.print("P1 just sit down for: ");
    Serial.println(sum_sit_temp1);
    Serial.print("P1 total sitting time: ");
//    sum_sit_total1 = String(sit_total1 /3600) + ":" + String(sit_total1 / 60) + ":"+String(sit_total1 % 60);
    Serial.println(sum_sit_total1);
    Serial.println("--------------------------");
    }
  
  //p2 data
  //p2 has pressure
  if (p2 >= 100){
    if (sit_temp2 > 2){
      current2 = "sit";
      standup2 = 0;
      sit_total2 ++;
      sum_sit_temp2 = String(sit_temp2 /3600) + ":" + String(sit_temp2 / 60) + ":"+String(sit_temp2 % 60);
      }                                                                                                                                               
    sit_temp2 ++;  
  }
  //p2 no pressure
  else if (p2 < 100){
    if(standup2 > 2){
       current2 = "stand";
       sit_temp2 = 0;
       sum_standup2 = String(standup2/3600) + ":" + String(standup2 / 60) + ":"+String(standup2 % 60);
      }
//    Serial.print(standup2);
    standup2 ++;
    }
  //p2 sits down
  if (current2 == "sit" && prev2 =="stand"){
    Serial.print("timer:");
    Serial.println(timer);
    Serial.print("P2 just stood up for: ");
    Serial.println(sum_standup2);
    Serial.println("--------------------------");
    }
  //p2 stands up
  else if (current2 == "stand" && prev2 == "sit"){
    Serial.print("timer:");
    Serial.println(timer);
    Serial.print("P2 just sit down for: ");
    Serial.println(sum_sit_temp2);
    Serial.print("P2 total sitting time: ");
    sum_sit_total2 = String(sit_total2 /3600) + ":" + String(sit_total2 / 60) + ":"+String(sit_total2 % 60);
    Serial.println(sum_sit_total2);
    Serial.println("--------------------------");
    }
  //record previous state
  prev1 = current1;
  prev2 = current2;
  delay(1000);
} 
