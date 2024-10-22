//Baseado em: https://github.com/Silvio8989/Equipamento-de-tomografia-por-impedancia-eletrica-escalavel-e-de-baixo-custo-para-uso-didatico/tree/main/C%C3%B3digos/Seguidor/Mux_Entrada/Mux_Entrada.ino

#include <Wire_slave.h>

#define MEU_ENDERECO 0x60


//Sinais de selecao dos mux que controlam a injecao de corrente
#define A_S0 PB5 //LSB
#define A_S1 PB4
#define A_S2 PB3
#define A_S3 PA15
#define A_S4 PB9 // MSB

//Sinais de selecao dos mux que controlam a drenagem de corrente
#define B_S0 PB15 //LSB
#define B_S1 PB14
#define B_S2 PB13
#define B_S3 PB12
#define B_S4 PB8 // MSB


//Sinais de enable dos mux que controlam a injecao de corrente
#define Enable_A  PA4
#define Enable_A1 PC15
#define Enable_A2 PA0
#define Enable_A3 PA1
#define Enable_A4 PA2

//Sinais de enable dos mux que controlam a drenagem de corrente
#define Enable_B  PA8
#define Enable_B1 PB0
#define Enable_B2 PB1
#define Enable_B3 PB10
#define Enable_B4 PB11

#define LED PC13

byte comando = 0;

long int contador = 0;

void liga_canal(int canal){
  switch (canal) {
    case 0:
      //Todos os eletrodos desligados
      digitalWrite(MUX1, HIGH);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, HIGH);
  
      digitalWrite(S0, LOW);   
      digitalWrite(S1, LOW);   
      digitalWrite(S2, LOW);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW);
      break;
    
    case 1: 
      //Eletrodo_01
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
  
      digitalWrite(S0, LOW);   
      digitalWrite(S1, LOW);   
      digitalWrite(S2, LOW);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW);
      break;
   
    case 2: 
      //Eletrodo_02
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
    
      digitalWrite(S0, HIGH);   
      digitalWrite(S1, LOW);   
      digitalWrite(S2, LOW);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW);
      break;
   
    case 3: 
      //Eletrodo_03
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
      
      digitalWrite(S0, LOW);   
      digitalWrite(S1, HIGH);   
      digitalWrite(S2, LOW);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW); 
      break;
    
    case 4:
      //Eletrodo_04
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
    
      digitalWrite(S0, HIGH);   
      digitalWrite(S1, HIGH);   
      digitalWrite(S2, LOW);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW); 
      break; 
      
    case 5: 
      //Eletrodo_05
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
      
      digitalWrite(S0, LOW);   
      digitalWrite(S1, LOW);   
      digitalWrite(S2, HIGH);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW);
      break; 

    case 6:
      //Eletrodo_06
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
    
      digitalWrite(S0, HIGH);   
      digitalWrite(S1, LOW);   
      digitalWrite(S2, HIGH);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW); 
      break;
    
    case 7:
      //Eletrodo_07  
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
    
      digitalWrite(S0, LOW);   
      digitalWrite(S1, HIGH);   
      digitalWrite(S2, HIGH);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW); 
      break;
    
    case 8:
      //Eletrodo_08
      digitalWrite(MUX1, LOW);   
      digitalWrite(MUX2, HIGH);   
      digitalWrite(MUX3, HIGH);   
      digitalWrite(MUX4, HIGH);   
      digitalWrite(MUX5, LOW);
     
      digitalWrite(S0, HIGH);   
      digitalWrite(S1, HIGH);   
      digitalWrite(S2, HIGH);   
      digitalWrite(S3, LOW);   
      digitalWrite(S4, LOW); 
      break; 
    
    default:
      break;
   }
}

void configura_pinos_mux(){
  // Variaveis de seleção do Mux
  pinMode(S0, OUTPUT); 
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT); 
  
  //  Variaveis de Habilitação do MUX (Nivel logico baixo)
  pinMode(MUX1, OUTPUT); // MUX 1 "Eletrodo 1 a 8"
  pinMode(MUX2, OUTPUT); // MUX 2 "Eletrodo 9 a 16"
  pinMode(MUX3, OUTPUT); //MUX 3 'Eletrodo 17 a 24"
  pinMode(MUX4, OUTPUT); // MUX 4 "Eletrodo 25 a 32"
  pinMode(MUX5, OUTPUT); // MUX 5 " Seleção do MUX
}

void dadorecebido(int howmany){
  comando = Wire.read();  
  if(comando == 0) comando = 0xFF;
}

void processacomando(){
  contador = 0;
  if(comando < 0xFF) liga_canal(comando);
  else liga_canal(0);
  comando = 0;
}

void setup() {
  Wire.begin(MEU_ENDERECO); //Endereço do MUX
  Wire.onReceive(dadorecebido);    // register event
  pinMode(LED, OUTPUT);
  configura_pinos_mux();
  liga_canal(0);
}

void loop() {
  contador = contador+1;
  if(comando!=0) processacomando();
  if(contador>10000) digitalWrite(LED, HIGH); // Verificação de funcionamento
  else digitalWrite(LED, LOW); // Verificação de funcionamento
}
