// Codigo utilizado no STM32F103C8T6 que atua como controlador
// O objetivo é garantir que a comunicação entre os n dispositivos STM32 ( 1 controlador e n-1 perifericos) esta ocorrendo

// Criado por: Mirela de Oliveira Tomazini em 01 de setembro de 2024
// Código adaptado a partir do arquivo "Wire Peripheral Receiver" by Nicholas Zambetti [http://www.zambetti.com](http://www.zambetti.com) - Created 29 March 2006
// This example code is in the public domain.
// Código editado em 16 de março de 2026.

// O pino B6 - SCL (clock) do mestre e escravo estao conectados entre si a um ressitor pul-up (vide esquema)
// O pino B7 - SDA (dados) do mestre e escravo estao conectados entre si a um ressitor pul-up (vide esquema)
// Alem disso, os pinos GND de ambas as placas estao conectadas para garantir que ambos tenham a mesma referencia.


/* * LISTA DE COMANDOS DISPONIVEIS PARA SEREM ENVIADOS DIRETAMENTE A ESSE CONTROLADOR
 *  OS COMANDOS QUE PODEM SER ENVIADOS A PARTIR DESSE CONTROLADOR PARA CADA UM DOS PERIFERICOS EH DESCRITO NA PROGRAMACAO DE CADA UM DOS PERIFERICOS, COMANDOS DESSE CONTROLADOR ESTAO DESCRITOS ABAIXO:
 *  
 *  
 *  101 - Altera as frequências geradas para 2kHz e 10 kHz
 *  102 - Altera as frequências geradas para 2kHz e 20 kHz
 *  103 - Altera as frequências geradas para 1kHz e 50 kHz
 *  104 - Altera as frequências geradas para 10kHz e 100 kHz
 *  105 - Altera as frequências geradas para 10kHz e 200 kHz
 *  106 - Altera as frequências geradas para 10kHz e 20 kHz
 *  107 - Altera as frequências geradas para 5kHz e 50 kHz
 *  108 - Altera as frequências geradas para 20kHz e 200 kHz


 *  110 - Solicita os valores adquiridos por todos os eletrodos
 *  
 *  111 - Conecta E1 na I1 e E0 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  112 - Conecta E2 na I1 e E1 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  113 - Conecta E3 na I1 e E2 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  114 - Conecta E4 na I1 e E3 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  115 - Conecta E5 na I1 e E4 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  116 - Conecta E6 na I1 e E5 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  117 - Conecta E7 na I1 e E6 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  118 - Conecta E0 na I1 e E7 na I2 (Terra ou contrafase) e solicita aquisicao 
 *  

 * a - altera flag loop para true
 * b - altera flag loop para false
 * 
 * c - aumenta o mydelay em 5 ms
 * d - diminui o mydelay em 5 ms
 * 
 * e - altera flagloopcompleto para true
 * f - altera flagloopcompleto para false
 *
 *Se o flagloop for verdadeiro e o flagloop completo também for, serao realizadas varreduras completas seguidas;
 *Se o flagloop for verdadeiro e o flagloop completo NÃO for, o controlador ficará pedindo para todos os eletrodos medirem e para todos retornarem, sem mudar o padrão de injeção;
 *Se o flagloop for falso, o sistema ficará printanto pontos na tela apenas para confirmar a comunicacao;
 * 
 */



#include <Wire_slave.h>
#include "controlador.h"

#define DEBUG 0
#define DEBUG1 0



typedef union {
    float floatingPoint;
    byte binary[4];
} binaryFloat;

String receivedData = "";
int comprimento;
char vetorcaracteres[10];
int periferico;
int error;
bool flagloop = false;
bool flagloopcompleto = false;
bool flagvarredura = false;
int mydelay = 200;

binaryFloat amplitude[2];

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PC13, OUTPUT);      // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);         // start serial for output
  Wire.begin();               // join i2c bus (address optional for master)
}

