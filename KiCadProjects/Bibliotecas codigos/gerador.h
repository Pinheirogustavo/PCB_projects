//#Autor: Gustavo Pinheiro


//freq inicial
int freq_sinal = 100;
// frequencias a serem testadas
int freq[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,  100000, 200000, 250000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
int i=0;
//#include "ad9850.h"

float Rs; //valor do resistor variavel
float Rf = 51; //valor do resistor de feedback (kOHM)
int Vin = 1.1; //tensao PcPc do gerador ad9850


//#define debug



//-----------------------------------------DigiPot1-------------------------------------//

// Saidas digitais
#define inc_outPin PB11 // INC(DigPot1)
#define ud_outPin PB10  // U/D(DigPot1)
#define cs_digpot1 PB1   // CS do DigPot 1, usado para salvar a ultima resistencia obtida

const int loopPeriod = 20;



//-----------------------------------------DigiPot2-------------------------------------//


//-----------------------------------------Encoder-------------------------------------//


//-----------------------------------------Teclado matricial-------------------------------------//


///////////////// FUNCOES /////////////////////

void incrementa_frequencia(){
    if (freq_sinal < 1000000){
        freq_sinal = freq[i+1];
        i = i+1;
        ad9850_sendFrequency(freq_sinal);
        delay(loopPeriod);
        Serial.print("Incremento do sinal\t");
        Serial.print("frequencia: ");
        Serial.println(freq_sinal);
    } else Serial.println("frequencia maxima atingida");    
}

void decrementa_frequencia(){
    if (freq_sinal >= 100){
        freq_sinal = freq[i-1];
        i = i-1;
        ad9850_sendFrequency(freq_sinal);
        delay(loopPeriod);
        Serial.print("Decremento do sinal\t");
        Serial.print("frequencia: ");
        Serial.println(freq_sinal);
    }
    else Serial.println("frequencia minima atingida");
}

void wiper_down(){ //wiper down
  digitalWrite(ud_outPin, LOW);
  delay(loopPeriod);
  digitalWrite(inc_outPin, LOW);
  delay(loopPeriod);
  digitalWrite(inc_outPin, HIGH);
  delay(loopPeriod);
  digitalWrite(ud_outPin, HIGH);  
}

void wiper_up(){ //wiper up
  digitalWrite(ud_outPin, HIGH);
  delay(loopPeriod);
  digitalWrite(inc_outPin, LOW);
  delay(loopPeriod);
  digitalWrite(inc_outPin, HIGH);
  delay(loopPeriod);
}

void printa_dados(){
    Serial.print("valor de Rs: ");
    Serial.println(Rs);
    Serial.print("Frequencia atual: ");
    Serial.println(freq_sinal); 
    Serial.print("Ganho atual: ");
    Serial.println(Rf/Rs);
    Serial.print("Tensao de saida ideal: ");
    Serial.print(Vin*(Rf/Rs)); 
    Serial.println(" Vpp");   
}

#if defined debug  

  void aumenta_ganho(){//wiper down
      if (Rs>9){
          decrementa_frequencia(); //debug
          delay(loopPeriod);       //debug
          wiper_down();
          delay(loopPeriod);
          incrementa_frequencia(); //debug
          Rs = Rs-1;
          Serial.print("Incremento da amplitude do sinal\t ");
          Serial.print("valor do digpot Rs(kOhm): ");
          Serial.println(Rs);
      }else Serial.println("ganho maximo atingido");
  
  }

    void diminui_ganho(){ //wiper up
        if (Rs<18){
            decrementa_frequencia();  //debug
            delay(loopPeriod);        //debug
            wiper_up();
            delay(loopPeriod);
            incrementa_frequencia();  //debug
            delay(loopPeriod);        //debug
            Rs = Rs+1;
            Serial.print("Decremento da amplitude do sinal\t");
            Serial.print("valor do digpot Rs(kOhm): ");
            Serial.println(Rs);
        } else Serial.println("ganho minimo atingido");    
    }

  void inicia_digpot(){
    for (int i = 0; i < 99; i++) {
          diminui_ganho();
    }
      for (int i = 0; i < 99; i++) { //debug
          aumenta_ganho();
    }
    for (int i = 0; i < 8; i++) {     //debug
          diminui_ganho();
    }

      Serial.println("digpot ");  
  }
       //
#else
    
    void diminui_ganho(){ //wiper up
        if (Rs<100){
            wiper_up();
            delay(loopPeriod);
            Rs = Rs+1;
            Serial.print("Decremento da amplitude do sinal\t");
            Serial.print("valor do digpot Rs(kOhm): ");
            Serial.println(Rs);
        } else Serial.println("ganho minimo atingido");    
    }
    
    void aumenta_ganho(){//wiper down
        if (Rs>0){
            wiper_down();
            delay(loopPeriod);
            Rs = Rs-1;
            Serial.print("Incremento da amplitude do sinal\t ");
            Serial.print("valor do digpot Rs(kOhm): ");
            Serial.println(Rs);
        }else Serial.println("ganho maximo atingido");
    
    }

    void inicia_digpot(){
      for (int i = 0; i < 99; i++) {
            aumenta_ganho();
      }
      Serial.println("ganho minimo atingido");  
    }
       //
#endif


void ganho_minimo(){
    while (Rs<100){
        Serial.println("Configurando ganho minimo...");
        diminui_ganho();
    } 
    Serial.println("ganho minimo atingido");  
}

void ganho_maximo(){
    while (Rs>0){
        Serial.println("Configurando ganho maximo...");
        aumenta_ganho();
    } 
    Serial.println("ganho maximo atingido");  
}



void gerador_setup() {
    Serial.begin(9600);

    pinMode(inc_outPin, OUTPUT);
    pinMode(ud_outPin, OUTPUT);
    pinMode(cs_digpot1, OUTPUT);

    digitalWrite(inc_outPin, HIGH);
    digitalWrite(ud_outPin, HIGH);
    digitalWrite(cs_digpot1, LOW);
    
    inicia_digpot();
}
