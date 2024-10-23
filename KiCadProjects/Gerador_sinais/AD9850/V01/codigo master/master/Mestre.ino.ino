#include <Wire.h>

#define NUM_ELETRODOS 8
byte num_eletrodos_usados = NUM_ELETRODOS; // mudar para: int num_eletrodos_usados = NUM_ELETRODOS

#define GANHO_CORRENTE (1000.0/(47*2.8)) // Para corrente em mA (R_sent = 47ohm; G_ina = 2.8)
int tempo_demodulacao = 2; // tempo em ms que demora a leitura e demodulacao

byte pula = 1;

byte flag_leitura_continua = false;
byte flag_leitura_continua_limpa = false;
byte flag_envia_impedancia = false;


#define NUM_SAMPLES_MAX   500
int n_pontos_base, n_pontos_mult;

typedef union{
  float floatingPoint;
  byte binary[4];
} binaryFloat;


float amplitudes[NUM_ELETRODOS];
float fases[NUM_ELETRODOS];

float amplitudes_frame[NUM_ELETRODOS*NUM_ELETRODOS];
float fases_frame[NUM_ELETRODOS*NUM_ELETRODOS];

float ampli_corrente[NUM_ELETRODOS], fase_corrente[NUM_ELETRODOS];

void envia_comando_todos(byte comando){
  for (byte n = 0; n < num_eletrodos_usados; n++) wire_envia_byte(0X51+n,comando); // envia para eletrodos
  wire_envia_byte(0X40,comando); // Envia para gerador de onda
}


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

// avisando aos eletodos para iniciar nova leitura
void inicia_leitura_eletrodos(){
  for (byte n = 0; n < num_eletrodos_usados; n++) wire_envia_byte(0X51+n,'i');
}

// Configurando os muxs e avisando aos eletodos para iniciar nova leitura
void inicia_leitura_um_frame(byte padrao){
  for (byte n = 0; n < num_eletrodos_usados; n++){ 
    // Passo 1: Ajusta os mux
    wire_envia_byte(0X60, 1 + n);
    wire_envia_byte(0X61, 1 + ( (n+padrao)%num_eletrodos_usados) );

    // Passo 2: Dispara leitura nos eletrodos
    envia_comando_todos('i');

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

void pega_leitura_de_um_eletrodo(byte endereco, float *amplitude, float *fase){
  Wire.requestFrom(endereco, 8);

  binaryFloat amplitude_lida, fase_lida;
  for(byte idx = 0; idx < 4; idx++) amplitude_lida.binary[idx] = Wire.read();
  
  for(byte idx = 0; idx < 4; idx++) fase_lida.binary[idx] = Wire.read();

  *amplitude = amplitude_lida.floatingPoint;
  *fase = fase_lida.floatingPoint;
}

void pega_leitura_eletrodos(){
  for (byte n = 0; n < num_eletrodos_usados; n++){
    float ampl, pha;
    pega_leitura_de_um_eletrodo(0X51+n, &ampl, &pha);
    amplitudes[n] = ampl;
    fases[n] = pha;
  } 
}

void setup()
{ 
  Wire.begin(); // join i2c bus (address optional for master)
  delay(300);  // aguarda 300ms para os slaves ligarem
  wire_envia_byte(0X40,1); // Inciando gerador em 200kHz
  n_pontos_base = 3;
  n_pontos_mult = 2;
  tempo_demodulacao = 2;
  Serial.begin(115200);
}

void loop()
{
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

void processacomandoserial(){
  int comandoserial = Serial.read();
   
   switch (comandoserial) {
    case '1': // 200Khz 6 pontos (6 pts = 2 ciclos)
      envia_comando_todos(1);
      n_pontos_base = 3;
      n_pontos_mult = 2;
      tempo_demodulacao = 2;
      Serial.print("200Khz 6 pontos (6 pts = 2 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break;
   
    case '2': // 125Khz 24 pontos (24pts = 5 ciclos)
      envia_comando_todos(2);
      n_pontos_base = 24;
      n_pontos_mult = 1;
      tempo_demodulacao = 10;
      Serial.print("125Khz 24 pontos (24pts = 5 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break;
   
    case '3': // 100Khz 12 pontos (12 pts = 2 ciclos)
      envia_comando_todos(3);
      n_pontos_base = 6;
      n_pontos_mult = 2;
      tempo_demodulacao = 5;
      Serial.print("100Khz 12 pontos (12 pts = 2 ciclos) e tempo de demod = ");
      Serial.println(tempo_demodulacao);
      break;
    
    case '4': // 50Khz 24 pontos (24 pts = 2 ciclos)
      envia_comando_todos(4);
      n_pontos_base = 12;
      n_pontos_mult = 2;
      tempo_demodulacao = 10;
      Serial.print("50Khz 24 pontos (24 pts = 2 ciclos) e tempo de demod = ");
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

    case 'a': // altear mux para padrão de injeção 1-2
      wire_envia_byte(0X60, 1);
      wire_envia_byte(0X61, 2);
      Serial.println("Injetando nos eletrodos 1 e 2");      
      break;
     
    case 'b': // altear mux para padrão de injeção 2-3
      wire_envia_byte(0X60, 2);
      wire_envia_byte(0X61, 3);
      Serial.println("Injetando nos eletrodos 2 e 3");      
      break;

    case 'c': // altear mux para padrão de injeção 3-4
      wire_envia_byte(0X60, 3);
      wire_envia_byte(0X61, 4);
      Serial.println("Injetando nos eletrodos 3 e 4");      
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

    case 'p': // interromper leitura continua
      flag_leitura_continua = false;
      flag_leitura_continua_limpa = false;
      flag_envia_impedancia = false;
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
      
    case 't': // diminui nro de pontos
      if(n_pontos_mult>1){
        n_pontos_mult = n_pontos_mult-1;
        envia_comando_todos('t');
        tempo_demodulacao = 1+(n_pontos_base*n_pontos_mult)/4;
      }
      else Serial.print("Nro de pontos minimo atingido. ");
      Serial.print("Npontos = ");
      Serial.print(n_pontos_base*n_pontos_mult);
      Serial.print("; npontos_base = ");
      Serial.print(n_pontos_base);
      Serial.print("; n_pontos_mult = ");
      Serial.print(n_pontos_mult);
      Serial.print("; tempo_demodulacao = ");
      Serial.println(tempo_demodulacao);
      break;
      
    case 'y': // aumenta nro de pontosNUM_SAMPLES_MAX
      if(((n_pontos_mult+1)*n_pontos_base) < NUM_SAMPLES_MAX){
        n_pontos_mult = n_pontos_mult+1;
        envia_comando_todos('y');
        tempo_demodulacao = 1+(n_pontos_base*n_pontos_mult)/4;
      }
      else Serial.print("Nro de pontos maximo atingido. ");
      Serial.print("Npontos = ");
      Serial.print(n_pontos_base*n_pontos_mult);
      Serial.print("; npontos_base = ");
      Serial.print(n_pontos_base);
      Serial.print("; n_pontos_mult = ");
      Serial.print(n_pontos_mult);
      Serial.print("; tempo_demodulacao = ");
      Serial.println(tempo_demodulacao);
      break;
      
    default:
      break;
  }
}

void wire_envia_byte(byte endereco, byte com) {
    Wire.beginTransmission(endereco);
    Wire.write(com);
    Wire.endTransmission();    
}
