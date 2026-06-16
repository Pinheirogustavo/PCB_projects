 /*
 *  Codigo baseado no desenvolvido por Erick Dario Leon Bueno de Camargo em https://github.com/edlbcamargo/stm32/tree/master/dual_adc e adaptador por Mirela de Oliveira Tomazini:
 *  
 * Uso do ADC do STM32F103 em Dual Mode para aquisicao de sinais em dois canais simultaneamente
 *  
 * A taxa de amostragem é dada por:
 *  FS = 72 MHz / prescaler / (ADC_SMPR + 12.5)
 *  
 * Para PRE_SCALER==RCC_ADCPRE_PCLK_DIV_6 e ADC_SMPR==ADC_SMPR_1_5, a taxa de amostragem é:
 *  - Regular simultaneous mode: 857 kSps por canal, no caso de 2 canais
 *  - Fast interleaved mode: 1714 kSps
 *  
 * Para PRE_SCALER==RCC_ADCPRE_PCLK_DIV_2 e ADC_SMPR==ADC_SMPR_1_5, a taxa de amostragem é:
 *  - Regular simultaneous mode: 2.571 MSps por canal, no caso de 2 canais
 *  - Fast interleaved mode: 5.143 MSps
 *  
 * Obs: segundo nota do Reference Manual ([1], pág 215), não deve ser usado prescaler menor que 6 (72MHz/6 = 12MHz):
 * "The ADC input clock is generated from the PCLK2 clock divided by a prescaler and it must not exceed 14 MHz"
 * Provavelmente, a precisão da medida cai em frequências mais altas e cargas de alta impedância de saída devido aos 
 * capacitores do ADC (ADC do tipo "successive approximation analog-to-digital converter"). Ver [5], págs 6 e 33.
 *  
 * O original foi escrito por: Erick León
 * 
 * Referências:
 * 
 * [1] STM32F10xxx Reference Manual (RM0008), disponível em www.st.com;
 * [2] Application note (AN3116), STM32's ADC modes and theis applications, disponível em www.st.com;
 * [3] Problems with regular simultaneous dual ADC conversion with DMA transfer, Spark Logic Forum,
 * disponível em https://sparklogic.ru/arduino-for-stm32/problems-with-regular-simultaneous-dual-adc.html
 * [4] https://github.com/rogerclarkmelbourne/Arduino_STM32/blob/master/STM32F1/libraries/STM32ADC/src/STM32ADC.cpp
 * [5] Application note (AN2834), How to get the best ADC accuracy in STM32 microcontrollers, disponível em www.st.com;


 * ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * LISTA DE COMANDOS DISPONIVEIS PARA SEREM ENVIADOS A PARTIR DO CONTROLADOR PARA ESSE PERIFERICO 
 * 
 * n eh o ID do periferico, sendo que para aa placa de aquisicao U1, esse valor eh 7, para a U4 eh  8, para a U5 eh 9 e para a U6 eh 5.
 * 
 * 
 * COMANDOS DE MEDICAO
 * n001 - executa a função de medir para o canal 1 na frequência baixa
 * n002 - executa a função de medir para o canal 1 na frequência alta
 * n003 - executa a função de medir para o canal 1 em ambas as frequências
 * 
 * n006 - executa a função de medir para o canal 2 na frequência baixa
 * n007 - executa a função de medir para o canal 2 na frequência alta
 * n008 - executa a função de medir para o canal 2 em ambas as frequências
 * 
 * 
 * COMANDOS PARA RETORNAR OS DADOS MEDIDOS E DEMODULADOS
 * n011 - executa a função de retornar a informacao para o canal 1 na frequência baixa
 * n012 - executa a função de retornar a informacao para o canal 1 na frequência alta
 * n013 - executa a função de retornar a informacao para o canal 1 em ambas as frequências
 * 
 * n016 - executa a função de retornar a informacao para o canal 2 na frequência baixa
 * n017 - executa a função de retornar a informacao para o canal 2 na frequência alta
 * n018 - executa a função de retornar a informacao para o canal 2 em ambas as frequências
 * 
 * 
 * COMANDOS PARA ALTERAR AS FREQUENCIAS UTILIZADAS NA FFT
 * n021 - altera a frequência 1 utilizada na demodulação para 1kHz
 * n022 - altera a frequência 1 utilizada na demodulação para 2kHz
 * n023 - altera a frequência 1 utilizada na demodulação para 3kHz
 * n024 - altera a frequência 1 utilizada na demodulação para 5kHz
 * n025 - altera a frequência 1 utilizada na demodulação para 10kHz
 * n026 - altera a frequência 1 utilizada na demodulação para 20kHz
 * 
 * n031 - altera a frequência 2 utilizada na demodulação para 10kHz
 * n032 - altera a frequência 2 utilizada na demodulação para 20kHz
 * n033 - altera a frequência 2 utilizada na demodulação para 30kHz
 * n034 - altera a frequência 2 utilizada na demodulação para 50kHz
 * n035 - altera a frequência 2 utilizada na demodulação para 100kHz
 * n036 - altera a frequência 2 utilizada na demodulação para 150kHz
 * n037 - altera a frequência 2 utilizada na demodulação para 200kHz
 * 
 * 
 * COMANDOS PARA VERIFICAR AS FREQUENCIAS CONFIGURADAS PARA A FFT
 * n041 - retorna o valor para frequência baixa 
 * n042 - retorna o valor para frequência alta
 * n043 - retorna o valor para fambas as frequências
 * 
 * 
 */

