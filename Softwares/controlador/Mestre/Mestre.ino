

//#define DEBUG

#include <Wire.h>
#include "ad9850.h"
#include "gerador.h"
#include "stm32_adc_dual_mode.h"
#include "dft.h"


#define NUM_ELETRODOS 8
#define R_SENT_INA 10       // 10ohms, em algumas placas está 47 ohms
#define GANHO_INA  16.1976  // G_ina = 1+(50k/3,29k)
#define GANHO_CORRENTE (1000.0/(R_SENT_INA*GANHO_INA)) // Para corrente em mA (R_sent = 10ohm; G_ina = 1+(50k/3,29k) )
                                                       // Vina= Vrs.G --> Vrs = Vina/G ; I = Vrs/rs --> I = Vina/(G.rs)

#define F5K     5000
#define F50K   50000
#define F100K 100000
#define F125K 125000
#define F200K 200000

#define CHANNELS_PER_ADC  1                      // number of channels for each ADC. Must match values in ADCx_Sequence array below
#define ADC_SMPR          ADC_SMPR_7_5           // when using dual mode, each pair of channels must have same rate. Here all channels have the same
#define NUM_SAMPLES_MAX   500                    // number of samples for each ADCx. Each channel will be sampled NUM_SAMPLES/CHANNELS_PER_ADC
#define PRE_SCALER        RCC_ADCPRE_PCLK_DIV_6  // Prescaler do ADC
#define FAST_INTERLEAVED  false                  // Fast Interleave Mode Flag. Para "dobrar" taxa de amostragem medindo o mesmo canal dos 2 ADCs.

#define LED PC13

typedef union{
  float floatingPoint;
  byte binary[4];
} binaryFloat;

//////////////// Variáveis relacionadas à amostragem

uint32 adcbuf[NUM_SAMPLES_MAX+1];  // buffer to hold samples, ADC1 16bit, ADC2 16 bit
uint16_t datav1[NUM_SAMPLES_MAX+1];
uint16_t datav2[NUM_SAMPLES_MAX+1];

float freq_sinal = 200000;  // 200kHz
int n_pontos_base = 3;
int n_pontos_mult = 2;
int num_samples = n_pontos_base*n_pontos_mult;



float amplitudes[NUM_ELETRODOS]; //vetor de amplitudes vistas pelos eletrodos
float fases[NUM_ELETRODOS];      //vetor de fases (em relacao a ?????) vistas pelos eletrodos

float amplitudes_frame[NUM_ELETRODOS*NUM_ELETRODOS];
float fases_frame[NUM_ELETRODOS*NUM_ELETRODOS];

float ampli_corrente[NUM_ELETRODOS], fase_corrente[NUM_ELETRODOS];



float phase1, phase2, amplit1, amplit2;

byte comando = 0;
boolean mediu = false;


//////////////// Configuração do ADC

// O STM32F103 possui 10 pinos do ADC disponíveis:
// pino A0 (PA0) -> 0 (ADC0)
// ...
// pino A7 (PA7) -> 7 (ADC7)
// pino B0 (PB0) -> 8 (ADC8)
// pino B1 (PB1) -> 9 (ADC9)
// Para "dobrar" taxa de amostragem (FAST_INTERLEAVED true), medir o mesmo canal dos 2 ADCs.

//uint8 ADC1_Sequence[]={8,0,0,0,0,0};   // ADC1 channels sequence, left to right. Unused values must be 0. Note that these are ADC /channels, not pins
//uint8 ADC2_Sequence[]={9,0,0,0,0,0};   // ADC2 channels sequence, left to right. Unused values must be 0

// CASO 2: lê canal X e canal Y
uint8 ADC1_Sequence[]={4,0,0,0,0,0}; // Amplitude da corrente está ligada no PA4
uint8 ADC2_Sequence[]={8,0,0,0,0,0}; // PB0 não está sendo usado, vamos ignorar a medida

const float referenceVolts= 3.3;
float sample_freq =  (72e6 / 6.0 / 20.0); // = 600kHz

