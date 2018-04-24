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
boolean up=0;
boolean Stop=0;
int Quant;
boolean GetUp;
boolean GetDown;
boolean down=1;
boolean set_go=0; 
boolean down_set=0;
void loop() {
 
 button1.tick();                      //опрос кнопки смены направления
 button2.tick();                      //опрос кнопки стар/стоп
 GetUp=digitalRead(OpUp);             //читаем верхнюю оптопару
 GetDown=digitalRead(OpDown);         //читаем нижнюю оптопару
 OpEncoder.tick();                    //опрос енкодера
 
 if (GetUp==false)                    //условие если верхняя кнопка разомкнута 
 {
  digitalWrite(R1, HIGH);             //выставляем направление на вверх
  digitalWrite(R2, HIGH);
  digitalWrite(R3, LOW);              //идем вверх
 }
 else
 {
  digitalWrite(R1, LOW);              //выставляем направление на вниз
  digitalWrite(R2, LOW);
  digitalWrite(R3, HIGH);             //стоп движение
 }
 
 while (Auto_bit==1)                  //цикл по условию автоматического режима отбора проб
 {
   GetUp=digitalRead(OpUp);             //читаем верхнюю оптопару
   GetDown=digitalRead(OpDown);         //читаем нижнюю оптопару
   OpEncoder.tick();                    //опрос енкодера
   if(Stop==1)
   {
    Start_move();
   }
   if(L==300&&down_set==true){
    Start_move();
    change_direction();
    Start_move();
    down_set=false;
   }
   if(GetUp==1)
   {
    Auto_bit=0;
   }
 }
 
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
 if(val=="Auto"){
  Auto_Run();
 }
 val="";
}


void change_direction(){
if (up==0)
up=1; //up
else
up=0; //down
switch(up){
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
if (Stop==0)
Stop=1;
else
Stop=0;
switch (Stop){
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
   if(up==false)
   Quant++;
   else
   Quant--;
   
   if(GetDown==0)
   {
    if(up==0 && L<300)
    {
      L++; 
    }
    else
    {
      L--;
    }
   }
  Serial.println(Quant);
}

