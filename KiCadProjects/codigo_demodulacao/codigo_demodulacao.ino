/* 
 * Exemplo de uso do ADC do STM32F103 em Dual Mode.
 *  
 * A taxa de amostragem é dada por:
 *  FS = 72 MHz / prescaler / (ADC_SMPR + 12.5)
 *  
 * Para PRE_SCALER==RCC_ADCPRE_PCLK_DIV_6 e ADC_SMPR==ADC_SMPR_7_5, a taxa de amostragem é:
 *  - Regular simultaneous mode: 600 kSps por canal, no caso de 2 canais
 *  - Fast interleaved mode: 1200 kSps
 *  
 * Obs: segundo nota do Reference Manual ([1], pág 215), não deve ser usado prescaler menor que 6 (72MHz/6 = 12MHz):
 * "The ADC input clock is generated from the PCLK2 clock divided by a prescaler and it must not exceed 14 MHz"
 * Provavelmente, a precisão da medida cai em frequências mais altas e cargas de alta impedância de saída devido aos 
 * capacitores do ADC (ADC do tipo "successive approximation analog-to-digital converter"). Ver [5], págs 6 e 33.
 *  
 * Escrito por: Erick León
 * 
 * Referências:
 * 
 * [1] STM32F10xxx Reference Manual (RM0008), disponível em www.st.com;
 * [2] Application note (AN3116), STM32's ADC modes and theis applications, disponível em www.st.com;
 * [3] Problems with regular simultaneous dual ADC conversion with DMA transfer, Spark Logic Forum,
 * disponível em https://sparklogic.ru/arduino-for-stm32/problems-with-regular-simultaneous-dual-adc.html
 * [4] https://github.com/rogerclarkmelbourne/Arduino_STM32/blob/master/STM32F1/libraries/STM32ADC/src/STM32ADC.cpp
 * [5] Application note (AN2834), How to get the best ADC accuracy in STM32 microcontrollers, disponível em www.st.com;

 * 
 */

#include <Wire_slave.h>
#include "stm32_adc_dual_mode.h"
#include "dft.h"


//#define comfase


#if defined comfase
       //
#else
       //
#endif



int npontos_base; // menor mutiplo inteiro de 'sample_freq/freq_sinal'.
//Define a quantidade minima de pontos para reconstruir o menor numero possivel de ciclos do sinal.
int n_pontos_mult;// fator multiplicador de 'npontos_base'. Permite adquirir mais ciclos do sinal.

const float referenceVolts= 3.3;
float sample_freq =  (72e6 / 6.0 / 20.0); // = 600kHz
float freq_sinal = 50000;  // 50kHz
float phase1, phase2, amplit1, amplit2; //phase1: phase2: amplit1: amplit2:
int NUM_SAMPLES = 24;      // number of samples for each ADCx. Each channel will be sampled NUM_SAMPLES/CHANNELS_PER_ADC
//NUM_SAMPLES precisa apenas ser iniciada????????? pode ser qualquer valor??????????
byte comando = 0; //entrada do i2c
boolean mediu = false;

int tempo_demodulacao ; // tempo em ms que demora a leitura e demodulacao



#define CHANNELS_PER_ADC  1                      // number of channels for each ADC. Must match values in ADCx_Sequence array below
#define ADC_SMPR          ADC_SMPR_7_5           // when using dual mode, each pair of channels must have same rate. Here all channels have the same
#define NUM_SAMPLES_MAX   500                    // number of samples for each ADCx. Each channel will be sampled NUM_SAMPLES/CHANNELS_PER_ADC
#define PRE_SCALER        RCC_ADCPRE_PCLK_DIV_6  // Prescaler do ADC
#define FAST_INTERLEAVED  false                  // Fast Interleave Mode Flag. Para "dobrar" taxa de amostragem medindo o mesmo canal dos 2 ADCs.
                                                 // Se 'false', habilita "Regular simultaneous mode". Se 'true', habilita "Fast interleaved mode".

#define LED PC13

uint32 adcbuf[NUM_SAMPLES_MAX+1];  // buffer to hold samples, ADC1 16bit, ADC2 16 bit
uint16_t datav1[NUM_SAMPLES_MAX+1];
uint16_t datav2[NUM_SAMPLES_MAX+1];