/*

VERSAO 0: da qualif

setup:
 - configura 200kHz e 6 pontos

loop:
 - verifica se chegou comando... se chegou, trata (por enquanto, ignora comando)
 - for padrão de 1 a 8:
    - configura injeção do padrão -> I2C para/de o MUX
    - lê 8 eletrodos e guarda em vetor tam 64 -> I2C para/de canais de medição
    - se erro, termina for
 - se não erro, envia 64 valores pela Serial

VERSAO 1:
setup:
 - configura 200kHz e 6 pontos

loop:
 - verifica se chegou comando... se chegou, trata
 - for padrão de 1 a 8:
    - configura injeção do padrão -> I2C para/de o MUX
    - avisar canais qual padrão é o atual
    - lê 8 eletrodos e guarda em vetor tam 64 -> I2C para/de canais de medição
    - se erro, termina for
 - se não erro, envia 64 valores pela Serial

----- no código do canal:
 - na 1a vez, só lê...
 - da 2a em diante, ajusta ganho ótimo para aquele padrão
 - dependendo do padrão, altera ganho..

*/

byte num_eletrodos_usados = NUM_ELETRODOS; // mudar para: int num_eletrodos_usados = NUM_ELETRODOS


int tempo_demodulacao = 2; // tempo em ms que demora a leitura e demodulacao

byte pula = 0;

byte flag_leitura_continua = false;
byte flag_leitura_continua_limpa = false;
byte flag_envia_impedancia = false;




void mede_ADC(){
  //Realiza a medicao das amplitudes vistas nos ADCs e calcula sinais medios;
  //retorna o calculo de amplitude e fase
  digitalWrite(LED, LOW); // Verificação de funcionamento
  // medindo valores:
  start_convertion_dual_channel(adcbuf, num_samples);
  wait_convertion_dual_channel();

  // separando valores lidos nos 2 ADCs:
  for(int i=0;i<(num_samples);i++) {
    //datav1[i] = ((adcbuf[i] & 0xFFFF0000) >>16);
    //datav2[i] = (adcbuf[i] & 0xFFFF);
    datav2[i] = ((adcbuf[i] & 0xFFFF0000) >>16);
  }

  // calculando amplitudes e fases
  float media1 = sinal_medio (datav1, num_samples);
  phase1 = 0, amplit1=0;
 // amplit1 =   calc_dft_singfreq(datav1, freq_sinal, sample_freq, media1, 10000, num_samples, &phase1);
  calc_dft_singfreq(datav1, freq_sinal, sample_freq, media1, amplit1, phase1, 1000, num_samples);
    //verificar essa funcao no programa TG, pois retornava amplitude e fase

  float media2 = sinal_medio (datav2, num_samples);
  phase2 = 0;
//  amplit2 =   calc_dft_singfreq(datav2, freq_sinal, sample_freq, media2, 10000, num_samples, &phase2);
  calc_dft_singfreq(datav2, freq_sinal, sample_freq, media2, amplit2, phase2, 1000, num_samples);
    //verificar essa funcao no programa TG, pois retornava amplitude e fase

  mediu = true;
  digitalWrite(LED, HIGH); // Verificação de funcionamento
}




/* Processa comandos enviados pela I2C:
 * - 'P': imprime valores medidos na serial
 * - '1': 200Khz 6 pontos (6 pts = 2 ciclos)
 * - '2': 125Khz 24 pontos (24pts = 5 ciclos)
 * - '3': 100Khz 12 pontos (12 pts = 2 ciclos)
 * - '4': 50Khz 24 pontos (24 pts = 2 ciclos)
 * - '5': 5Khz 240 pontos (240 pts = 2 ciclos)
 * - 'i': inicia conversão AD
 * - 't': decrementa o numero de pontos amostrados (diminui o fator de multiplicacao de ciclos amostrados)
 * - 'y': incrementa o numero de pontos amostrados (aumenta o fator de multiplicacao de ciclos amostrados)
 */
