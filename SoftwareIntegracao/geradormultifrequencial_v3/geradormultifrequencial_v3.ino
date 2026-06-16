/*
 * COMANDOS QUE PODEM SER ENVIADOS A PARTIR DO CONTROLADOR PARA ESSE PERIFERICO
 * 
 * 
 * COMANDOS DE CONFERENCIA
 * 4048 - Retorna a informação de frequência configurada no primeiro gerador de sinal (frequencias de 1kHz a 20 kHz)
 * 4049 - Retorna a informação de frequência configurada no segundo gerador de sinal (frequências de 10kHz a 200 kHz)
 * 
 * 
 * COMANDOS PARA ALTERACAO DA FREQUENCIA NO GERADOR 1
 * 4065 - Altera a frequência do Gerador 1 para 1kHz, ou seja, freq1 = 1000;
 * 4066 - Altera a frequência do Gerador 1 para 2kHz, ou seja, freq1 = 2000;
 * 4067 - Altera a frequência do Gerador 1 para 3kHz, ou seja, freq1 = 3000;
 * 4068 - Altera a frequência do Gerador 1 para 5kHz, ou seja, freq1 = 5000;
 * 4069 - Altera a frequência do Gerador 1 para 10kHz, ou seja, freq1 = 10000;
 * 4070 - Altera a frequência do Gerador 1 para 20kHz, ou seja, freq1 = 20000;
 *
 * 4090 - Altera a frequência do Gerador 1 para 0kHz, ou seja, freq1 = 0; (para desabilitar o uso desse gerador;
 * 
 * 
 *  * COMANDOS PARA ALTERACAO DA FREQUENCIA NO GERADOR 2
 * 4097 - Altera a frequência do Gerador 2 para 10 kHz, ou seja, freq2 = 10000;
 * 4098 - Altera a frequência do Gerador 2 para 20 kHz, ou seja, freq2 = 20000;
 * 4099 - Altera a frequência do Gerador 2 para 30 kHz, ou seja, freq2 = 30000;
 * 4100 - Altera a frequência do Gerador 2 para 50 kHz, ou seja, freq2 = 50000;
 * 4101 - Altera a frequência do Gerador 2 para 100 kHz, ou seja, freq2 = 100000;
 * 4102 - Altera a frequência do Gerador 2 para 150 kHz, ou seja, freq2 = 150000;
 * 4103 - Altera a frequência do Gerador 2 para 200 kHz, ou seja, freq2 = 200000;
 * 
 * 4122- Altera a frequência do Gerador 2 para 0kHz, ou seja, freq2 = 0; (para desabilitar o uso desse gerador;
 * 
 */




// =============================================================================================================
// --- Mapeamento de Bibliotecas ---
#include <Wire_slave.h>


// =============================================================================================================
// --- Mapeamento de Hardware ---
#define W_CLK_2 PA7  //Pino WCLK  do módulo AD9850 - Gerador 2 (amarelo)
#define FQ_UD_2 PA6  //Pino FQUP  do módulo AD9850 - Gerador 2 (laranja)
#define DATA_2 PA5   //Pino data  do módulo AD9850 - Gerador 2 (preto)
#define RESET_2 PA4  //Pino reset do módulo AD9850 - Gerador 2 (verde)

#define W_CLK_1 PB12  //Pino WCLK  do módulo AD9850 - Gerador 1 (amarelo)
#define FQ_UD_1 PB13  //Pino FQUP  do módulo AD9850 - Gerador 1 (laranja)
#define DATA_1 PB14   //Pino data  do módulo AD9850 - Gerador 1 (preto)
#define RESET_1 PB15  //Pino reset do módulo AD9850 - Gerador 1 (cinza)


// =============================================================================================================
// --- Constantes Auxiliares ---
#define AD9850_CLOCK 125000000  //Frequência do cristal do módulo
#define SLAVE_ADDRESS 0x04
//#define DEBUG 0
byte x = 0;

// =============================================================================================================
// --- Funções Auxiliares ---
#define pulseHigh(pin) \
  { \
    digitalWrite(pin, HIGH); \
    digitalWrite(pin, LOW); \
  }
