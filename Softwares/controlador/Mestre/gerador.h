//#Autor: Gustavo Pinheiro

//-----------------------------------------DigiPot1-------------------------------------//

// Saidas digitais
#define inc_outPin PB11 // INC(DigPot1)
#define ud_outPin PB10  // U/D(DigPot1)
#define cs_digpot1 PB1   // CS do DigPot 1, usado para salvar a ultima resistencia obtida

#define RS_LIMITE 18 // valor máximo de Rs para não saturar o circuito, equilave a ganho mínimo de 2,8x. Confirmar...
#define RS_MAX   100 // Valor máximo ajustável no digipot
#define RS_INT  0.04 // Resistência interna do digipot

float Rs = 1; //valor do resistor variavel
float Rf = 51; //valor do resistor de feedback (kOHM)
int Vin = 1.1; //tensao PcPc do gerador ad9850

const int loopPeriod = 20; // tempo de espera enrte envios de sinais do Digipot.
                           // testar qual o menor valor possível

///////////////// FUNCOES DIGIPOT /////////////////////

float ganho(){
  return (Rf/(Rs+RS_INT));
}

// Controla o digipot, mininuindo o valor da resistência
// Diminui um passo do digipot; para o X9C104 um passo equivale a 1kohm
void wiper_down(){ //wiper down -> aumenta o ganho
  digitalWrite(ud_outPin, LOW);
  delay(loopPeriod);
  digitalWrite(inc_outPin, LOW);
  delay(loopPeriod);
  digitalWrite(inc_outPin, HIGH);
  delay(loopPeriod);
  digitalWrite(ud_outPin, HIGH);
  delay(loopPeriod);
  Rs = Rs-1;
  if (Rs < 0) Rs = 0;
}

// Controla o digipot, aumentando o valor da resistência
// Aumenta um passo do digipot; para o X9C104 um passo equivale a 1kohm
void wiper_up(){ //wiper up -> diminui o ganho
  //digitalWrite(ud_outPin, HIGH);
  //delay(loopPeriod);
  digitalWrite(inc_outPin, LOW);
  delay(loopPeriod);
  digitalWrite(inc_outPin, HIGH);
  delay(loopPeriod);
  Rs = Rs + 1;
  if (Rs > RS_MAX) Rs = RS_MAX;
}

// Dá problema com Rs > 18kohms. Verificar porque...
void diminui_ganho(){ //wiper up
    if (Rs < RS_LIMITE){
        wiper_up();
    }
    #ifdef DEBUG
      else Serial.println("ganho minimo atingido");    
    #endif
}

// Dá problema com Rs > 18kohms. Verificar porque...
void aumenta_ganho(){ //wiper up
    if (Rs > 0){
        wiper_down();
    }
    #ifdef DEBUG
      else Serial.println("ganho máximo atingido");    
    #endif
}

// Inicializa digipot diminuindo 100 passos e aumentando RS_MAX passos (ganho mínimo)
void inicia_digpot(){
  for (int i = 0; i <= 100; i++) {
        wiper_down(); // -> ganho máx
  }
  for (int i = 0; i < RS_LIMITE; i++) {
        wiper_up();  // -> ganho mín
  }
}

void ganho_minimo(){
  while (Rs < RS_LIMITE){
    diminui_ganho();
    #ifdef DEBUG
      Serial.println("Configurando ganho minimo...");
    #endif
  }
  #ifdef DEBUG
    Serial.println("ganho minimo atingido");  
  #endif
}

void ganho_maximo(){
    while (Rs > 0){
      aumenta_ganho();
      #ifdef DEBUG
        Serial.println("Configurando ganho maximo...");
      #endif
    }
    #ifdef DEBUG
      Serial.println("ganho maximo atingido");  
    #endif
}

// Inicializa pinos e ajusta Rs para ganho mínimo
void gerador_setup() {
    pinMode(inc_outPin, OUTPUT);
    pinMode(ud_outPin, OUTPUT);
    pinMode(cs_digpot1, OUTPUT);

    digitalWrite(inc_outPin, HIGH);
    digitalWrite(ud_outPin, HIGH);
    digitalWrite(cs_digpot1, LOW);

    delay(loopPeriod);
    inicia_digpot();
}
