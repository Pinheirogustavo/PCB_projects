//Baseado em: https://github.com/Silvio8989/Equipamento-de-tomografia-por-impedancia-eletrica-escalavel-e-de-baixo-custo-para-uso-didatico/tree/main/C%C3%B3digos/Seguidor/Mux_Entrada/Mux_Entrada.ino

/*COMANDOS DISPONÍVEIS NA PLACA DE DEMUX
 * QUE PODEM SER ENVIADOS A PARTIR DA PLACA DO CONTROLADOR PARA ESSA PLACA
 * 
 * 6000 - Desliga os MUX
 * 
 * 6001 - Conecta o I1 da fornte de corrente ao E0
 * 6002 - Conecta o I1 da fornte de corrente ao E1
 * ... Segue a logica de que o eletrodo En será conectado a I1 quando o o comando enviado for 6000 + n +1
 * 6127 - Conecta o I1 da fornte de corrente ao E126
 * 
 * 
 * 6128 - Conecta o I2 (no caso da fonte de corrente bipolar) ou terra (no caso da fonte de corrente monopolar) ao E0
 * 6129 - Conecta o I2 (no caso da fonte de corrente bipolar) ou terra (no caso da fonte de corrente monopolar) ao E1
 * ... Segue a logica de que o eletrodo En será conectado a I2/Terra quando o o comando enviado for 6000 + n +128
 * 6255 - Conecta o I2 (no caso da fonte de corrente bipolar) ou terra (no caso da fonte de corrente monopolar) ao E127
 * 
 * 
 * Esse codigo permite que ate 126 eletrodos possam ser usados como injetores da corrente I1 e até 127 eletrodos possam ser usados como injetores da corrente I2 (Terra). 
 */




#include <Wire_slave.h>
#include "demux.h"
//#include <stm32f1xx_hal_rcc.h>

#define DEBUG 0
#define MEU_ENDERECO 0x06 //define endereco i2c do uC que controla o grupo de muxs
#define SLAVE_ADDRESS 0x06 //define endereco i2c do uC que controla o grupo de muxs
#define LED PC13 //Led verde do uC stm32, usado para indicar determinadas acoes do uC

byte comando = 0;
long int contador = 0;
byte aux1 = 65;
byte aux2 = 98;
int x = 0;
int nerr = 9;

void receiveEvent(int howMany) {
  x = Wire.read();  // receive byte as an integer porque o x eh um inteiro
  
  if ((x>0)&&(x<128)){ //a entrada deve ser alterada
    aux1 = x;
    nerr = 2;
    #ifdef DEBUG
      Serial.print("recebi comando para alterar a entrada "); //debug
      Serial.println(aux1);  //debug
      Serial.print("canal selecionado "); //debug
      Serial.println(aux1-1);  //debug
    #endif
    if ((aux2-128) == (aux1-1)){
      nerr = 0;
      #ifdef DEBUG
        Serial.print("Canal ja selecionado para saida"); //debug
      #endif
    }
    else{
      seleciona_canal_in(aux1-1);
    }
    
  }
  else if ((x>127)&&(x<256)){ //a saida deve ser alterada
    aux2 = x;
    nerr = 3;
    #ifdef DEBUG
      Serial.print("recebi comando para alterar a saida "); //debug
      Serial.println(aux2);  //debug
      Serial.print("canal selecionado "); //debug
      Serial.println(aux2-128);  //debug
    #endif
    if ((aux2-128) == (aux1-1)){
      nerr = 0;
      #ifdef DEBUG
        Serial.print("Canal ja selecionado para entrada"); //debug
      #endif
    }
    else{
        seleciona_canal_out(aux2-128);
    } 
  }
  else if (x==0){
    configura_pinos_mux();
    nerr = 4;
    #ifdef DEBUG
      Serial.println("Zeradas as entradas e saidas"); //debug
    #endif
  }
  else if (x==999){
    configura_pinos_mux();
    nerr = 5;
  }
  else{
    nerr = 0;
    #ifdef DEBUG
      Serial.println("Nao reconhecido"); //debug
    #endif
  }
  
}

void requestEvent(){
  
  byte dataBuffer[] = {SLAVE_ADDRESS, x, nerr};
  Wire.write(dataBuffer, sizeof(dataBuffer));
}

void setup() {
  disableDebugPorts();// permite utilizar os pinos B3, B4 e A15 como GPIO, mover BOOT0 para 1 para poder gravar
  Wire.begin(MEU_ENDERECO); //Endereço do MUX
  Wire.onReceive(receiveEvent);    // chama uma funcao qualquer quando algum dado eh recebido pelo i2c
  Wire.onRequest(requestEvent);  // registra um evento para tratar requisicoes
  pinMode(LED, OUTPUT);
  delay (3000);
  digitalWrite(LED, HIGH);
  configura_pinos_mux();
  Serial.begin(9600);

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
  if (Serial.available() > 0) {
      String incomingString = Serial.readStringUntil('\n');// read the incoming string:
      Serial.print("Eu recebi na Serial: ");
      Serial.println(incomingString);// prints the received data
      comando = incomingString.toInt();
      Serial.print("Comando: ");
      Serial.println(comando);
   }
  
     
  
  //delay(50);                 // adiciona um delay de 50 ms
  //digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(50);                 // adiciona um delay de 50 ms
  //digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
}

/*void requestEvent(){
    if (x == 48){
      nerr = 1;
      x = auxfreq1;}
    else if (x == 49){
      nerr = 1;
      x = auxfreq2;}
  
  byte dataBuffer[] = {SLAVE_ADDRESS, comando,1};
  Wire.write(dataBuffer, sizeof(dataBuffer));
}*/
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