const float referenceVolts= 3.3;

#define MEU_ENDERECO     0x03                   // definindo o endereço usado na comunicacao i2c
#define DEBUG             0                      // the DEBUG is used in the ifdef, when it is necessary it is possible to define DEBUG and use all the print in the code, if this whole line is commented the controller wont print the values
#define CHANNELS_PER_ADC  1                      // number of channels for each ADC. Must match values in ADCx_Sequence array below
#define NUM_SAMPLES       600                    // number of samples for each ADCx. Each channel will be sampled NUM_SAMPLES/CHANNELS_PER_ADC
#define ADC_SMPR          ADC_SMPR_7_5           // when using dual mode, each pair of channels must have same rate. Here all channels have the same
#define PRE_SCALER        RCC_ADCPRE_PCLK_DIV_6  // Prescaler do ADC
#define FAST_INTERLEAVED  false                  // Fast Interleave Mode Flag. Para "dobrar" taxa de amostragem medindo o mesmo canal dos 2 ADCs.
                                                 // Se 'false', habilita "Regular simultaneous mode". Se 'true', habilita "Fast interleaved mode".

typedef union {
    float floatingPoint;
    byte binary[4];
} binaryFloat;  


#include "stm32_adc_dual_mode.h"
#include "dft.h"
#include <Wire_slave.h>


float freq_1          = 1000;
float freq_2          = 10000;

float sample_freq     = 600000;

binaryFloat ch1_baixa;        
binaryFloat ch1_alta;         
binaryFloat ch2_baixa ;       
binaryFloat ch2_alta;         

byte nerr             = 0;
byte aux              = 0; 
byte y                 = 0;

uint32 adcbuf[NUM_SAMPLES+1];  // buffer to hold samples, ADC1 16bit, ADC2 16 bit
uint16 adc1buf[NUM_SAMPLES+1];  // buffer to hold samples, ADC1 16bit
uint16 adc2buf[NUM_SAMPLES+1];  // buffer to hold samples, ADC2 16 bit

// O STM32F103 possui 10 pinos do ADC disponíveis:
// pino A0 (PA0) -> 0 (ADC0)
// ...
// pino A7 (PA7) -> 7 (ADC7)
// pino B0 (PB0) -> 8 (ADC8)
// pino B1 (PB1) -> 9 (ADC9)
// Para "dobrar" taxa de amostragem (FAST_INTERLEAVED true), medir o mesmo canal dos 2 ADCs.