// O STM32F103 possui 10 pinos do ADC disponíveis:
// pino A0 (PA0) -> 0 (ADC0)
// ...
// pino A7 (PA7) -> 7 (ADC7)
// pino B0 (PB0) -> 8 (ADC8)
// pino B1 (PB1) -> 9 (ADC9)
// Para "dobrar" taxa de amostragem (FAST_INTERLEAVED true), medir o mesmo canal dos 2 ADCs.

//uint8 ADC1_Sequence[]={8,0,0,0,0,0};   // ADC1 channels sequence, left to right. Unused values must be 0. Note that these are ADC /channels, not pins
//uint8 ADC2_Sequence[]={9,0,0,0,0,0};   // ADC2 channels sequence, left to right. Unused values must be 0

// CASO 1: lê canal X e amplitude I1
uint8 ADC1_Sequence[]={0,0,0,0,0,0}; //PA0 sign_Cn
uint8 ADC2_Sequence[]={1,0,0,0,0,0}; //PA1 Ampl1


// CASO 2: lê canal X e canal Y
/*  uint8 ADC1_Sequence[]={0,0,0,0,0,0}; //PA0 sign_Cn
 *  uint8 ADC2_Sequence[]={8,0,0,0,0,0}; //PB0 sign_Cn+4
 */

// CASO 3: lê canal X e amplitude I2
/*  uint8 ADC1_Sequence[]={0,0,0,0,0,0}; //PA0 sign_Cn
 *  uint8 ADC2_Sequence[]={8,0,0,0,0,0}; //PA4 Ampl2
 */


void mede_ADC(){
  //Realiza a medicao das amplitudes vistas nos ADCs e calcula sinais medios;
  //retorna o calculo de amplitude e fase
  digitalWrite(LED, LOW); // Verificação de funcionamento
  // medindo valores:
  start_convertion_dual_channel(adcbuf, NUM_SAMPLES);
  wait_convertion_dual_channel();


uint16_t datav1[NUM_SAMPLES];
uint16_t datav2[NUM_SAMPLES];
    
  // separando valores lidos nos 2 ADCs:
  for(int i=0;i<(NUM_SAMPLES);i++) {
    //datav1[i] = ((adcbuf[i] & 0xFFFF0000) >>16);
    datav1[i] = (adcbuf[i] & 0xFFFF);
    datav2[i] = ((adcbuf[i] & 0xFFFF0000) >>16);
  }

  // calculando amplitudes e fases
  float media1 = sinal_medio (datav1, NUM_SAMPLES);
  calc_dft_singfreq(datav1, freq_sinal, sample_freq, media1, amplit1, phase1, 1000, NUM_SAMPLES);

  float media2 = sinal_medio (datav2, NUM_SAMPLES);
  calc_dft_singfreq(datav2, freq_sinal, sample_freq, media2, amplit2, phase2, 1000, NUM_SAMPLES);

  mediu = true;
  digitalWrite(LED, HIGH); // Verificação de funcionamento
}