//Cria uma função que se chama "pulseHigh", primeiro escreve o valor lógico "HIGH" nesse pino e, em seguida, escreve o valor lógico "LOW" nesse pino.


// =============================================================================================================
// --- Protótipo das Funções ---
//==========================================
void receiveEvent(int howMany);
void tfr_byte_1(byte data);              //transfere um byte de forma serial, pelo pino DATA
void tfr_byte_2(byte data);              //transfere um byte de forma serial, pelo pino DATA
void sendFrequency_1(double frequency);  //envia a frequência configurada pelo usuário
void sendFrequency_2(double frequency);  //envia a frequência configurada pelo usuário

int aux = 0;
int control = 2;
double freqaux = 0;
long unsigned int freq_1 = 1000;          //local de definição do valor de frequência do sinal desejado no Gerador 1
long unsigned int freq_2 = 10000;         //local de definição do valor de frequência do sinal desejado no Gerador 2
byte auxfreq1 = 65;
byte auxfreq2 = 97;
bool nerr = 1;

// =============================================================================================================
// --- Configurações Iniciais ---
void setup() {
  pinMode(FQ_UD_1, OUTPUT);  //Configura pinos como saída que serão enviados para o Gerador 1
  pinMode(W_CLK_1, OUTPUT);
  pinMode(DATA_1, OUTPUT);
  pinMode(RESET_1, OUTPUT);
  pinMode(FQ_UD_2, OUTPUT);  //Configura pinos como saída que serão enviados para o Gera
  pinMode(W_CLK_2, OUTPUT);
  pinMode(DATA_2, OUTPUT);
  pinMode(RESET_2, OUTPUT);

  // --- Configurações da comunicacao I2C ---
  Wire.begin(SLAVE_ADDRESS);                 // Configura que esse sera o escravo com endereco 4
  Wire.onReceive(receiveEvent);  // Registra o evento
  Wire.onRequest(requestEvent);  // registra um evento para tratar requisicoes
  Serial.begin(9600);            // Inicia o modulo serial
  pinMode(PC13, OUTPUT);        // define PC13 como uma saida
  
  // Inicializa os módulos AD9850.
  pulseHigh(RESET_1);
  pulseHigh(W_CLK_1);
  pulseHigh(FQ_UD_1);  //Este pulso habilita o AD9850 para funcionar no modo serial (ver datasheet pag 12, figura 10)

  pulseHigh(RESET_2);
  pulseHigh(W_CLK_2);
  pulseHigh(FQ_UD_2);

  //final das configurações iniciais do AD9850

  sendFrequency1(freq_1);
  sendFrequency1(freq_2);
}

