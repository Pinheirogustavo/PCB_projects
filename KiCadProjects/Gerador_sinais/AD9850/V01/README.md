# Gerador de Sinais

## Descrição Geral do projeto

O gerador de sinais é baseado no AD9850. São gerados dois sinais senoidais e dois sinais quadrados, com banda de frequência entre 1 Hz e 40 MHz.

 - Sinais Senoidais: Controle de amplitude e frequência;
 - Sinais quadrados: Controle de frquência.
 
 
## Descrição do sistema

#### Gerador de sinais AD9850

O gerador é controlado por quatro sinais digitais vindos do uC STM32. Sua alimentação é feita pelo barramento principal com 5V.

Os sinais quadrados SQ_AD1 e SQ_AD2 passam por um filtro passivo de primeira ordem passa alta, com frequência de corte de 10 Hz. Esses sinais ficam disponíveis na barra de pinos "Squad_wave" como SQ1 e SQ2.

Os sinais senoidais sin_AD1 e sin_AD2 passam por um filtro passivo de primeira ordem passa alta, com frequência de corte de 10 Hz. Esses sinais ficam disponíveis no barramento principal  como Sin1 e Sin2.

#### Circuito de ganho

Os sinais Sin1 e Sin2 entram em um Amplificador Inversor, com o resistor de entrada sendo um potenciômetro digital X9c10x e o resistor de feedback de 51k. O amplificador usado é o AD826/828. 

O controle de cada potenciômetro digital é feito por três sinais digitais vindos do uC STM32. Sua alimentação é feita pelo barramento principal com 5V.

Os sinais Sin1 e Sin2, após passarem por esse estágio de ganho, são nomeados por Sin1_gain e Sin2_gain, respectivamente.

#### Filtro pós ganho

Em simulações realizadas foi observado offset nos sinais após a realização do ganho. Por esse motivo, foi adicionado um estágio, opcional, de filtro Passa-Alta e buffer. Os sinais Sin1_gain e Sin2_gain entram nesse estágio e saem nomeados como Sin1_filter e Sin2_filter

#### Seleção dos sinais para SinA e SinB

O barramento principal do Eitduino recebe os sinais SinA e SinB. Estes podem ser selecionados a partir de  Sin_gain ou Sin_filter por meio de pinos "Select_SinA" e "Select_sinB".

#### Opções de controle por entradas digitais

###### Botões

Quatro botões podem ser implementados para controle de frequência e amplitude do sinal senoidal. Eles são conectados a entradas digitais do uC STM32 (que devem ser definidas como pullup).

###### Teclado matricial

Um teclado matricial 4x4 pode ser implementado para realizar os controles de  frequência e amplitude do sinal senoidal. Esses modelos de teclados numéricos geralmente possuem resistores pullup internos.

###### Encoder

Um encoder pode ser implementado para realizar os controles de  frequência e amplitude do sinal senoidal, em conjunto com os sinais vindos dos botões ou do teclado matricial. Um modelo de fácil acesso é o KY-040, de 20 steps por revolução.

## Descrição do esquemático

###### A1 - Squad Wave

Componentes para filtrar e disponibilisar os dois sinais quadrados.

 > Os sinais quadrados que saem do AD9850, SQ_AD1 e SQ_AD2, passam por um filtro PA e saem como SQ1 e SQ2.
 > SQ1 e SQ2 ficam disponíveis em uma barra de pinos (Squad_wave) junto com o AGND.

###### A2 - Encoder

Barra de pinos (encoder ky-040) para encaixe do módulo encoder como o KY-040. 

 > O módulo encoder trabalha com cinco pinos. +5V e DNGD para alimentação. Os outros três pinos são sinais digitais (En1, En2 e En3) que enviam dados para o uC.
 
 As conexões entre o encoder e o uC são:
    - En1       PA15
    - En2       PB8
    - En3       PB9

###### A3 - Teclado matricial

Barra de pinos (teclado matricial) para conexão do teclado matricial 4x4.

 > São oito pinos de sinais digitais (M1, M2, ... , M8) que enviam dados para o uC.

As conexões entre o teclado e o uC são:
    - M1        PA2
    - M2        PA3
    - M3        PA12
    - M4        PA11
    - M5        PA6
    - M6        PA7
    - M7        PB0
    - M8        PB12