//In the Aquisicao V01 2024 board the STM32 pins connected to the electrodes are PA0 (ADC0) and PB0 (ADC8) that is the reason why ADC1 uses 0 and ADC2 uses 8 in the array below.

uint8 ADC1_Sequence[]={0,0,0,0,0,0};   // ADC1 channels sequence, left to right. Unused values must be 0. Note that these are ADC channels, not pins.  
uint8 ADC2_Sequence[]={8,0,0,0,0,0};   // ADC2 channels sequence, left to right. Unused values must be 0

byte flag = 0;
////////////////////////////////////////////////////////////////////////////////////


void receiveEvent(int howMany) {
  
  y = Wire.read();  // 
  flag = y;
  aux = 0;
  Serial.print("Recebi ");
  Serial.println(y);
}

void requestEvent(){
  if ((y>0) && (y<11)){
    byte dataBuffer[] = {MEU_ENDERECO, y, nerr};
    Wire.write(dataBuffer, sizeof(dataBuffer));

  }
  else if((y>10) && (y<21)){
    byte dataBuffer[] = {MEU_ENDERECO, y};
    switch (y){
        case 11:{
          //byte dataBuffer[] = {MEU_ENDERECO, y, ch1_baixa};
          byte dataBuffer[5];
          dataBuffer[0] = 1;
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+1] = ch1_baixa.binary[idx];
          }
          Wire.write(dataBuffer, sizeof(dataBuffer));
          Serial.print("7011 comando ");
          for(int idx = 0;idx<5; idx++){
            Serial.print(dataBuffer[idx]);
            Serial.print(" ");
          }

        }
        case 12:{
          //byte dataBuffer[] = {MEU_ENDERECO, y, ch1_alta};
          byte dataBuffer[5];
          dataBuffer[0] = 1;
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+1] = ch1_alta.binary[idx];
          }
          Wire.write(dataBuffer, sizeof(dataBuffer));
        }
        case 13:{
          //byte dataBuffer[] = {MEU_ENDERECO, ch1_baixa, ch1_alta};
          byte dataBuffer[9];
          dataBuffer[0] = 1;
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+1] = ch1_baixa.binary[idx];
          }
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+5] = ch1_alta.binary[idx];
          }
          Wire.write(dataBuffer, sizeof(dataBuffer));
        }
        case 16:{
          //byte dataBuffer[] = {MEU_ENDERECO, y, ch2_baixa};
          byte dataBuffer[5];
          dataBuffer[0] = 2;
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+1] = ch2_baixa.binary[idx];
          }
          Wire.write(dataBuffer, sizeof(dataBuffer));
        }
        case 17:{
          //byte dataBuffer[] = {MEU_ENDERECO, y, ch2_alta};
          byte dataBuffer[5];
          dataBuffer[0] = 2;
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+1] = ch2_alta.binary[idx];
          }
          Wire.write(dataBuffer, sizeof(dataBuffer));
        }
        case 18:{
          //byte dataBuffer[] = {MEU_ENDERECO, ch2_baixa, ch2_alta};
          byte dataBuffer[9];
          dataBuffer[0] = 2;
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+1] = ch2_baixa.binary[idx];
          }
          for (int idx = 0; idx< 4; idx++){
            dataBuffer[idx+5] = ch2_alta.binary[idx];
          }
          Wire.write(dataBuffer, sizeof(dataBuffer));
        }

     }
     Wire.write(dataBuffer, sizeof(dataBuffer));
   }
   else if((y>20) && (y<41)){
     byte dataBuffer[] = {MEU_ENDERECO, y, nerr};
     Wire.write(dataBuffer, sizeof(dataBuffer));
   }
    else if((y>40) && (y<51)){
      byte dataBuffer[] = {MEU_ENDERECO, y};
      switch (y){
        case 41:{
          byte dataBuffer[] = {MEU_ENDERECO, y,byte(freq_1/1000)};
        }
        case 42:{
          byte dataBuffer[] = {MEU_ENDERECO, y, byte(freq_2/1000)};
        }
        case 43:{
          byte dataBuffer[] = {MEU_ENDERECO, byte(freq_1/1000), byte(freq_2/1000)};
        }
        default:{
          byte dataBuffer[] = {MEU_ENDERECO, y, 93};
        }
        Wire.write(dataBuffer, sizeof(dataBuffer));
      }
    }
}

