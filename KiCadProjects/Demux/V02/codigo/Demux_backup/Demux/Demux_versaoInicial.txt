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

/*
TRECHO QUE SUBISTITUI O switch/case (func liga_canal) PARA SELECIONAR OS CANAIS IN/OUT

//// ACIONAR X ELETRODO IN
void seleciona_canal_in(int canal){
  //canais iniciam no num 0
  int A = bitRead(canal,0); //LSB canal
  int B = bitRead(canal,1);
  int C = bitRead(canal,2);
  int D = bitRead(canal,3);
  int E = bitRead(canal,4); //MSB canal

  if (canal<8){ // liga apenas o mux A1
    digitalWrite(Enable_A1,0);
  } else if(canal<16){ //liga apenas o mux A2
    //digitalWrite(Enable_A1,0);
    digitalWrite(Enable_A2,0);
  } else if(canal<24){ //liga apenas o mux A3
    //digitalWrite(Enable_A1,0);
    //digitalWrite(Enable_A2,0);
    digitalWrite(Enable_A3,0);
  } else if(canal<32){ //liga apenas o mux A4
    //digitalWrite(Enable_A1,0);
    //digitalWrite(Enable_A2,0);
    //digitalWrite(Enable_A3,0);
    digitalWrite(Enable_A4,0);
  }

  digitalWrite(A_S0, A);
  digitalWrite(A_S1, B);
  digitalWrite(A_S2, C);
  digitalWrite(A_S3, D);
  digitalWrite(A_S4, E);
}

//// ACIONAR X ELETRODO OUT
void seleciona_canal_out(int canal){
  int A = bitRead(canal,0); //LSB canal
  int B = bitRead(canal,1);
  int C = bitRead(canal,2);
  int D = bitRead(canal,3);
  int E = bitRead(canal,4); //MSB canal

  if (canal<8){ //liga apenas o mux B1
      digitalWrite(Enable_B1,0);
    } else if(canal<16){ //liga apenas o mux B2
      //digitalWrite(Enable_A1,0);
      digitalWrite(Enable_B2,0);
    } else if(canal<24){ //liga apenas o mux B3
      //digitalWrite(Enable_A1,0);
      //digitalWrite(Enable_A2,0);
      digitalWrite(Enable_B3,0);
    } else if(canal<32){ //liga apenas o mux B4
      //digitalWrite(Enable_A1,0);
      //digitalWrite(Enable_A2,0);
      //digitalWrite(Enable_A3,0);
      digitalWrite(Enable_B,0);
    }


  digitalWrite(B_S0, A);
  digitalWrite(B_S1, B);
  digitalWrite(B_S2, C);
  digitalWrite(B_S3, D);
  digitalWrite(B_S4, E);
}

 */

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
  //IN
  pinMode(A_S0, OUTPUT); 
  pinMode(A_S1, OUTPUT);
  pinMode(A_S2, OUTPUT);
  pinMode(A_S3, OUTPUT);
  pinMode(A_S4, OUTPUT); 
  //OUT
  pinMode(B_S0, OUTPUT); 
  pinMode(B_S1, OUTPUT);
  pinMode(B_S2, OUTPUT);
  pinMode(B_S3, OUTPUT);
  pinMode(B_S4, OUTPUT);
  
  //  Variaveis de Habilitação do MUX IN (Nivel logico baixo)
  pinMode(Enable_A1, OUTPUT); // MUX 1 "Eletrodo 1 a 8"
  pinMode(Enable_A2, OUTPUT); // MUX 2 "Eletrodo 9 a 16"
  pinMode(Enable_A3, OUTPUT); //MUX 3 'Eletrodo 17 a 24"
  pinMode(Enable_A4, OUTPUT); // MUX 4 "Eletrodo 25 a 32"
  pinMode(Enable_A, OUTPUT); // MUX 5 " Seleção do MUX

  digitalWrite(Enable_A1, 1); // MUX 1 inicia desabilitado
  digitalWrite(Enable_A2, 1); // MUX 2 inicia desabilitado
  digitalWrite(Enable_A3, 1); // MUX 3 inicia desabilitado
  digitalWrite(Enable_A4, 1); // MUX 4 inicia desabilitado
  digitalWrite(Enable_A, 0); //  MUX 5 sempre habilitado

  //  Variaveis de Habilitação do MUX OUT (Nivel logico baixo)
  pinMode(Enable_B1, OUTPUT); // MUX 1 "Eletrodo 1 a 8"
  pinMode(Enable_B2, OUTPUT); // MUX 2 "Eletrodo 9 a 16"
  pinMode(Enable_B3, OUTPUT); //MUX 3 'Eletrodo 17 a 24"
  pinMode(Enable_B4, OUTPUT); // MUX 4 "Eletrodo 25 a 32"
  pinMode(Enable_B, OUTPUT); // MUX 5 " Seleção do MUX

  digitalWrite(Enable_B1, 1); // MUX 1 inicia desabilitado
  digitalWrite(Enable_B2, 1); // MUX 2 inicia desabilitado
  digitalWrite(Enable_B3, 1); // MUX 3 inicia desabilitado
  digitalWrite(Enable_B4, 1); // MUX 4 inicia desabilitado
  digitalWrite(Enable_B, 0); //  MUX 5 sempre habilitado
}

void dadorecebido(int howmany){
  comando = Wire.read();  
  if(comando == 0) comando = 0xFF;
  configura_pinos_mux(); //chama a funcao para desligar todos os mux entre cada comando
}

/*
 *substitui a func dadorecebido() para receber dois bytes do master, sendo o numero do canal in e o do canal out

 void dadorecebido(int howmany){
  //comando = Wire.read();
  int eletrodo_in = Wire.read();
  int eletrodo_out = Wire.read();
  //if(comando == 0) comando = 0xFF;
  if(eletrodo_in == 0) eletrodo_in = 0xFF;
  if(eletrodo_out == 0) eletrodo_out = 0xFF;
  configura_pinos_mux(); //chama a funcao para desligar todos os mux entre cada comando
}
 */

void processacomando(){
  contador = 0;
  if(comando < 0xFF) liga_canal(comando);
  else liga_canal(0);
  comando = 0;
}

/*
void processacomando(){
  contador = 0;
  if(eletrodo_in < 0xFF) seleciona_canal_in(eletrodo_in);
  else seleciona_canal_in(0);
  eletrodo_in = 0;
  if(eletrodo_out < 0xFF) seleciona_canal_out(eletrodo_out);
  else seleciona_canal_out(0);
  eletrodo_out = 0;
}
 */


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
  //if(eletrodo_in!=0) processacomando(); substituicao da variavel 'comando' pela variavel 'eletrodo_in'
  if(contador>10000) digitalWrite(LED, HIGH); // Verificação de funcionamento
  else digitalWrite(LED, LOW); // Verificação de funcionamento
}