void processacomando(){
  //Define a frequencia do sinal lido e o n de amostras - em funcao do comando recebido do master

  comando = Serial.read();
  
  switch (comando) {

    
    case 'i': // inicializa as medidas dos eletrodos
      mede_ADC();
      break;

case '1': // 200Khz 6 pontos (6 pts = 2 ciclos)
      freq_sinal = 200000;
      npontos_base = 3;
      n_pontos_mult = 2;
      tempo_demodulacao = 2;
      NUM_SAMPLES = npontos_base*n_pontos_mult;
      Serial.print("200Khz \t");
      Serial.print("num samples = ");
      Serial.print(NUM_SAMPLES);
      Serial.print("\t tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break;
   
    case '2': // 125Khz 24 pontos (24pts = 5 ciclos)
      freq_sinal = 125000;
      npontos_base = 24;
      n_pontos_mult = 1;
      tempo_demodulacao = 10;
      NUM_SAMPLES = npontos_base*n_pontos_mult;
      Serial.print("125Khz \t");
      Serial.print("num samples = ");
      Serial.print(NUM_SAMPLES);
      Serial.print("\t tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break;
   
    case '3': // 100Khz 12 pontos (12 pts = 2 ciclos)
      freq_sinal = 100000;
      npontos_base = 6;
      n_pontos_mult = 2;
      tempo_demodulacao = 5;
      NUM_SAMPLES = npontos_base*n_pontos_mult;
      Serial.print("100Khz \t");
      Serial.print("num samples = ");
      Serial.print(NUM_SAMPLES);
      Serial.print("\t tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break;
    
    case '4': // 50Khz 24 pontos (24 pts = 2 ciclos)
      freq_sinal = 50000;
      npontos_base = 12;
      n_pontos_mult = 2;
      tempo_demodulacao = 10;
      NUM_SAMPLES = npontos_base*n_pontos_mult;
      Serial.print("50Khz \t");
      Serial.print("num samples = ");
      Serial.print(NUM_SAMPLES);
      Serial.print("\t tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break; 

    case '5': // 5Khz 120 pontos (240 pts = 2 ciclos)
      freq_sinal = 5000;
      npontos_base = 120;
      n_pontos_mult = 2;
      tempo_demodulacao = 10;
      Serial.print("5Khz 240 pontos (240 pts = 2 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break;
      
    case '-': // diminui tempo para medida e demodulação
      tempo_demodulacao = tempo_demodulacao - 1;
      Serial.print("Tempo de demodulacao = ");
      Serial.println(tempo_demodulacao);
      break; 
      
    case '+': // aumenta tempo para medida e demodulação
      tempo_demodulacao = tempo_demodulacao + 1;
      Serial.print("Tempo de demodulacao = ");
      Serial.println(tempo_demodulacao);
      break; 
      

      
    case 't': // diminui nro de pontos
      if(n_pontos_mult>1){
        n_pontos_mult = n_pontos_mult-1;
        NUM_SAMPLES = npontos_base*n_pontos_mult;
        tempo_demodulacao = 1+(npontos_base*n_pontos_mult)/4;
      }
      else Serial.print("Nro de pontos minimo atingido. ");
      Serial.print("Npontos = ");
      Serial.print(npontos_base*n_pontos_mult);
      Serial.print("; npontos_base = ");
      Serial.print(npontos_base);
      Serial.print("; n_pontos_mult = ");
      Serial.print(n_pontos_mult);
      Serial.print("; tempo_demodulacao = ");
      Serial.println(tempo_demodulacao);
      break;
      
    case 'y': // aumenta nro de pontosNUM_SAMPLES_MAX
      if(((n_pontos_mult+1)*npontos_base) < NUM_SAMPLES_MAX){
        n_pontos_mult = n_pontos_mult+1;
        NUM_SAMPLES = npontos_base*n_pontos_mult;
        tempo_demodulacao = 1+(npontos_base*n_pontos_mult)/4;
      }
      else Serial.print("Nro de pontos maximo atingido. ");
      Serial.print("Npontos = ");
      Serial.print(npontos_base*n_pontos_mult);
      Serial.print("; npontos_base = ");
      Serial.print(npontos_base);
      Serial.print("; n_pontos_mult = ");
      Serial.print(n_pontos_mult);
      Serial.print("; tempo_demodulacao = ");
      Serial.println(tempo_demodulacao);
      break;



   case 'P':
      // imprimindo valores lidos:
      for(int i=0;i<(NUM_SAMPLES);i++) {
        float volts= ((adcbuf[i] & 0xFFFF) / 4095.0)* referenceVolts;
        float voltss=  (((adcbuf[i] & 0xFFFF0000) >>16) / 4095.0)* referenceVolts;
        
          Serial.print("adc1:");
          Serial.print(volts);
          Serial.print("\tadc2:");
          Serial.print(voltss);
          Serial.print("\tamplitude 1: ");
          Serial.print(amplit1);
          Serial.print("\tfase (2-1): ");
          Serial.println(phase2-phase1);
        }
      Serial.println();
      break;

////////////////////////////////////////////////////////////////

    default:
      break;
  }
  comando = 0;
}





////////////////////////////////////////////////////////////////////////////////////
void setup() {


  pinMode(LED, OUTPUT); // LED para verificação de funcionamento do eletrodo
   //digitalWrite(LED, HIGH); // Verificação de funcionamento
  Serial.begin(9600); // só usar para debugar...
  set_adc_dual_channel(PRE_SCALER, ADC_SMPR, CHANNELS_PER_ADC, ADC1_Sequence, ADC2_Sequence, FAST_INTERLEAVED);  // initial ADC1 and ADC2 settings

   
   
}

////////////////////////////////////////////////////////////////////////////////////
void loop() {

  if(Serial.available()){
    processacomando();
  }
}
