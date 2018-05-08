#include "OneButton.h"
#define R1 4                                  //
#define R2 5                                  //
#define R3 6                                  //
#define GND 9                                 //
#define OpUp 10                               //
#define OpDown 11                             //

OneButton OpEncoder(12,true);                 //
OneButton button1(7,true);                    //
OneButton button2(8,true);                    //
String val="";                                //

void setup() {
  pinMode(R1, OUTPUT);                        //
  pinMode(R2, OUTPUT);                        //
  pinMode(R3, OUTPUT);                        //
  digitalWrite(R3, HIGH);                     //
  pinMode(OpUp,INPUT_PULLUP);                 //
  pinMode(OpDown,INPUT_PULLUP);               //
  pinMode(GND, OUTPUT);                       //
  digitalWrite(GND, LOW);                     //
  digitalWrite(R3, HIGH);                     //
    Serial.begin(38400);                      //
  //Serial.println("Test!");
  button1.attachClick(change_direction);      //
  button2.attachClick(Start_move);            //
  button1.attachLongPressStart(Auto_move);
  OpEncoder.attachClick(All_Distance);        //
  }
/*------------глобальные переменные-----------*/  
boolean up=1,up_bit=0;                                 //
boolean Stop=0;                               //
int Quant,L,LongDistance,DownDistance;        //
boolean GetUp;                                //
boolean GetDown;                              //
boolean down=1;                               //
boolean set_go=0;                             //
boolean down_set=0;                           //
boolean Auto_bit=0;                           //
boolean FirstBoot=1;                          //
/*--------------------------------------------*/
void loop() { 
 
 button1.tick();                              //опрос кнопки смены направления
 button2.tick();                              //опрос кнопки стар/стоп
 
 GetUp=digitalRead(OpUp);                     //читаем верхнюю оптопару
 GetDown=digitalRead(OpDown);                 //читаем нижнюю оптопару
 OpEncoder.tick();                            //опрос енкодера
 if (FirstBoot==1)
 {
 while (GetUp==false)                            //условие если верхняя кнопка разомкнута 
 {
  
  digitalWrite(R1, LOW);                     //выставляем направление на вверх
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);                      //идем вверх
  GetUp=digitalRead(OpUp);
  
 }
 if (GetUp==true)
 {
  digitalWrite(R1, HIGH);                      //выставляем направление на вниз
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);                     //стоп движение
 }
 FirstBoot=0;
 }
/*цикл по условию автоматического режима отбора проб*/
 while (Auto_bit==1)                          //
 {
   
   while (GetDown==true)
   {
    GetDown=digitalRead(OpDown);              //читаем нижнюю оптопару
    digitalWrite(R3, LOW);                    //старт движение
    up_bit=0;
    OpEncoder.tick();                         //опрос енкодера
    DownDistance=Quant;
    Serial.println(DownDistance);
   }
   Quant=0;
   if(GetDown==false)
   {                                          //
    while(L<30)
    {
      GetDown=digitalRead(OpDown);              //читаем нижнюю оптопару
      digitalWrite(R3, LOW);                    //старт движение
      up_bit=0;
      OpEncoder.tick();                         //опрос енкодера
      L=Quant;
      Serial.println(L);
    }
    digitalWrite(R3, HIGH);                     //стоп движение
    LongDistance=DownDistance+L;
    Quant=LongDistance;
    Serial.println(Quant);
    while(GetUp==false)
    {
      GetUp=digitalRead(OpUp);                     //читаем верхнюю оптопару
      digitalWrite(R1, LOW);                     //выставляем направление на вверх
      digitalWrite(R2, LOW);
      digitalWrite(R3, LOW);                    //старт движение
      up_bit=1;
      OpEncoder.tick();
     
      Serial.println(Quant);
    }
    if(GetUp==true)
    {
      digitalWrite(R1, HIGH);                      //выставляем направление на вниз
      digitalWrite(R2, HIGH);
      digitalWrite(R3, HIGH);                    //старт движение
      L=0;
      LongDistance=0;
      DownDistance=0;
      Quant=0;
      Auto_bit=0;                                 //
      Serial.println(Quant);
    }
   }
  }
 /*------цикл опроса блютуз команд------*/
 while(Serial.available()){             //
  char c= Serial.read();                //
  val+=c;                               //
  delay(3);                             //
 }                              
 if (val!=""){                          //
  Serial.println(val);                  //
 }
 if(val=="Run"){                        //
  Start_move();                         //
 }
 if(val=="Switch"){                     //
  change_direction();                   //
 }
 if(val=="Auto"){                       //
  Auto_bit=1;                           //
 }
 val="";                                //
}
/*-------------------------------------*/

/*-----функция смены направления движения-----*/
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
/*----------------------------------------------*/

/*--------функция старт/стоп движения-----------*/   
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
/*----------------------------------------------*/

/*---------не сбывшиеся мечты  (-_-)--------------*/
void Auto_move(){
  Auto_bit=1;
}

void All_Distance(){
   if(up_bit==false)
   Quant++;
   else
   Quant--;
   
   
}

