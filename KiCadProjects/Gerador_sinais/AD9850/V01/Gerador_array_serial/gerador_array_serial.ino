//#Autor: Gustavo Pinheiro
#include "ad9850.h"
//#include<Wire.h>    

//freq inicial
int freq_sinal = 100; 
// frequencias a serem testadas
int freq[37] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,  100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
int i = 0;


//-----------------------------------------DigiPot-------------------------------------//
//const int up_buttonPin = 8;     //Pin D8 of Arduino - up_botton - Entrada
//const int down_buttonPin =  7;  //Pin D7 of Arduino - down_botton - Entrada
//int up_buttonState = 0;	//estado inicial up_botton
//int down_buttonState = 0;	//estado inicial down_botton

//const int inc_outPin =  10;     //Pin D10 of Arduino - inc_signal - Saida
//const int ud_outPin =  9;       //Pin D9 of Arduino  - ud_signal - Saida

#define inc_outPin PB11
#define ud_outPin PB10

const int loopPeriod = 50;  
//-----------------------------------------DigiPot-------------------------------------//

int loop_cnt = 0;

char comando;



void setup() {
  Serial.begin(115200);

  ad9850_setup(); 
  ad9850_sendFrequency(freq_sinal);
  
//-----------------------------------------DigiPot-------------------------------------//
//pinMode(up_buttonPin, INPUT_PULLUP);  //Internal Pullup on Up button (No external resistor required)
//pinMode(down_buttonPin, INPUT_PULLUP);//Internal Pullup on Down button (No external resistor required)

pinMode(inc_outPin, OUTPUT);
pinMode(ud_outPin, OUTPUT);

digitalWrite(inc_outPin, HIGH);
digitalWrite(ud_outPin, HIGH);
//-----------------------------------------DigiPot-------------------------------------//

}
  
void loop() {
   
//-----------------------------------------DigiPot-------------------------------------// 
   // loop_cnt = loop_cnt + 1;
//-----------------------------------------DigiPot-------------------------------------//


  if(Serial.available()){
    comando = Serial.read();

    switch (comando) {

      case '+':
        if (freq_sinal < 1000000){
          freq_sinal = freq[i+1];
          i = i+1;
          ad9850_sendFrequency(freq_sinal);
        }
        break;     

      case '-':
        if (freq_sinal > 100){
          freq_sinal = freq[i-1];
          i = i-1;
          ad9850_sendFrequency(freq_sinal);
        }
        break; 
        
        
//-----------------------------------------DigiPot-------------------------------------//
      case 'u':
        digitalWrite(ud_outPin, HIGH);
        delay(loopPeriod);
        digitalWrite(inc_outPin, LOW);
        delay(loopPeriod);
        digitalWrite(inc_outPin, HIGH);
        delay(loopPeriod);
        break;     
        
      case 'd':
        digitalWrite(ud_outPin, LOW);
        delay(loopPeriod);
        digitalWrite(inc_outPin, LOW);
        delay(loopPeriod);
        digitalWrite(inc_outPin, HIGH);
        delay(loopPeriod);
        break;     
//-----------------------------------------DigiPot-------------------------------------//

        default:
          break;
          
        }
  }        
}
