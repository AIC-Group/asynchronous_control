#include "OneButton.h"
#define R1 4
#define R2 5
#define R3 6
#define GND 9
 boolean i;
 boolean j;
 boolean k;
 boolean m;
void setup() {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);
    Serial.begin(9600);
  Serial.println("Test!");
 
  }

void loop() {
  
  boolean Change=!digitalRead(7);
  boolean Start=!digitalRead(8);
  //Serial.println(Change);
  change_rotation(Change);
  startMove(Start);
  
  
  
  }
void change_rotation(boolean button){
  if (button!=i) {
    
   if (button==1){
    if (k==1){
    k=0;
    }
    else{
    k=1;
    }
    digitalWrite(R1,k);
    digitalWrite(R2,k);      
    }
   }
 
  i=button;
 delay(50);
  
}
void startMove(boolean button2){
  if (button2!=j) {
    
   if (button2==1){
    if (m==1)
    m=0;
    else
    m=1;
    
    digitalWrite(R3,m);
    
   
    
    }
   }
 
  j=button2;
  delay(50);
 
}

  }
}
  