void processacomando(){
  //Define a frequencia do sinal lido e o n de amostras - em funcao do comando recebido do master
  switch (comando) {

#ifdef DEBUG
    case 'P':
      // imprimindo valores lidos:
      for(int i=0;i<(num_samples);i++) {
        float volts= ((adcbuf[i] & 0xFFFF) / 4095.0)* referenceVolts;
        float voltss=  (((adcbuf[i] & 0xFFFF0000) >>16) / 4095.0)* referenceVolts;

        if(FAST_INTERLEAVED){ // Fast interleaved mode, não utilizado ainda
          /*Serial.print("ADC:");
          Serial.println(voltss); //ADC2 é convertido primeiro... Ver [2], pág 10.
          Serial.print("ADC:");
          Serial.println(volts);*/
        }
        else{ // Regular simultaneous mode
          Serial.print("adc1:");
          Serial.print(volts);
          Serial.print("\tadc2:");
          Serial.println(voltss);
        }
      }
      Serial.print("\tamplitude 1: ");
      Serial.print(amplit1);
      Serial.print("\tamplitude 2: ");
      Serial.println(amplit2);
      Serial.println();
      break;
#endif

    case 1: // 200Khz 6 pontos (6 pts = 2 ciclos)
      freq_sinal = 200000;
      n_pontos_base = 3; // sample_freq/freq_sinal
      n_pontos_mult = 2;
      num_samples = n_pontos_base*n_pontos_mult;
      break;

    case 2: // 125Khz 24 pontos (24pts = 5 ciclos)
      freq_sinal = 125000;
      n_pontos_base = 24;  // (sample_freq/freq_sinal)*5
      n_pontos_mult = 1;
      num_samples = n_pontos_base*n_pontos_mult;
      break;

    case 3: // 100Khz 12 pontos (12 pts = 2 ciclos)
      freq_sinal = 100000;
      n_pontos_base = 6; // sample_freq/freq_sinal
      n_pontos_mult = 2;
      num_samples = n_pontos_base*n_pontos_mult;
      break;

    case 4: // 50Khz 24 pontos (24 pts = 2 ciclos)
      freq_sinal = 50000;
      n_pontos_base = 12; //sample_freq/freq_sinal
      n_pontos_mult = 2;
      num_samples = n_pontos_base*n_pontos_mult;
      break;

       case 5: // 5Khz 240 pontos (240 pts = 2 ciclos)
      freq_sinal = 5000;
      n_pontos_base = 120; //sample_freq/freq_sinal
      n_pontos_mult = 2;
      num_samples = n_pontos_base*n_pontos_mult;
      break;

    case 'i': // inicializa as medidas dos eletrodos
      mede_ADC();
      break;

    case 't': // decrementa o numero de pontos amostrados (diminui o fator de multiplicacao de ciclos amostrados)
      n_pontos_mult = n_pontos_mult-1;
      if (n_pontos_mult<1) n_pontos_mult = 1;
      num_samples = n_pontos_base*n_pontos_mult;
      break;

    case 'y': // incrementa o numero de pontos amostrados (aumenta o fator de multiplicacao de ciclos amostrados)
      n_pontos_mult = n_pontos_mult+1;
      if (n_pontos_base*n_pontos_mult >= NUM_SAMPLES_MAX) n_pontos_mult = n_pontos_mult-1;
      num_samples = n_pontos_base*n_pontos_mult;
      break;

    default:
      break;
  }
  comando = 0; // depois que processa, volta para comando = 0
}


//funcao para enviar o mesmo comando para todos perifericos de um mesmo conjunto (eletrodos, gerador, mux)
void envia_comando_todos(byte comando){
  for (byte n = 0; n < num_eletrodos_usados; n++) wire_envia_byte(0X51+n,comando); // envia para eletrodos
  //wire_envia_byte(0X40,comando); // Envia para gerador de onda
  wire_envia_byte(0X60,comando); // Envia para controlador do mux
}

//imprime os valores de duas medidas, m1 e m2:
  //m1: ???
  //m2: ???
void imprime_uma_medida(float m1, float m2){
  Serial.print("(");
  Serial.print(m1,3);
  Serial.print(";");
  Serial.print(m2,3);
  Serial.print(")\t");  
}

void imprime_uma_medida_limpa(float m1, float m2){
  Serial.print(m1,3);
  Serial.print("\t");
  Serial.print(m2,3);
  Serial.print("\t");  
}

// avisa aos eletrodos para iniciar nova leitura. Envia comando 'i' para todos os uC dos eletrodos
  //i: inicia_leitura_eletrodos();
void inicia_leitura_eletrodos(){
  for (byte n = 0; n < num_eletrodos_usados; n++) wire_envia_byte(0X51+n,'i');
}