###### A4 - botões

Barra de pinos (botoes_selecao) para conexão de 4 botões.

 > São quatro pinos para conexão de botões e um pino DGND. Os quatro pinos dos botões são:
    - Freq +: incrementa a frequência dos sinais gerados
    - Freq -: decrementa a frequência dos sinais gerados
    - Up_gain: incrementa a amplitude dos sinais gerados
    - Down_gain: decrementa a amplitude dos sinais gerados
    
As conexões entre os botoes e o uC são:
    - Freq+         PB13
    - Freq-         PB14
    - Up_gain       PB15
    - Down_gain     PA8
    
 > Os botões devem ser conectados ao sinal DGND presente na barra de pinos  e nas entradas digitais do uC. Essas entradas devem estar definidas com pullup. 

###### B1 - AD9850

Modelo de componente criado nas dimensões do módulo utilizado.

As conexões entre o módulo e o uC são:
    - W_CLK     PC14
    - FQ_UD     PC15
    - DATA      PA0
    - RESET     PA1
    
Os sinais senoidais (com offset) fornecidos são: sin_AD1 e sin_AD2

A alimentação é feita por: +5V e DGND

###### C1 - Filtro saída AD9850

###### B2 - uC STM32

Alimentação: pode ser feita por 3.3V ou 5.0V - jumper na barra de pinos (3.3V STM32 **OU** 5.0V STM32).

Entradas Digitais: Ver "Encoder", "Teclado matricial" e "Botões".

Saídas digitais: Ver "AD9850" e "DigPot1 / DigPot2" em "Ganho programável".

Entradas Analógicas:
    - PA4       Ampl1 (amplitude da corrente I1 - vinda do barramento principal)
    - PA5       Ampl2 (amplitude da corrente I2 - vinda do barramento principal)

Comunicação I2C: O uC está conectado ao barramento principal de comunicação I2C-1. No primeiro momento essa funcionalidade não é utilizada, mas foi implementada caso optemos por realizar o controle do sinal de excitação por outro uC de outro módulo do projeto. 
Há resistores pullup (+3.3V) para essa comunicação.

###### C1 e D1 - Barramento principal

Verificar os sinais dispo no barramento principal em: <https://github.com/Pinheirogustavo/PCB_projects>

###### C3 - LEDs de alimentação

LEDs de diferentes cores para indicar o correto fornecimento das tensões empregadas no circuito.

Foi considerado uma tensão de joelho de aproximadamente 3V e uma corrente de 5mA para ter o um brilho perceptível e baixo consumo de energia.

 - Azul:        +9V
 - Vermelho:    -9V
 - Verde:       +5V
 - Amarelo:     +3.3V

###### A5 e B5 - Ganho programável

Amplificador duplo (AD826/828) na forma não inversor para controle do ganho do sinal senoidal filtrado vindo do AD9850.

Cada um dos sinais (Sin1 e Sin2) passa por um potenciômetro digital diferente (DIgPot 1 e DigPot2). Ambos estão conectados à entrada não inversora do amplificador. 

Cada potenciômetro digital (DigPot) possui um vetor resistivo de 99 passos. O CI X9c104 possui resistência máxima de 100k \Omega. Ele é controlado por 4 sinais digitais.

As conexões entre os potenciômetros digitais e o uC são:
    - Pot1_CS_(X9c104)      PB1
    - Pot1_X9c10x_U/D       PB10
    - Pot1_X9c10x_INC       PB11
    
    - Pot2_CS_(X9c104)      PB5
    - Pot2_X9c10x_U/D       PB4    
    - Pot2_X9c10x_INC       PB3    
    
![Sinais controle potenciômetro digital](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Gerador_sinais/Datasheets/Digital-Potentiometer-X9C103s-Mode-selection.jpg)

###### C5 - Filtro e buffer

## Particularidades na construção da PCB

Devido o tamanho restrito da placa e o grande número de componentes, foram adotados tamanhos de trilha e espaçamentos diferentes dos padrões.

 - Tamanho de trilha: 0,50mm
 - Espaçamento: 0,50mm
 - Tamnho de via: 1,00mm furo da via: 0,60mm

