//Baseado em: https://github.com/Silvio8989/Equipamento-de-tomografia-por-impedancia-eletrica-escalavel-e-de-baixo-custo-para-uso-didatico/tree/main/C%C3%B3digos/Seguidor/Mux_Entrada/Mux_Entrada.ino

#include <Wire_slave.h>
#include "demux.h"

#define MEU_ENDERECO 0x60 //define endereco i2c do uC que controla o grupo de muxs
#define LED PC13 //Led verde do uC stm32, usado para indicar determinadas acoes do uC

byte comando = 0;
long int contador = 0;

//#define debug

#if defined debug

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

void imprime_canais(){
  if(comando <= 0x7F){
    Serial.print("input current ");
    Serial.print("channel ");
    Serial.println(comando);
    Serial.print(A);
    Serial.print(B);
    Serial.print(C);
    Serial.print(D);
    Serial.println(E);
  }

  if (comando > 0x7F && comando < 0xFF ){
    comando = comando-0x80;
    Serial.print("Output current ");
    Serial.print("channel ");
    Serial.println(comando);
    Serial.print(A);
    Serial.print(B);
    Serial.print(C);
    Serial.print(D);
    Serial.println(E);
    }
}

testa();
imprime_canais();

#else
       //
#endif

//recebe o comando por meio do barramento i2c
  //e chama a funcao 'configura_pinos_mux' para configurar a gpio do uC de controle da multiplexacao
void dadorecebido(int howmany){
  comando = Wire.read();  
  if(comando == 0) comando = 0xFF;
  configura_pinos_mux(); //chama a funcao para desligar todos os mux entre cada comando; depois implementar: nova funcao que apenas desabilita os muxs
}

//avalia o comando recebido pelo i2c
    //se 'comando' entre 0 e 127 -> indica o eletrodo de injecao de corrente
    //se 'comando' entre 128 e 255 -> indica o eletrodo de drenagem de corrente
void processacomando(){
  contador = 0;
  Serial.print("recebi comando "); //debug
  Serial.println(comando, HEX);  //debug
  if(comando <= 0x7F) seleciona_canal_in(comando);
  if (comando > 0x7F && comando < 0xFF ){
          comando = comando-0x80;
          seleciona_canal_out(comando);
  }
//  comando = 0;
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
