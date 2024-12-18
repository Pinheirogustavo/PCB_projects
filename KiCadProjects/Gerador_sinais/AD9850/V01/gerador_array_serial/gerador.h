//#Autor: Gustavo Pinheiro


//freq inicial
int freq_sinal = 100;
// frequencias a serem testadas
int freq[37] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,  100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
int i=0;
//#include "ad9850.h"

int Rs; //valor do resistor variavel

//-----------------------------------------DigiPot1-------------------------------------//

// Saidas digitais
#define inc_outPin PB11 // INC(DigPot1)
#define ud_outPin PB10  // U/D(DigPot1)
#define cs_digpot1 PB1   // CS do DigPot 1, usado para salvar a ultima resistencia obtida

const int loopPeriod = 50;



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


void wiper_up(){ //wiper up
  digitalWrite(ud_outPin, HIGH);
  delay(loopPeriod);
  digitalWrite(inc_outPin, LOW);
  delay(loopPeriod);
  digitalWrite(inc_outPin, HIGH);
  delay(loopPeriod);
}

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


void ganho_minimo(){
    while (Rs<100){
        Serial.println("Configurando ganho minimo...");
        diminui_ganho();
        Rs=Rs+1;
    } 
    Serial.println("ganho minimo atingido");  
}

void ganho_maximo(){
    while (Rs>0){
        Serial.println("Configurando ganho maximo...");
        aumenta_ganho();
        Rs=Rs-1;
    } 
    Serial.println("ganho maximo atingido");  
}



void inicia_digpot(){
  for (int i = 0; i < 99; i++) {
        diminui_ganho();
  }
  Serial.println("ganho minimo atingido");  
  Rs = 100;
}

void printa_dados(){
    Serial.print("valor de Rs: ");
    Serial.println(Rs);
    Serial.print("Frequencia atual: ");
    Serial.println(freq_sinal);  
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