// the loop function runs over and over again forever
void loop() {

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Se o flagloop for verdadeiro e o flagloop completo também for, sera realizada uma varredura completa;
// Se o flagloop for verdadeiro e o flagloop completo NÃO for, o controlador ficará pedindo para todos os eletrodos medirem e para todos retornarem, sem mudar o padrão de injeção
// Se o flagloop for falso, o sistema ficará printanto pontos na tela apenas para confirmar a comunicacao

  if (flagloop){
    if (flagloopcompleto){
      //medir_CO1();
      //delay(100);
      //retornar_CO1();
      //delay(100);
      aquisicao_completa(10,mydelay);
      Serial.println();
      delay(100);
    }
    else if(flagvarredura){
      seleciona_2_freq(F1_2K,F2_0);
      aquisicao_completa(10,mydelay);
      delay(mydelay);
      seleciona_2_freq(F1_5K,F2_0);
      aquisicao_completa(10,mydelay);
      delay(mydelay);
      seleciona_2_freq(F1_10K,F2_0);
      aquisicao_completa(10,mydelay);
      delay(mydelay);
      seleciona_2_freq(F1_20K,F2_0);
      aquisicao_completa(10,mydelay);
      delay(mydelay);
      flagvarredura = false;
      flagloop = false;
    }
    else{
      medir_todos();
      retornar_todos(-1);
      Serial.println();
      delay(mydelay); 
    }
  }
  else{
    Serial.println(".");
  }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// Coleta os dados na serial, se for comando numerico, escreve no receivedData, se for comando alfabéticos ele trata de acordo.

  while(Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      receivedData += (char)inChar;
    }
    else{
      if (inChar == 'a'){
        flagloop = true;
      }
      if (inChar == 'b'){
        flagloop = false;
      }
      if (inChar == 'c'){
        mydelay = mydelay +5;
        Serial.print("DELAY: ");
        Serial.println(mydelay);
      }
      if (inChar == 'd'){
        mydelay = mydelay-5;
        Serial.print("DELAY: ");
        Serial.println(mydelay);
      }
       if (inChar == 'e'){
        flagloopcompleto = true;
      }
      if (inChar == 'f'){
        flagloopcompleto = false;
      }
      if (inChar == 'g'){
        flagloop = true;
        flagloopcompleto = true;
      }
      if (inChar == 'h'){
        flagloop = false;
        flagloopcompleto = false;
      }
      if (inChar == 'i'){
        flagloop = true;
        flagvarredura = true;
      }
      if (inChar == 'j'){
        flagloop = false;
        flagvarredura = false;
      }
    }
  }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// Tratando os comandos que são maiores que 1000, ou seja, comandos que devem ser enviados para os perfiéricos 

    if (receivedData.toInt() > 1000){
      
      receivedData = receivedData.toInt();
      
      #ifdef DEBUG
        Serial.print("Recebido da Serial: ");
        Serial.println(receivedData);     // Imprima os dados recebidos para verificação
      #endif
      
      switch ((int)(receivedData.toInt()/1000)) {
      case 4:
        periferico = ID_MULT; // Gerador multifrequencial 
        break;
      case 6:
        periferico = ID_DEMUX; // Placa de MUX/ DEMUX
        break;
      case 7:
        periferico = ID_AQ_U1; // U1 da placa de Aquisicao, controla C1 e C5, que são (0/1) e (4/5)
        break;
      case 8:
        periferico = ID_AQ_U4; // U4 da placa de Aquisicao, controla C2 e C6, que são (0/1) e (4/5)
        break;
      case 9:
        periferico = ID_AQ_U5; // U5 da placa de Aquisicao, controla C3 e C7, que são (2/3) e (6/7)
        break;
      case 5:
        periferico = ID_AQ_U6; // U6 da placa de Aquisicao, controla C4 e C8, que são (2/3) e (6/7)
        break;
      case 3:
        periferico = ID_AQ_CO; // U6 da placa de Aquisicao, controla C4 e C8, que são (2/3) e (6/7)
        break;
      default:
        error = 1;
        break;
        #ifdef DEBUG
          Serial.println("Escravo nao reconhecido");
        #endif
      }
      
      if (error == 0){
        #ifdef DEBUG
          Serial.print("Comunicar com o ");
          Serial.println(periferico);
          Serial.print(" e enviar o comando");
          Serial.println(receivedData.toInt()-periferico*1000);
        #endif
    
        Wire.beginTransmission(periferico);
        Wire.write(receivedData.toInt()-periferico*1000);          // sends one byte
        Wire.endTransmission();     // stop transmitting
        digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW]
    
        resposta(periferico, 100);
        
        receivedData = "";
     }
     else{
        #ifdef DEBUG
          Serial.println("Erro resetado");
        #endif
        error = 0;
        receivedData = "";
      }
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Tratando os comandos que são maiores que 100, ou seja, comandos para que o controlador execute sequencias de funcoes especificas

    else if (receivedData.toInt()>100){

      #ifdef DEBUG
        Serial.print("Recebido da Serial: ");
        Serial.println(receivedData);     // Imprima os dados recebidos para verificação
      #endif
      
      switch (receivedData.toInt()) {
      case 101:
        //gerador 1 com freq de 2kHz, gerador 2 com freq de 10kHz
        seleciona_2_freq(F1_2K,F2_10K);
        #ifdef DEBUG1
          Serial.println("Freq1 2k e Freq2 10k");
        #endif   
        break;
      case 102:
        //gerador 1 com freq de 2kHz, gerador 2 com freq de 20kHz
        seleciona_2_freq(F1_2K,F2_20K);   
        #ifdef DEBUG1
          Serial.println("Freq1 2k e Freq2 20k");
        #endif  
        break;
      case 103:
        //gerador 1 com freq de 1kHz, gerador 2 com freq de 50kHz
        seleciona_2_freq(F1_1K,F2_50K);
        #ifdef DEBUG1
          Serial.println("Freq1 1k e Freq2 50k");
        #endif   
        break;
      case 104:
        //gerador 1 com freq de 10kHz, gerador 2 com freq de 100kHz
        seleciona_2_freq(F1_10K,F2_100K);
        #ifdef DEBUG1
          Serial.println("Freq1 10k e Freq2 100k");
        #endif  
        break;  
      case 105:
        //gerador 1 com freq de 10kHz, gerador 2 com freq de 200kHz
        seleciona_2_freq(F1_10K,F2_200K);
        #ifdef DEBUG1
          Serial.println("Freq1 10k e Freq2 200k");
        #endif 
        break;
      case 106:
        //gerador 1 com freq de 10kHz, gerador 2 com freq de 20kHz
        seleciona_2_freq(F1_10K,F2_20K);
        #ifdef DEBUG1
          Serial.println("Freq1 10k e Freq2 20k");
        #endif 
        break;
      case 107:
        //gerador 1 com freq de 5kHz, gerador 2 com freq de 50kHz
        seleciona_2_freq(F1_5K,F2_50K);
        #ifdef DEBUG1
          Serial.println("Freq1 5k e Freq2 50k");
        #endif 
        break;
      case 108:
        //gerador 1 com freq de 20kHz, gerador 2 com freq de 200kHz
        seleciona_2_freq(F1_20K,F2_200K);
        #ifdef DEBUG1
          Serial.println("Freq1 20k e Freq2 200k");
        #endif 
        break;
      case 110:
        // Retorna todos os valores de amplitude de tensão medidos
        retornar_todos(-1);
        break;  
        
      case 111:
        // Fonte de corrente conectada no E1 e Terra no E0 e solicita medicao dos eletrodos
        controla_injecao(I_E1,O_E0,mydelay);
        #ifdef DEBUG1
          Serial.println("E1 I1 e E0 Terra");
        #endif 
        medir_todos();
        break;
        
      case 112:
        // Fonte de corrente conectada no E2 e Terra no E1 e solicita medicao dos eletrodos
        controla_injecao(I_E2,O_E1,mydelay);
        #ifdef DEBUG1
          Serial.println("E2 I1 e E1 Terra");
        #endif 
        medir_todos();
        break;
        
      case 113:
        // Fonte de corrente conectada no E3 e Terra no E2 e solicita medicao dos eletrodos
        controla_injecao(I_E3,O_E2,mydelay);
        #ifdef DEBUG1
          Serial.println("E3 I1 e E2 Terra");
        #endif 
        medir_todos();
        break;
        
      case 114:
        // Fonte de corrente conectada no E4 e Terra no E3 e solicita medicao dos eletrodos
        controla_injecao(I_E4,O_E3,mydelay);
        #ifdef DEBUG1
          Serial.println("E4 I1 e E3 Terra");
        #endif 
        medir_todos();
        break;
        
       case 115:
        // Fonte de corrente conectada no E5 e Terra no E4 e solicita medicao dos eletrodos
        controla_injecao(I_E5,O_E4,mydelay);
        #ifdef DEBUG1
          Serial.println("E5 I1 e E4 Terra");
        #endif 
        medir_todos();
        break;
        
      case 116:
        // Fonte de corrente conectada no E6 e Terra no E5 e solicita medicao dos eletrodos
        controla_injecao(I_E6,O_E5,mydelay);
        #ifdef DEBUG1
          Serial.println("E6 I1 e E5 Terra");
        #endif 
        medir_todos();
        break;

      case 117:
        // Fonte de corrente conectada no E7 e Terra no E6 e solicita medicao dos eletrodos
        controla_injecao(I_E7,O_E6,mydelay);
        #ifdef DEBUG1
          Serial.println("E7 I1 e E6 Terra");
        #endif 
        medir_todos();
        break;
        
      case 118:
        // Fonte de corrente conectada no E0 e Terra no E7 e solicita medicao dos eletrodos
        controla_injecao(I_E0,O_E7,mydelay);
        #ifdef DEBUG1
          Serial.println("E0 I1 e E7 Terra");
        #endif 
        medir_todos();
        break;
       
       default:
          #ifdef DEBUG
            Serial.println("Comando nao reconhecido");
          #endif
      }


      receivedData = "";
    }
    else if (receivedData.toInt() > 1){ // limpando caso venha um comando com apenas 1 numero
      receivedData = "";
    }
  
    
  
  
  digitalWrite(PC13, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(200);                 // adiciona um delay de 400 ms
  digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                 // adiciona um delay de 400 ms
  
}