// altera a injecao de corrente percorrendo todos os eletrodos; realiza medida de amp e fase a cada iteracao
void inicia_leitura_um_frame(byte padrao){
  for (byte n = 0; n < num_eletrodos_usados; n++){ 
    // Passo 1: define as saidas acionadas pelos muxs com base no num de eletrodos usados e padrao de injecao
    wire_envia_byte(0X60, 1 + n);
    wire_envia_byte(0X61, 1 + ( (n+padrao)%num_eletrodos_usados) );

    // Passo 2: Dispara leitura nos eletrodos
    envia_comando_todos('i'); // i:inicia_leitura_eletrodos();

    // Passo 3: Aguarda a leitura e a demodulação
    delay(tempo_demodulacao); // deixar o menor possível que nunca dê erro

    // Passo 4: Ler amplitudes e fases
    pega_leitura_eletrodos();
    pega_leitura_de_um_eletrodo(0X40, &ampli_corrente[n], &fase_corrente[n]);
    ampli_corrente[n] = ampli_corrente[n]*GANHO_CORRENTE; // calcula corrente
    for (byte m = 0; m < num_eletrodos_usados; m++){ // copiando valores para matriz
      amplitudes_frame[m+(n*num_eletrodos_usados)] = amplitudes[m];
      fases_frame[m+(n*num_eletrodos_usados)] = fases[m];
    }
  }
}

// pega a amplitude e fase da corrente monitorada no ina???
void pega_leitura_de_um_eletrodo(byte endereco, float *amplitude, float *fase){
  Wire.requestFrom(endereco, 8);

  binaryFloat amplitude_lida, fase_lida;
  for(byte idx = 0; idx < 4; idx++) amplitude_lida.binary[idx] = Wire.read();
  
  for(byte idx = 0; idx < 4; idx++) fase_lida.binary[idx] = Wire.read();

  *amplitude = amplitude_lida.floatingPoint;
  *fase = fase_lida.floatingPoint;
}

//retorna arrays de amplitude e fase lidas sequencialmente em todos os eletrodos
void pega_leitura_eletrodos(){
  for (byte n = 0; n < num_eletrodos_usados; n++){
    float ampl, pha;
    pega_leitura_de_um_eletrodo(0X51+n, &ampl, &pha);
    amplitudes[n] = ampl;
    fases[n] = pha;
  } 
}


// A partir de um comando serial assume determinado fluxo de execucao, relacionados a:
  //frequencia do sinal de excitacao
  //tempo de demodulacao
  //iniciar medidas dos eletrodos
  //imprimir medidas dos eletrodos
  //pegar frame e imprimir matriz ???
  //alterar padrao de injecao
