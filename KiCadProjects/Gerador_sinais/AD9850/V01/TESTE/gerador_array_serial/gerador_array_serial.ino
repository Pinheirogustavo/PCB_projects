//#Autor: Gustavo Pinheiro
/*Programa para controle do projeto "Gerador de sinais AD9850 V01" por meio da porta serial da placa stm
 * As frequencias possiveis sao aquelas presentes no vetor freq
 * O incremento e decremento do vetor de frequencias eh realizado por meio dos caracteres "+" e "-"
 * O aumento da amplitude do sinal eh feito pelo caracter "u"
 * A diminuicao da amplitude do sinal eh feita pelo caracter "d" 
 */
#include "ad9850.h"
#include "gerador.h"

//#include "Arduino.h"
#include "X9C10X.h"

X9C10X pot(100000);  //  100 KΩ  (ALT-234)

uint8_t direction = LOW;
uint8_t step = 1;


//const int loopPeriod = 50;  
char comando;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Aguarde a configuracao do sistema");


  ad9850_setup(); 
  ad9850_sendFrequency(freq_sinal);
  gerador_setup();
  delay(1000);


  pot.begin(inc_outPin, ud_outPin, cs_digpot1);  // pulse, direction, select
  pot.setPosition(0);


  Serial.println("Configuracao encerrada");

}
  
void loop() {

  if(Serial.available()){
    comando = Serial.read();

    switch (comando) {

      //case 'i':

      case '+': // incrementa o vetor de frequencias
        incrementa_frequencia();
        break;     

      case '-': // decrementa o vetor de frequencias
        decrementa_frequencia();
        break; 
        
        
      case 'd': // diminui a amplitude do sinal (wiper up)
        pot.decr();
        delay(100);
        break;
        
      case 'u': // aumenta a amplitude do sinal (wiper down)
        pot.incr();
        delay(100);
        break;
      
      case 's': // Salva a resistencia
        digitalWrite(cs_digpot1, HIGH);
        delay(loopPeriod);
        digitalWrite(cs_digpot1, LOW);
        break;  

      case 'x':
        ganho_minimo();
        break;

      case 'y':
        ganho_maximo();
        break;

      case 'p':
        printa_dados();
        Serial.println(pot.getPosition());
        break;

    default:
        break;
          
    }
  }        
}
