//Demux.h

int A = 0, B = 0, C = 0, D = 0, E = 0;
//Definicao GPIO


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


//Configuracao GPIO

void configura_pinos_mux(){ //funcao define os pinos e estados dos sinais de controle dos mux; desativa todos
  // Variaveis de seleção do Mux
  //IN current
  pinMode(A_S0, OUTPUT);
  pinMode(A_S1, OUTPUT);
  pinMode(A_S2, OUTPUT);
  pinMode(A_S3, OUTPUT);
  pinMode(A_S4, OUTPUT);
  //OUT current
  pinMode(B_S0, OUTPUT);
  pinMode(B_S1, OUTPUT);
  pinMode(B_S2, OUTPUT);
  pinMode(B_S3, OUTPUT);
  pinMode(B_S4, OUTPUT);

  //  Variaveis de Habilitação do MUX IN (Nivel logico baixo)
  pinMode(Enable_A1, OUTPUT); //  MUX 1 "Eletrodo 0 a 7"
  pinMode(Enable_A2, OUTPUT); //  MUX 2 "Eletrodo 8 a 15"
  pinMode(Enable_A3, OUTPUT); //  MUX 3 "Eletrodo 16 a 23"
  pinMode(Enable_A4, OUTPUT); //  MUX 4 "Eletrodo 24 a 31"
  pinMode(Enable_A, OUTPUT);  //  MUX 5  primeiro da cascata

  digitalWrite(Enable_A1, HIGH);  // MUX 1 inicia desabilitado
  digitalWrite(Enable_A2, HIGH);  // MUX 2 inicia desabilitado
  digitalWrite(Enable_A3, HIGH);  // MUX 3 inicia desabilitado
  digitalWrite(Enable_A4, HIGH);  // MUX 4 inicia desabilitado
  digitalWrite(Enable_A, LOW);    // MUX 5 sempre habilitado

  //  Variaveis de Habilitação do MUX OUT (Nivel logico baixo)
  pinMode(Enable_B1, OUTPUT); //  MUX 1 "Eletrodo 0 a 7"
  pinMode(Enable_B2, OUTPUT); //  MUX 2 "Eletrodo 8 a 15"
  pinMode(Enable_B3, OUTPUT); //  MUX 3 "Eletrodo 16 a 23"
  pinMode(Enable_B4, OUTPUT); //  MUX 4 "Eletrodo 24 a 31"
  pinMode(Enable_B, OUTPUT);  //  MUX 5  primeiro da cascata

  digitalWrite(Enable_B1, HIGH);  // MUX 1 inicia desabilitado
  digitalWrite(Enable_B2, HIGH);  // MUX 2 inicia desabilitado
  digitalWrite(Enable_B3, HIGH);  // MUX 3 inicia desabilitado
  digitalWrite(Enable_B4, HIGH);  // MUX 4 inicia desabilitado
  digitalWrite(Enable_B, LOW);    //  MUX 5  primeiro da cascata
}

//Acionamento dos eletrodos

//// ACIONAR X ELETRODO IN
void seleciona_canal_in(int canal){
  //canais iniciam no num 0
  byte A = bitRead(canal,0); //LSB canal
  byte B = bitRead(canal,1);
  byte C = bitRead(canal,2);
  byte D = bitRead(canal,3);
  byte E = bitRead(canal,4); //MSB canal




  Serial.print("canal ");
  Serial.println(canal);
  Serial.print(A);
  Serial.print(B);
  Serial.print(C);
  Serial.print(D);
  Serial.println(E);
  //testa();


  digitalWrite(A_S0, A); // B5
  digitalWrite(A_S1, B); // B4
  digitalWrite(A_S2, C); // B3
  digitalWrite(A_S3, D); // A15
  digitalWrite(A_S4, E); // B9

  if (canal<8){ // liga apenas o mux A1
      digitalWrite(Enable_A1,0);
  } else if(canal<16){ //liga apenas o mux A2
      digitalWrite(Enable_A2,0);
  } else if(canal<24){ //liga apenas o mux A3
      digitalWrite(Enable_A3,0);
  } else if(canal<32){ //liga apenas o mux A4
      digitalWrite(Enable_A4,0);
  }
}

//// ACIONAR X ELETRODO OUT
void seleciona_canal_out(int canal){
  int A = bitRead(canal,0); //LSB canal
  int B = bitRead(canal,1);
  int C = bitRead(canal,2);
  int D = bitRead(canal,3);
  int E = bitRead(canal,4); //MSB canal

  
  Serial.print("canal ");
  Serial.println(canal);
  Serial.print(A);
  Serial.print(B);
  Serial.print(C);
  Serial.print(D);
  Serial.println(E);

  digitalWrite(B_S0, A);
  digitalWrite(B_S1, B);
  digitalWrite(B_S2, C);
  digitalWrite(B_S3, D);
  digitalWrite(B_S4, E);

  if (canal<8){ //liga apenas o mux B1
      digitalWrite(Enable_B1,0);
    } else if(canal<16){ //liga apenas o mux B2
      digitalWrite(Enable_B2,0);
    } else if(canal<24){ //liga apenas o mux B3
      digitalWrite(Enable_B3,0);
    } else if(canal<32){ //liga apenas o mux B4
      digitalWrite(Enable_B,0);
    }
}