void processacomandoserial(){
  int comandoserial = Serial.read();
   
   switch (comandoserial) {

//////////////////////////////////// Selecao de frequencias ////////////////////////////////////
    case '1': // 200Khz 6 pontos (6 pts = 2 ciclos)
      envia_comando_todos(1);
      n_pontos_base = 3;
      n_pontos_mult = 2;
      tempo_demodulacao = 2;
      Serial.print("200Khz 6 pontos (6 pts = 2 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      ad9850_sendFrequency(200000);
      break;
   
    case '2': // 125Khz 24 pontos (24pts = 5 ciclos)
      envia_comando_todos(2);
      n_pontos_base = 24;
      n_pontos_mult = 1;
      tempo_demodulacao = 10;
      Serial.print("125Khz 24 pontos (24pts = 5 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      ad9850_sendFrequency(125000);
      break;
   
    case '3': // 100Khz 12 pontos (12 pts = 2 ciclos)
      envia_comando_todos(3);
      n_pontos_base = 6;
      n_pontos_mult = 2;
      tempo_demodulacao = 5;
      Serial.print("100Khz 12 pontos (12 pts = 2 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      ad9850_sendFrequency(100000);
      break;
    
    case '4': // 50Khz 24 pontos (24 pts = 2 ciclos)
      envia_comando_todos(4);
      n_pontos_base = 12;
      n_pontos_mult = 2;
      tempo_demodulacao = 10;
      Serial.print("50Khz 24 pontos (24 pts = 2 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      ad9850_sendFrequency(50000);
      break; 

    case '5': // 5Khz 120 pontos (240 pts = 2 ciclos)
      envia_comando_todos(5);
      n_pontos_base = 120;
      n_pontos_mult = 2;
      tempo_demodulacao = 10;
      Serial.print("5Khz 240 pontos (240 pts = 2 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      ad9850_sendFrequency(5000);
      break;
////-----------------------------------------------------------------------------------------------------////

////////////////////////////////////////// parametros de demodulacao ////////////////////////////////////////
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
        envia_comando_todos('t');
        tempo_demodulacao = 1+(n_pontos_base*n_pontos_mult)/4;
      }
      else Serial.print("Nro de pontos minimo atingido. ");
      Serial.print("Npontos = ");
      Serial.print(n_pontos_base*n_pontos_mult);
      Serial.print("; n_pontos_base = ");
      Serial.print(n_pontos_base);
      Serial.print("; n_pontos_mult = ");
      Serial.print(n_pontos_mult);
      Serial.print("; tempo_demodulacao = ");
      Serial.println(tempo_demodulacao);
      break;

    case 'u': // aumenta nro de pontosNUM_SAMPLES_MAX
      if(((n_pontos_mult+1)*n_pontos_base) < NUM_SAMPLES_MAX){
        n_pontos_mult = n_pontos_mult+1;
        envia_comando_todos('y');
        tempo_demodulacao = 1+(n_pontos_base*n_pontos_mult)/4;
      }
      else Serial.print("Nro de pontos maximo atingido. ");
      Serial.print("Npontos = ");
      Serial.print(n_pontos_base*n_pontos_mult);
      Serial.print("; n_pontos_base = ");
      Serial.print(n_pontos_base);
      Serial.print("; n_pontos_mult = ");
      Serial.print(n_pontos_mult);
      Serial.print("; tempo_demodulacao = ");
      Serial.println(tempo_demodulacao);
      break;
////-----------------------------------------------------------------------------------------------------////

//////////////////////////////////////////// controle de eletrodos //////////////////////////////////////////
//// DEBUG MUX inicio
    case 'd':
      wire_envia_byte(0X60, 1);
      Serial.println("DEBUG Injetando no eletrodo 1");
      break;

    case 'D':
    wire_envia_byte(0X60, 0X80+2);
      Serial.println("DEBUG Drenando no eletrodo 2");
      break;
//// DEBUG MUX fim

    case 'a':
      /*  //altear mux para padrão de injeção 1-2
          //wire_envia_byte(0X60, 1);
          //wire_envia_byte(0X61, 2);
          //Serial.println("Injetando nos eletrodos 1 e 2"); */
      //altear mux para padrão de injeção 0-1
      wire_envia_byte(0X60, 0);
      wire_envia_byte(0X60, 0X80+1);
      Serial.println("Injetando nos eletrodos 0 e 1");
      break;

    case 'b':
      /*  // altear mux para padrão de injeção 2-3
          //wire_envia_byte(0X60, 2);
          //wire_envia_byte(0X61, 3);
          //Serial.println("Injetando nos eletrodos 2 e 3");*/
      // altear mux para padrão de injeção 1-2
      wire_envia_byte(0X60, 1);
      wire_envia_byte(0X60, 0X80+2);
      Serial.println("Injetando nos eletrodos 1 e 2");
      break;

    case 'c':
      /*  // altear mux para padrão de injeção 3-4
          //wire_envia_byte(0X60, 3);
          //wire_envia_byte(0X61, 4);
          //Serial.println("Injetando nos eletrodos 3 e 4");*/
      // altear mux para padrão de injeção 2-3
      wire_envia_byte(0X60, 2);
      wire_envia_byte(0X60, 0X80+3);
      Serial.println("Injetando nos eletrodos 2 e 3");
      break;

    case 'w': // diminui padrao de injecao
      if( pula > 1 ){
        pula = pula-1;
        Serial.print("Usando padrao pula ");
        Serial.println(pula);
      }
      else Serial.println("Padrao pula no limite");
      break;

    case 'z': // aumenta padrao de injecao
      if( (pula+1) < num_eletrodos_usados){
        pula = pula+1;
        Serial.print("Usando padrao pula ");
        Serial.println(pula);
      }
      else Serial.println("Padrao pula no limite");
      break;
////-----------------------------------------------------------------------------------------------------////

///////////////////////////////////////////// modos de leitura //////////////////////////////////////////////
    case 'i': // inicia medidas nos eletrodos
      inicia_leitura_eletrodos();
      Serial.println("Leitura dos eletrodos iniciada...");
      break;

    case 'v': // pega valores lidos dos eletrodos
      pega_leitura_eletrodos();
      delay(tempo_demodulacao); // aguarda leitura e demodulação; menor possível
      Serial.println("Valores lidos:");

      for (byte n = 0; n < num_eletrodos_usados; n++){
        imprime_uma_medida(amplitudes[n],fases[n]);
      }
      Serial.println();
      break;

    case 'f': // pega 1 frame
      inicia_leitura_um_frame(pula);
      for (byte n = 0; n < num_eletrodos_usados*num_eletrodos_usados; n++){
        imprime_uma_medida(amplitudes_frame[n],fases_frame[n]);
      }
      Serial.println();
      break;

    case 'm': // pega 1 frame e mostra a matriz
      inicia_leitura_um_frame(pula);
      for (byte n = 0; n < num_eletrodos_usados*num_eletrodos_usados; n++){
        if( (n%num_eletrodos_usados)== 0) Serial.println();
        imprime_uma_medida(amplitudes_frame[n],fases_frame[n]);
      }
      Serial.println();
      Serial.println();
      for (byte n = 0; n < num_eletrodos_usados; n++){
        imprime_uma_medida(ampli_corrente[n],fase_corrente[n]);
      }
      Serial.println(" [mA]");
      break;

    case 'j': // leitura continua dividindo pela corrente (envia impedancias)
      flag_leitura_continua_limpa = true;
      flag_envia_impedancia = true;
      break;

    case 'k': // leitura continua
      flag_leitura_continua = true;
      break;

    case 'l': // leitura continua
      flag_leitura_continua_limpa = true;
      flag_envia_impedancia = false;
      break;

    case 's': // interromper leitura continua
      flag_leitura_continua = false;
      flag_leitura_continua_limpa = false;
      flag_envia_impedancia = false;
      break;
////-----------------------------------------------------------------------------------------------------////

/////////////////////////////////// DIGPOT - Controle da amplitude do sinal /////////////////////////////////
    case 'L': // diminui a amplitude do sinal (wiper up)
      diminui_ganho();
      break;

    case 'U': // aumenta a amplitude do sinal (wiper down)
      aumenta_ganho();
      break;

    case 'S': // Salva a resistencia
      digitalWrite(cs_digpot1, HIGH);
      delay(loopPeriod);
      digitalWrite(cs_digpot1, LOW);
      break;

    case 'x':
      ganho_minimo();
      break;

    case 'y':
      ganho_maximo();
      break;

    case 'p':
      //printa_dados();
      break;
////-----------------------------------------------------------------------------------------------------////

/////////////////////////////////// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx /////////////////////////////////
      case 'P':
        envia_comando_todos('P');
        break;
        
    default:
      break;
  }
}

// funcao para enviar um byte (com) a determinado periferico(endereco)
void wire_envia_byte(byte endereco, byte com) {
    Wire.beginTransmission(endereco);
    Wire.write(com);
    Wire.endTransmission();    
}

void setup(){
  disableDebugPorts();// permite utilizar os pinos B3, B4 e A15 como GPIO, mover BOOT0 para 1 para poder gravar
  Wire.begin(); // join i2c bus (address optional for master)
  delay(300);  // aguarda 300ms para os slaves ligarem
  //wire_envia_byte(0X40,1); // Inciando gerador em 200kHz
  n_pontos_base = 3; // por que iniciar essas variaveis com estes valores ??????
  n_pontos_mult = 2;  // por que iniciar essas variaveis com estes valores ??????
  tempo_demodulacao = 2;  // por que iniciar essas variaveis com estes valores ??????
  Serial.begin(9600);
  delay(1000);
  Serial.println("Aguarde a configuracao do sistema");

ad9850_setup();
gerador_setup();
delay(1000);
Serial.println("Configuracao encerrada");
}

void loop(){
  if (Serial.available() > 0) {
    processacomandoserial();
  }
  if(flag_leitura_continua){
      inicia_leitura_um_frame(pula);
      for (byte n = 0; n < num_eletrodos_usados*num_eletrodos_usados; n++){
        imprime_uma_medida(amplitudes_frame[n],fases_frame[n]);
      }
      for (byte n = 0; n < num_eletrodos_usados; n++){
        imprime_uma_medida(ampli_corrente[n],fase_corrente[n]);
      }
      Serial.println();
  }
  if(flag_leitura_continua_limpa){
      inicia_leitura_um_frame(pula);
      for (byte n1 = 0; n1 < num_eletrodos_usados; n1++){
        for (byte n2 = 0; n2 < num_eletrodos_usados; n2++){
          byte n = n1*num_eletrodos_usados + n2;
          if(flag_envia_impedancia){
            imprime_uma_medida_limpa(amplitudes_frame[n]/ampli_corrente[n1],fases_frame[n]-fase_corrente[n1]);
          }
          else{
            imprime_uma_medida_limpa(amplitudes_frame[n],fases_frame[n]);
          }
        }
      }
      for (byte n = 0; n < num_eletrodos_usados; n++){
        imprime_uma_medida_limpa(ampli_corrente[n],fase_corrente[n]);
      }
      Serial.println();
  }
}
