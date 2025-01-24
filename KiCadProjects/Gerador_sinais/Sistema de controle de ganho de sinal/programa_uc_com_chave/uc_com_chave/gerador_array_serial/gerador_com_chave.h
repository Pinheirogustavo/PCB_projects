//#Autor: Gustavo Pinheiro


//freq inicial
int freq_sinal = 0;
int ganho=0;
// frequencias a serem testadas
int freq[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,  100000, 200000, 250000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};

int f=0; // contador para frequencia
int g=0; //contador para ganho
//#include "ad9850.h"

int passos[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};


int Vin = 1.1; //tensao PcPc do gerador ad9850


//#define debug

//-----------------------------------------pre-definicoes -------------------------------------//
const int loopPeriod = 20;
//-----------------------------------------Chave 1 -------------------------------------//
// Saidas digitais
#define c1_r1  PB12 //sinal de controle interruptor C1
#define c2_r2  PB15 //sinal de controle interruptor C2
#define c3_r3  PB14//sinal de controle interruptor C3
#define c4_r4  PB13//sinal de controle interruptor C4
//-----------------------------------------Chave 2 -------------------------------------//


///////////////// FUNCOES /////////////////////

void incrementa_frequencia(){
    if (freq_sinal < 1000000){
        freq_sinal = freq[f+1];
        f = f+1;
        ad9850_sendFrequency(freq_sinal);
        delay(loopPeriod);
        Serial.print("Incremento do sinal\t");
        Serial.print("frequencia: ");
        Serial.println(freq_sinal);
    } else Serial.println("frequencia maxima atingida");    
}

void decrementa_frequencia(){
    if (freq_sinal >= 100){
        freq_sinal = freq[f-1];
        f = f-1;
        ad9850_sendFrequency(freq_sinal);
        delay(loopPeriod);
        Serial.print("Decremento do sinal\t");
        Serial.print("frequencia: ");
        Serial.println(freq_sinal);
    }
    else Serial.println("frequencia minima atingida");
}

void pega_bits(int ganho){
  int A = bitRead(ganho,0); //LSB canal
  int B = bitRead(ganho,1);
  int C = bitRead(ganho,2);
  int D = bitRead(ganho,3); //MSB canal

  Serial.print("ganho ");
  Serial.println(ganho);
  Serial.print(D);
  Serial.print(C);
  Serial.print(B);
  Serial.println(A);

  digitalWrite(c1_r1, A);
  digitalWrite(c2_r2, B);
  digitalWrite(c3_r3, C);
  digitalWrite(c4_r4, D);
}

void diminui_ganho(){ // decrementa o vetor de ganho 'passos'
    if (ganho>0){
        ganho = passos[g-1];
        g = g-1;
        delay(loopPeriod);
        pega_bits(ganho);
        delay(loopPeriod);
        Serial.print("Decremento da amplitude do sinal\t");
        Serial.print("passo do ganho: ");
        Serial.println(ganho);
    } else Serial.println("ganho minimo atingido");
}

void aumenta_ganho(){// incrementa o vetor de ganho 'passos'
    if (ganho<15){
        ganho = passos[g+1];
        g = g+1;
        delay(loopPeriod);
        pega_bits(ganho);
        delay(loopPeriod);
        Serial.print("Incremento da amplitude do sinal\t ");
        Serial.print("passo do ganho: ");
        Serial.println(ganho);
    }else Serial.println("ganho maximo atingido");

}




void printa_dados(){
    Serial.print("valor do passo do ganho:: ");
    Serial.println(ganho);
    Serial.print("Frequencia atual: ");
    Serial.println(freq_sinal); 
    //Serial.print("Ganho atual: ");
    //Serial.println(Rf/Rs);
    //Serial.print("Tensao de saida ideal: ");
    //Serial.print(Vin*(Rf/Rs));
    //Serial.println(" Vpp");
}


    

void ganho_minimo(){
    while (ganho>0){
        Serial.println("Configurando ganho minimo...");
        diminui_ganho();
    } 
    Serial.println("ganho minimo atingido");  
}

void ganho_maximo(){
    while (ganho<15){
        Serial.println("Configurando ganho maximo...");
        aumenta_ganho();
    } 
    Serial.println("ganho maximo atingido");  
}



void gerador_setup() {
    Serial.begin(9600);

    pinMode(c1_r1, OUTPUT);
    pinMode(c2_r2, OUTPUT);
    pinMode(c3_r3, OUTPUT);
    pinMode(c4_r4, OUTPUT);

    digitalWrite(c1_r1, LOW);
    digitalWrite(c2_r2, LOW);
    digitalWrite(c3_r3, LOW);
    digitalWrite(c4_r4, LOW);

}
