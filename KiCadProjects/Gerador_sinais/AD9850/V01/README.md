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

###### A2 - Encoder

###### A3 - Teclado matricial

###### A4 - botões

###### B1 - AD9850

###### C1 - Filtro saída AD9850

###### B2 - uC STM32

###### C1 e D1 - Barramento principal

###### C3 - LEDs de alimentação

###### A5 e B5 - Ganho programável

###### C5 - Filtro e buffer

## Particularidades na construção da PCB

Devido o tamanho restrito da placa e o grande número de componentes, foram adotados tamanhos de trilha e espaçamentos diferentes dos padrões.

 - Tamanho de trilha: 0,50mm
 - Espaçamento: 0,50mm

