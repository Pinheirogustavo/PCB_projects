#define DEBUG1 1 

// Definindo o ID configurado em cada um dos STM32 perifericos presentes no projeto

#define ID_DEMUX  6
#define ID_MULT   4
#define ID_AQ_U1  7
#define ID_AQ_U4  8
#define ID_AQ_U5  9
#define ID_AQ_U6  5
#define ID_AQ_CO  3


// Definindo os comandos que cada um dos eletrodos seja usado como eletrodo que aplica a corrente quando usada a fonte de corrente monopolar (ou aplica a corrente 1 na fonte bipolar)

#define I_E0 1
#define I_E1 2
#define I_E2 3
#define I_E3 4
#define I_E4 5
#define I_E5 6
#define I_E6 7
#define I_E7 8
#define I_E8 9
#define I_E9 10
#define I_E10 11
#define I_E11 12
#define I_E12 13
#define I_E13 14
#define I_E14 15
#define I_E15 16


// Definindo os comandos que cada um dos eletrodos seja usado como terra  quando usada a fonte de corrente monopolar (ou aplica a corrente 2, em contrafase na fonte bipolar)

#define O_E0 128
#define O_E1 129
#define O_E2 130
#define O_E3 131
#define O_E4 132
#define O_E5 133
#define O_E6 134
#define O_E7 135
#define O_E8 136
#define O_E9 137
#define O_E10 138
#define O_E11 139
#define O_E12 140
#define O_E13 141
#define O_E14 142
#define O_E15 143




// Definindo os comandos para alterar a frequência de cada um dos geradores

#define F1_1K 65
#define F1_2K 66 
#define F1_3K 67
#define F1_5K 68
#define F1_10K 69
#define F1_20K 70
#define F1_0 90

#define F2_10K 97
#define F2_20K 98
#define F2_30K 99
#define F2_50K 100
#define F2_100K 101
#define F2_150K 102
#define F2_200K 103
#define F2_0 122

#define NE_MAX 8

float medidas1[NE_MAX];
float medidas2[NE_MAX];

float corrente1 = 1.0;
float corrente2 = 1.0;
float Rg = 3300;
float ganhoINA = (1 + (50000/Rg));
float Rsentinela = 10;
float ganhocorrente = 1000.0/( ganhoINA*Rsentinela );



// Funcao que sabe o Id do eletrodo com base no ID do periferico e o canal adquirido do periferico

int localizaeletrodo(int ID, byte ch){
  int eletrodo = 99;
  if (ID == ID_AQ_U1){
    if (ch == 1){
      eletrodo = 1;
    }
    else if (ch==2){
      eletrodo = 5;
    }
  }
  else if (ID == ID_AQ_U4){
    if (ch == 1){
      eletrodo = 0;
    }
    else if (ch==2){
      eletrodo = 4;
    }
  }
  else if (ID == ID_AQ_U5){
    if (ch == 1){
      eletrodo = 3;
    }
    else if (ch==2){
      eletrodo = 7;
    }
  }
  else if (ID == ID_AQ_U6){
    if (ch == 1){
      eletrodo = 2;
    }
    else if (ch==2){
      eletrodo = 6;
    }
  }
  else if (ID == ID_AQ_CO){
    if (ch == 1){
      eletrodo = 91;
    }
    else if (ch==2){
      eletrodo = 92;
    }
  }
  Serial.print(" E");
  Serial.print(eletrodo);
  return eletrodo;
}



//Funcao para solicitar a resposta de um periférico e um canal com relacao aos valores de tensão medidos

void resposta(int ID, int mydelay){
  typedef union {
    float floatingPoint;
    byte binary[4];
  } binaryFloat;

  binaryFloat amplitude[2];
  int el = -1;
  
  
  if ((ID == 0x05)||(ID == 0x07)||(ID == 0x08)||(ID == 0x09)||(ID == 0x03)){
          Wire.requestFrom(ID, 9);
          int idx = 0; 
          int cont = 0;
          byte c;
          while(Wire.available()) {
            //Serial.print("Perif. ");         // Print ]
            //Serial.print(ID);       // Print 
            //Serial.print("; canal ");       // Print
             
            if (cont == 0){
              c = Wire.read();           // Receive a byte 
              //Serial.print(c);                // Print
              el = localizaeletrodo(ID,c);
              cont = cont +1;
            }
            
            while (idx < 2 && cont>0) {
              //Serial.print("IDx= ");
              //Serial.print(idx);
              //Serial.print(" - ");
              for (byte idy = 0; idy < 4; idy++) {
                amplitude[idx].binary[idy] = Wire.read();
              }
              idx++;
            }

            if (ID == ID_AQ_CO){
              if (c==1){
                corrente1 = amplitude[0].floatingPoint*ganhocorrente;
                corrente2 = amplitude[1].floatingPoint*ganhocorrente;
                Serial.print(" C1="); 
                Serial.print(corrente1,4); 
                Serial.print(" C2="); 
                Serial.print(corrente2,4);
                delay(mydelay);                
              }

            }
            else{
              medidas1[el] = amplitude[0].floatingPoint;
              ///corrente1;
              medidas2[el] = amplitude[1].floatingPoint;
              ///corrente2;
              //Serial.print(" "); 
              //Serial.print(amplitude[0].floatingPoint/corrente1,4); 
              //Serial.print(" "); 
              //Serial.print(amplitude[1].floatingPoint/corrente2,4);
              delay(mydelay);
            }
          
             
          }
   }
   else {
          Wire.requestFrom(ID, 3);
          while(Wire.available()) {
            int c = Wire.read();    // Receive a byte as character
            Serial.print(c);         // Print the character
            Serial.print(",");         // Print the character
          }
   }
}

