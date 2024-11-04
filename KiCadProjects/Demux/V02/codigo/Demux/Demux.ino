//Baseado em: https://github.com/Silvio8989/Equipamento-de-tomografia-por-impedancia-eletrica-escalavel-e-de-baixo-custo-para-uso-didatico/tree/main/C%C3%B3digos/Seguidor/Mux_Entrada/Mux_Entrada.ino

#include <Wire_slave.h>
//#include <stm32f1xx_hal_rcc.h>

#define MEU_ENDERECO 0x60 //define endereco i2c do uC que controla o grupo de muxs


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

#define LED PC13 //Led verde do uC stm32, usado para indicar determinadas acoes do uC

byte comando = 0;

long int contador = 0;




/*
void testa(){
  for(int iii=1;iii<30;iii++){
    delay(50);
    digitalWrite(A_S0, 0); // B5
    digitalWrite(A_S1, 0); // B4
    digitalWrite(A_S2, 0); // B3
    digitalWrite(A_S3, 0); // A15
    digitalWrite(A_S4, 0); // B9
    delay(50);
    digitalWrite(A_S0, 1); // B5
    digitalWrite(A_S1, 1); // B4
    digitalWrite(A_S2, 1); // B3
    digitalWrite(A_S3, 1); // A15
    digitalWrite(A_S4, 1); // B9
  }
}
*/

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

void dadorecebido(int howmany){
  comando = Wire.read();  
  if(comando == 0) comando = 0xFF;
  configura_pinos_mux(); //chama a funcao para desligar todos os mux entre cada comando; depois implementar: nova funcao que apenas desabilita os muxs
}

void processacomando(){
  //avalia o comando recebido pelo i2c
    //se 'comando' entre 0 e 127 -> indica o eletrodo de injecao de corrente
    //se 'comando' entre 127 e 255 -> indica o eletrodo de drenagem de corrente
  contador = 0;
  Serial.print("recebi comando "); //debug
  Serial.println(comando, HEX);  //debug
  if(comando <= 0x7F) seleciona_canal_in(comando);
  if (comando > 0x7F && comando < 0xFF ){
          comando = comando-0x80;
          seleciona_canal_out(comando);
  }
  comando = 0;
}

void setup() {
  disableDebugPorts();// permite utilizar os pinos B3, B4 e A15 como GPIO, mover BOOT0 para 1 para poder gravar
  Wire.begin(MEU_ENDERECO); //Endereço do MUX
  Wire.onReceive(dadorecebido);    // chama uma funcao qualquer quando algum dado eh recebido pelo i2c
  pinMode(LED, OUTPUT);
  delay (3000);
  digitalWrite(LED, HIGH);
  configura_pinos_mux();
  Serial.begin(115200);
  Serial.println("Demux ok");
}

/* Sobre habilitar os pinos B3, B4 e A15 para uso como GPIO:
 * Os pinos B3(JTDI), B4(JTDO) e A15(JTRST) da placa STM32 estão definidos como funcao Control e estao relacionados com testes e depuracao d uC e a placa. Por isso estao sempre em sinal alto, mesmo que você defina esses pinos como saida e envie um sinal baixo.
 * Para poder utilizar esses pinos como saidas digitais, eh preciso adicionar a funcao 'disableDebugPorts()' na funcao setup.
 * Para conseguir gravar seu programa por meio do stlink, eh preciso alterar o BOOT0 para 1. Caso contrario, a ide ira retornar uma mensagem de erro relacionada com a identificacao do chip.
 * Para acessar o monitor serial da placa, eh preciso retornar o BOOT0 para 0.
 *
 *  help disableDebugPorts: Disable the JTAG and Serial Wire (SW) debug ports.You can call this function in order to use the JTAG and SW debug pins as ordinary GPIOs. http://docs.leaflabs.com/static.leaflabs.com/pub/leaflabs/maple-docs/0.0.10/lang/api/disabledebugports.html
 */


void loop() {
  contador = contador+1;
  if(comando!=0) processacomando();
  if(contador>10000) digitalWrite(LED, HIGH); // Verificação de funcionamento
  else digitalWrite(LED, LOW); // Verificação de funcionamento
}