// =============================================================================================================
// --- Loop Infinito ---
void loop() {
  //delay(200);
  //control = x%2;
  //if (control == 0) {
  //  freqaux = x;
  //  freq_2 = freqaux*1000;
  //}
  //else if (control == 1){
  //  freqaux = x-1;
  //  freq_1 = freqaux*1000;
  //}
  //else {
  //  freq_1 = 2000;
  //  freq_2 = 20000;
  //}

  //sendFrequency1(3000);
  //sendFrequency2(1000);
  //Serial.print("x eh ");
  //Serial.print(x);
  //Serial.print(" freqaux eh ");
  //Serial.print(freqaux);
  //Serial.print(" freq1 eh ");
  //Serial.print(freq_1);
  //Serial.print(" freq2 eh ");
  //Serial.println(freq_2);
  //delay(800);                 // adiciona um delay de 400 ms
  //digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(800);                 // adiciona um delay de 400 ms
  //digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW

  digitalWrite(PC13, LOW);   // turn the LED off by making the voltage LOW
  delay(200);                // adiciona um delay de 200 ms
  digitalWrite(PC13, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(200);                // adiciona um delay de 200 ms

  if (aux ==1) {
    aux = 0;
    #ifdef DEBUG
      Serial.print("x eh ");
      Serial.print(x);
      Serial.print(" freq1 eh ");
      Serial.print(freq_1);
    #endif
    sendFrequency1(freq_1);
    
  }
  else if (aux ==2){
    aux = 0;
    #ifdef DEBUG
      Serial.print("x eh ");
      Serial.print(x);
      Serial.print(" freq2 eh ");
      Serial.print(freq_2);
    #endif
    
    sendFrequency2(freq_2);
    aux == 0;
  }
  else if (aux ==3){
    aux = 0;
    #ifdef DEBUG
      Serial.print("x eh ");
      Serial.print(x);
      Serial.print(" freq2 eh ");
      Serial.print(freq_2);
    #endif
    sendFrequency2(freq_2);
  }
  

 
}



// =============================================================================================================
// --- Desenvolvimento das Funções ---

// =============================================================================================================

void receiveEvent(int howMany) {
  x = Wire.read();  // receive byte as an integer porque o x eh um inteiro
  
  if ((x>64)&&(x<69)){
    auxfreq1 = x;
    nerr = 1;
  }
  else if ((x>96)&&(x<103)){
    auxfreq2 = x;
    nerr = 1;
  }


  switch (x) {
      case 65:
        freq_1 = 1000;
        aux = 1;
        break;
      case 66:
        freq_1 = 2000;
        aux = 1;
        break;
      case 67:
        freq_1 = 3000;
        aux = 1;
        break;
      case 68:
        freq_1 = 5000;
        aux = 1;
        break;
      case 69:
        freq_1 = 10000;
        aux = 1;
        break;
      case 70:
        freq_1 = 20000;
        aux = 1;
        break;
      case 90:
        freq_1 = 0;
        aux = 1;
        nerr = 1;
        break;
      case 97:
        freq_2 = 10000;
        aux = 2;
        break;
       case 98:
        freq_2 = 20000;
        aux = 2;
        break;
       case 99:
        freq_2 = 30000;
        aux = 2;
        break;
       case 100:
        freq_2 = 50000;
        aux = 2;
        break;
       case 101:
        freq_2 = 100000;
        aux = 2;
        break;
       case 102:
        freq_2 = 150000;
        aux = 2;
        break;
       case 103:
        freq_2 = 200000;
        aux = 2;
        break;
       case 122:
        freq_2 = 0;
        aux = 2;
        nerr = 1;
        break;
      default:
          nerr = 0;
          #ifdef DEBUG
              Serial.println("Comando nao reconhecido");
          #endif
      }
  
}

void requestEvent(){
    if (x == 48){
      nerr = 1;
      x = auxfreq1;}
    else if (x == 49){
      nerr = 1;
      x = auxfreq2;}
  
  byte dataBuffer[] = {SLAVE_ADDRESS, x, nerr};
  Wire.write(dataBuffer, sizeof(dataBuffer));
}

void tfr_byte_1(byte data) {
  for (int i = 0; i < 8; i++, data >>= 1) {
    digitalWrite(DATA_1, data & 0x01);
    pulseHigh(W_CLK_1);  //gera um pulso no W_CLK a cada bit transferido
  }                      //end for
}  //end tfr_byte

void tfr_byte_2(byte data) {
  for (int i = 0; i < 8; i++, data >>= 1) {
    digitalWrite(DATA_2, data & 0x01);
    pulseHigh(W_CLK_2);  //gera um pulso no W_CLK a cada bit transferido
  }                      //end for
}  //end tfr_byte

// =============================================================================================================
void sendFrequency1(double frequency) {
  int32_t freq1 = frequency * 4294967295 / AD9850_CLOCK;  //calcula frequência

  for (int b = 0; b < 4; b++, freq1 >>= 8) tfr_byte_1(freq1 & 0xFF);

  tfr_byte_1(0x000);   //Final, reinicia o valor do byte
  pulseHigh(FQ_UD_1);  //Pronto!

}  //end sendFrequency

void sendFrequency2(double frequency) {
  int32_t freq2 = frequency * 4294967295 / AD9850_CLOCK;  //calcula frequência

  for (int c = 0; c < 4; c++, freq2 >>= 8) tfr_byte_2(freq2 & 0xFF);

  tfr_byte_2(0x000);   //Final, reinicia o valor do byte
  pulseHigh(FQ_UD_2);  //Pronto!

}  //end sendFrequency


// =============================================================================================================