// Funcoes para enviar comando para perifericos
void enviacomando (byte endereco, byte comandoenviado){
   Wire.beginTransmission(endereco);
   Wire.write(comandoenviado);              
   Wire.endTransmission();
}

// Funcoes para solicitar a o resultado da medição para cada um dos eletrodos
void pegaresposta (byte endereco, byte comando, int mydelay){
   Wire.beginTransmission(endereco);
   Wire.write(comando);              
   Wire.endTransmission();
   resposta(endereco, mydelay);
}

void subtrai_ref(int ref){
  if (ref >= 0){
   for (int i = 0; i < NE_MAX; i++){
    medidas1[i] = medidas1[i] - medidas1[ref];
    medidas2[i] = medidas2[i] - medidas2[ref];
   }
  }
   for (int i = 0; i < NE_MAX; i++){
              Serial.print(" "); 
              Serial.print(medidas1[i],4); 
              Serial.print(" "); 
              Serial.print(medidas2[i],4);
   }
}

// Funcao que envia o comando para retornar o valor medido por todos os eletrodos
void retornar_todos(int ref){
  byte enderecos[] = {ID_AQ_CO, ID_AQ_U4, ID_AQ_U1, ID_AQ_U6, ID_AQ_U5};
  byte comandos[] = {13, 18};
  for (int idc = 0; idc < 2; idc++){
    for (int ide = 0; ide < 5; ide++){
       pegaresposta(enderecos[ide],comandos[idc], 100);
    }
  }
  subtrai_ref(ref);
}



// Funcao que envia o comando para medir o valor por todos os eletrodos

void medir_todos(){
  byte enderecos[] = {ID_AQ_CO, ID_AQ_U4, ID_AQ_U1, ID_AQ_U6, ID_AQ_U5};
  byte comandos[] = {3, 8};
  for (int ide = 0; ide < 5; ide++){
    for (int idc = 0; idc < 2; idc++){
       enviacomando(enderecos[ide],comandos[idc]);
       delay(200);
    }
  }
}


void troca_frequencia_demodulacao(byte freq1, byte freq2){
  freq1 = freq1-44;
  freq2 = freq2-66;

  byte enderecos[] = {ID_AQ_CO, ID_AQ_U4, ID_AQ_U1, ID_AQ_U6, ID_AQ_U5};
  byte comandos[] = {freq1, freq2};
  for (int ide = 0; ide < 5; ide++){
    for (int idc = 0; idc < 2; idc++){
       enviacomando(enderecos[ide],comandos[idc]);
       delay(300);
    }
  }
}


// Funcao que seleciona as frequências de cada um dos geradores e altera o valor da frequência que será utilizada para realização da FFT na placa de aquisicao

void seleciona_2_freq(byte freq1, byte freq2){
   enviacomando(ID_MULT,freq2);

   Serial.println();
   #ifdef DEBUG1
      Serial.print("Enviado o comando para freq2 ");
      Serial.println(freq2);
   #endif
   
   delay(300);
   troca_frequencia_demodulacao(freq1,freq2);
   // Esse delay entre alteracao de freq testei com 300 e funcionou, com 250 ja eh necessario enviar duas vezes o mesmo comando
   enviacomando(ID_MULT,freq1);
   
   #ifdef DEBUG1
      Serial.print("Enviado o comando para freq1 ");
      Serial.println(freq1);
   #endif
}

void controla_injecao(int in1, int in2, int delayy){
  enviacomando(ID_DEMUX,in1);
  delay(delayy);
  enviacomando(ID_DEMUX,in2);
  delay(delayy);
}

void aquisicao_completa(int delayy, int mydelay2){ //delayy eh o atraso entre trocar os canais de aquisicao e o mydelay2 eh o atraso para enviar os comandos para o multiplexador 
  byte canal1[] = {I_E1, I_E2, I_E3, I_E4, I_E5, I_E6, I_E7, I_E0};
  byte canal2[] = {O_E0, O_E1, O_E2, O_E3, O_E4, O_E5, O_E6, O_E7};

  for (int pad = 0; pad < 8; pad++){
    #ifdef DEBUG1
      Serial.println();
      Serial.print("I");
      Serial.print(canal1[pad]-1);
      Serial.print(" O");
      Serial.println(canal2[pad]-128);
    #endif     
    controla_injecao(canal1[pad],canal2[pad],mydelay2);
    delay(mydelay2);
    medir_todos();
    retornar_todos(canal2[pad]-128);
  } 
}
