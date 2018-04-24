#include "OneButton.h"
#define R1 4
#define R2 5
#define R3 6
#define GND 9
#define OpUp 10
#define OpDown 11

OneButton OpEncoder(12,true);
OneButton button1(7,true);
OneButton button2(8,true);
String val="";
void setup() {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  digitalWrite(R3, HIGH);
  pinMode(OpUp,INPUT_PULLUP);
  pinMode(OpDown,INPUT_PULLUP);
  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);
  digitalWrite(R3, HIGH);
    Serial.begin(38400);
  //Serial.println("Test!");
  button1.attachClick(change_direction);
  button2.attachClick(Start_move);
  
  OpEncoder.attachClick(All_Distance);
  }
boolean j=0;
boolean i=0;
int k;
boolean GetUp;
boolean GetDown;
void loop() {
  
 button1.tick();
 button2.tick();
 GetUp=digitalRead(OpUp);
 GetDown=digitalRead(OpDown);
 OpEncoder.tick();
 
 while(Serial.available()){
  char c= Serial.read();
  val+=c;
  delay(3);
 }
 if (val!=""){
  Serial.println(val);
 }
 if(val=="Run"){
  Start_move();
 }
 if(val=="Switch"){
  change_direction();
 }
 val="";
}
  
void change_direction(){
if (j==0)
j=1;
else
j=0;
switch(j){
case 0:
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);      
    break;
case 1:
    digitalWrite(R1,HIGH);
    digitalWrite(R2,HIGH);
    break;
        }
}
    
void Start_move(){
if (i==0)
i=1;
else
i=0;
switch (i){
case 0:
    digitalWrite(R3,HIGH);
    break;
case 1:
    digitalWrite(R3,LOW);
    break;
    }
}



void Down_Distance(){
  Serial.println("Down_Distance");
}

void All_Distance(){
   k++;
  Serial.println(k);
}

