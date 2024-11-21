/*
 * Funções relacionadas com o controlador Mestre do tomografo EIT - placa 'Gerador de sinais AD9850 v01'
 * Autor: Gustavo Pinheiro
*/


////////////DIGPOT - Controle da amplitude do sinal ////////////
// Saidas digitais
#define inc_outPin PB11 // INC(DigPot1)
#define ud_outPin PB10  // U/D(DigPot1)
#define cs_digpot1 PB1   // CS do DigPot 1, usado para salvar a ultima resistencia obtida

const int loopPeriod = 50;
////////////////////////////////////////////////////////////////


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

// pega a amplitude e fase da corrente monitorada no ina???
void pega_leitura_de_um_eletrodo(byte endereco, float *amplitude, float *fase){
  Wire.requestFrom(endereco, 8);

  binaryFloat amplitude_lida, fase_lida;
  for(byte idx = 0; idx < 4; idx++) amplitude_lida.binary[idx] = Wire.read();

  for(byte idx = 0; idx < 4; idx++) fase_lida.binary[idx] = Wire.read();

  *amplitude = amplitude_lida.floatingPoint;
  *fase = fase_lida.floatingPoint;
}
