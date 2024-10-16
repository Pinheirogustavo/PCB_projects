//#Autor: Gustavo Pinheiro
#include "ad9850.h"
//#include<Wire.h>
#include "RotaryEncoder.h"         //https://github.com/mathertel/RotaryEncoder?tab=readme-ov-file    

//freq inicial
int freq_sinal = 100; 
// frequencias a serem testadas
int freq[37] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,  100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
int i = 0;


//-----------------------------------------DigiPot-------------------------------------//
//const int up_buttonPin = 8;     //Pin D8 of Arduino - up_botton - Entrada
//const int down_buttonPin =  7;  //Pin D7 of Arduino - down_botton - Entrada
//const int inc_outPin =  10;     //Pin D10 of Arduino - inc_signal - Saida
//const int ud_outPin =  9;       //Pin D9 of Arduino  - ud_signal - Saida

#define inc_outPin PB11 // INC(DigPot1)
#define ud_outPin PB10  // U/D(DigPot1)
#define cs_digpot1 PB1   // CS do DigPot 1, usado para salvar a ultima resistencia obtida

const int loopPeriod = 50;  
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
pinMode(cs_digpot1, OUTPUT);

digitalWrite(inc_outPin, HIGH);
digitalWrite(ud_outPin, HIGH);
digitalWrite(cs_digpot1, LOW);

//-----------------------------------------DigiPot1-------------------------------------//

// Saidas digitais
#define inc_outPin PB11 // INC(DigPot1)
#define ud_outPin PB10  // U/D(DigPot1)
#define cs_digpot1 PB1   // CS do DigPot 1, usado para salvar a ultima resistencia obtida

const int loopPeriod = 50;  
char comando;

void setup() {
  Serial.begin(115200);

  ad9850_setup(); 
  ad9850_sendFrequency(freq_sinal);
  
pinMode(inc_outPin, OUTPUT);
pinMode(ud_outPin, OUTPUT);
pinMode(cs_digpot1, OUTPUT);

digitalWrite(inc_outPin, HIGH);
digitalWrite(ud_outPin, HIGH);
digitalWrite(cs_digpot1, LOW);

}
  
void loop() {

  if(Serial.available()){
    comando = Serial.read();

    switch (comando) {

      case '+': // incrementa o vetor de frequencias
        if (freq_sinal < 1000000){
          freq_sinal = freq[i+1];
          i = i+1;
          ad9850_sendFrequency(freq_sinal);
        }
        break;     

      case '-': // decrementa o vetor de frequencias
        if (freq_sinal > 100){
          freq_sinal = freq[i-1];
          i = i-1;
          ad9850_sendFrequency(freq_sinal);
        }
        break; 
        
        
      case 'd': // diminui a amplitude do sinal (wiper up)
        digitalWrite(ud_outPin, HIGH);
        delay(loopPeriod);
        digitalWrite(inc_outPin, LOW);
        delay(loopPeriod);
        digitalWrite(inc_outPin, HIGH);
        delay(loopPeriod);
        break;     
        
      case 'u': // aumenta a amplitude do sinal (wiper down)
        digitalWrite(ud_outPin, LOW);
        delay(loopPeriod);
        digitalWrite(inc_outPin, LOW);
        delay(loopPeriod);
        digitalWrite(inc_outPin, HIGH);
        delay(loopPeriod);
        digitalWrite(ud_outPin, HIGH);
        break;  

      case 's': // Salva a resistencia
        digitalWrite(cs_digpot1, HIGH);
        delay(loopPeriod);
        digitalWrite(cs_digpot1, LOW);
        break;  

    default:
        break;
          
    }
  }        
}