void setup() {
  Wire.begin(MEU_ENDERECO); //Endereço do MUX
  Wire.onReceive(receiveEvent);    // chama uma funcao qualquer quando algum dado eh recebido pelo i2c
  Wire.onRequest(requestEvent);  // registra um evento para tratar requisicoes
  
  Serial.begin(115200);
  set_adc_dual_channel(PRE_SCALER, ADC_SMPR, CHANNELS_PER_ADC, ADC1_Sequence, ADC2_Sequence, FAST_INTERLEAVED);  // initial ADC1 and ADC2 settings
}

////////////////////////////////////////////////////////////////////////////////////
void loop() {

  if ((flag >0) && (flag<11)) {
    // se o controlador enviar qualquer flag de medicao (entre 1 e 11) atraves de uma interrupcao para essa placa de aquisicao periferica, ela deve fazer a medicao dos pontos
    // medindo valores:
    Serial.println("IF 1 entre 0 e 11");

    start_convertion_dual_channel(adcbuf, NUM_SAMPLES);
    wait_convertion_dual_channel();
    /*
    #ifdef DEBUG
      // imprimindo valores lidos:
      for(int i=0;i<(NUM_SAMPLES);i++) {
        float volts= ((adcbuf[i] & 0xFFFF) / 4095.0)* referenceVolts;
        float voltss=  (((adcbuf[i] & 0xFFFF0000) >>16) / 4095.0)* referenceVolts;
    
        if(FAST_INTERLEAVED){ // Fast interleaved mode
          Serial.print("ADC:");
          Serial.println(voltss); //ADC2 é convertido primeiro... Ver [2], pág 10.
          Serial.print("ADC:");
          Serial.println(volts);
        }
        else{ // Regular simultaneous mode
          Serial.print("ADC1:");
          Serial.print(volts);
          Serial.print("\tADC2:");
          Serial.println(voltss);
        }
      }
      Serial.println(); 
     #endif
     */
     // se o modo FAST_INTERLEAVED for falso significa que esta sendo adquirido 2 canais de foma simultanea, portanto sera necessario dividir o buffer que contem cada informação de 32bits em 2 buffers em que cada informação possui 16 bits
    
     if(!FAST_INTERLEAVED){
      Serial.println("Aquisicao de pontos iniciada");
      for(int i=0;i<(NUM_SAMPLES);i++) {
        adc1buf[i] = (adcbuf[i] & 0xFFFF); //digitos menos significativos da array adcbuf vao para o buffer adc1buf
        adc2buf[i] = ((adcbuf[i] & 0xFFFF0000)>>16); //digitos mais significativos da array adcbuf vao para o buffer adc2buf
      }
      Serial.println("Aquisicao de pontos finalizada");
     }
  
      if ((flag>0) && (flag<6)){
      // valores entre 0 e 5 selecionam a funcao de coleta e calculo para o canal 1
      switch (flag){
        case 1:{
          //calcular a amplitude da baixa frequencia
          ch1_baixa.floatingPoint = calc_dft_singfreq(adc1buf,freq_1,sample_freq,sinal_medio(adc1buf));
          nerr=1;
          #ifdef DEBUG
            Serial.print("caso a. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq1 foi de ");
            Serial.println(ch1_baixa.floatingPoint);
          #endif  
          break;}
          
         case 2:{
          //calcular a amplitude da alta frequencia
          ch1_alta.floatingPoint = calc_dft_singfreq(adc1buf,freq_2,sample_freq,sinal_medio(adc1buf));
          nerr=1;
          #ifdef DEBUG
            Serial.print("caso b. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq2 foi de ");
            Serial.println(ch1_alta.floatingPoint);
          #endif
          break;}
          
         case 3:{
          //calcular a amplitude da baixa e alta frequencia
          ch1_baixa.floatingPoint = calc_dft_singfreq(adc1buf,freq_1,sample_freq,sinal_medio(adc1buf));
          ch1_alta.floatingPoint  = calc_dft_singfreq(adc1buf,freq_2,sample_freq,sinal_medio(adc1buf));
          nerr=1;
          #ifdef DEBUG
            Serial.print("caso c. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq1 e freq2 foi de ");
            Serial.print(ch1_baixa.floatingPoint);
            Serial.println(ch1_alta.floatingPoint);
          #endif
          break;
          }
          default:{
            #ifdef DEBUG
              Serial.print("caso c2. x escolhido foi ");
              Serial.print(flag);
              Serial.println(" Comando nao definido");
              nerr = 0;
            #endif
            break;
          }
        }
        flag = 0;
      }
      else if ((flag>5) && (flag<11)){
      // valores entre 6 e 10 selecionam a funcao de coleta e calculo para o canal 1
      aux = flag-5;
      
      switch (aux){
        case 1:{
          //calcular a amplitude da baixa frequencia
          ch2_baixa.floatingPoint = calc_dft_singfreq(adc2buf,freq_1,sample_freq,sinal_medio(adc2buf));
          nerr=1;
          #ifdef DEBUG
            Serial.print("caso d. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq1 foi de ");
            Serial.println(ch2_baixa.floatingPoint);
          #endif
          break;}
          
         case 2:{
          //calcular a amplitude da alta frequencia
          ch2_alta.floatingPoint = calc_dft_singfreq(adc2buf,freq_2,sample_freq,sinal_medio(adc2buf));
          nerr=1;
          #ifdef DEBUG
            Serial.print("caso e. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq2 foi de ");
            Serial.println(ch2_alta.floatingPoint);
          #endif
          break;}
          
         case 3:{
          //calcular a amplitude da baixa e alta frequencia
          ch2_baixa.floatingPoint = calc_dft_singfreq(adc2buf,freq_1,sample_freq,sinal_medio(adc2buf));
          ch2_alta.floatingPoint = calc_dft_singfreq(adc2buf,freq_2,sample_freq,sinal_medio(adc2buf));
          nerr=1;
          #ifdef DEBUG
            Serial.print("caso f. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq1 e freq2 foi de ");
            Serial.print(ch2_baixa.floatingPoint);
            Serial.println(ch2_alta.floatingPoint);
          #endif
          break;}
          default:{
            #ifdef DEBUG
              Serial.print("caso f2. x escolhido foi ");
              Serial.print(flag);
              Serial.println(" Comando nao definido");
              nerr = 0;
            #endif
            break;
      }
    }
    flag = 0;

  }
  }
    else if ((flag>10)&&(flag<20)){
       Serial.println("IF 2 entre 10 e 20");

      aux = flag - 10; 
      switch (aux){
        case 1:{
          //enviar a amplitude da baixa frequencia
          #ifdef DEBUG
            Serial.print("caso h. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq1 foi de ");
            Serial.println(ch1_baixa.floatingPoint);
          #endif
          break;}
          
         case 2:{
          //enviar a amplitude da alta frequencia
          #ifdef DEBUG
            Serial.print("caso i. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq2 foi de ");
            Serial.println(ch1_alta.floatingPoint);
          #endif
          break;}
          
         case 3:{
         //enviar a amplitude da baixa e alta frequencia
          #ifdef DEBUG
            Serial.print("caso j. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq1 e freq2 foi de ");
            Serial.print(ch1_baixa.floatingPoint);
            Serial.println(ch1_alta.floatingPoint);
          #endif
          break;}
          
          case 6:{
          //enviar a amplitude da baixa frequencia
          #ifdef DEBUG
            Serial.print("caso l. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq1 foi de ");
            Serial.println(ch2_baixa.floatingPoint);
           #endif
          break;}

          case 7:{
          //enviar a amplitude da alta frequencia
          #ifdef DEBUG
            Serial.print("caso m. x escolhido foi ");
            Serial.print(flag);
            Serial.print(" e a amplitude para freq2 foi de ");
            Serial.println(ch2_alta.floatingPoint);
          #endif
          break;}
          case 8:{
          //enviar a amplitude da baixa e alta frequencia
          #ifdef DEBUG
             Serial.print("caso n. x escolhido foi ");
             Serial.print(flag);
             Serial.print(" e a amplitude para freq1 e freq2 foi de ");
             Serial.print(ch2_baixa.floatingPoint);
             Serial.println(ch2_alta.floatingPoint);
           #endif
           break;}
           
           default:{
            #ifdef DEBUG
              Serial.print("caso n2. x escolhido foi ");
              Serial.print(flag);
              Serial.println(" Comando nao definido");
              nerr = 0;
            #endif
            break;    
      }
    }
    flag = 0;

   }
 

    else if ((flag>20)&&(flag<30)){
          Serial.println("IF 3 entre 20 e 31");

      // funcao de alterar as frequencias de referencia
      aux = flag-20;
      switch (aux){
        case 1:
          freq_1 = 1000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_1 alterada para 1.000 Hz");
          #endif
          break;
        case 2:
          freq_1 = 2000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_1 alterada para 2.000 Hz");
          #endif
          break;
        case 3:
          freq_1 = 3000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_1 alterada para 3.000 Hz");
          #endif        
          break;
         case 4:
          freq_1 = 5000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_1 alterada para 5.000 Hz");
          #endif 
          break;
         case 5:
          freq_1 = 10000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_1 alterada para 10.000 Hz");
          #endif 
          break;
         case 6:
          freq_1 = 20000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_1 alterada para 20.000 Hz");
          #endif 
          break;
         default:
          nerr = 9;
          #ifdef DEBU
            Serial.println("comando para alterar freq_1 desconhecido"); 
          #endif 
          break;
      }
      flag = 0;

    }
    else if ((flag>30)&&(flag<40)){
      // selecionado para alterar a freq2 que eh a mais alta
      aux = flag-30;
      Serial.println("IF 4 entre 30 e 41");

      switch (aux){
        case 1:
          freq_2 = 10000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_2 alterada para 10.000 Hz");
          #endif
          break;
        case 2:
          freq_2 = 20000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_2 alterada para 20.000 Hz");
          #endif
          break;
        case 3:
          freq_2 = 30000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_2 alterada para 30.000 Hz");
          #endif          
          break;
         case 4:
          freq_2 = 50000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_2 alterada para 50.000 Hz");
          #endif
          break;
         case 5:
          freq_2 = 100000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_2 alterada para 100.000 Hz");
          #endif
          break;
         case 6:
          freq_2 = 150000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_2 alterada para 150.000 Hz");
          #endif          
          break;
         case 7:
          freq_2 = 200000;
          nerr=3;
          #ifdef DEBUG
            Serial.println("freq_2 alterada para 200.000 Hz");
          #endif
          break;
         default:
          nerr = 9;
          Serial.println("comando para alterar freq_2 desconhecido");
          break;
      }
      flag = 0;

    }
    else if ((flag>40)&&(flag<50)){
    Serial.println("IF 5 entre 40 e 51");

    // funcao que retorna valores configurados
    aux = flag-40; 
    flag = 0;
    }
    else if (flag>0){
      Serial.println("IF 6 outros");

      flag = 0;
    }
  }
