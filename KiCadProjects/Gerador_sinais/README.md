# Gerador de Sinais

## Descrição Geral do projeto

Sistema que gera um sinal senoidal com controle de amplitude e frequência.

Estágios: Gerador de sinais ( CA@300mV + DC) &rarr; Filtro  passa-alta &rarr; SinA (CA@300mV) &rarr; buffer &rarr;  amplificador não-inversor &rarr; Sin1(CA@300mV-3V)

## Componentes do circuito:

- Arduino nano: controlador do sistema
- AD9833: gerador de sinais confeccionado em módulo. Gera uma onda senoidal de amplitude fixa de 300mA e offset
- Ad828: Amplificador operacional dedicado ao ganho de sinal. 
	>Amplificador 1 é buffer entre o filtro passa-alta e o circuito de ganho.
	>Amplificador 2 é um amplificador não inversor. Vout = (1+pot/R2)*Vin
- X9c10x: potenciometro digital dedicado ao ganho de sinal

## Estágios do circuito

#### Entradas e saídas digitais do arduino nano:
>D2:  cs (X9X104) - Sinal de Chip Select do potenciômetro digital - Botão 4 (pulldown) "The device is selected when the CS input is LOW." - Pressionar o botão faz o sinal passar de LOW para HIGH. Usado para armazenar o valor de resistência.

>D4:  cs (AD9833) - Sinal de Chip Select do gerador de sinais

>D5:  Up_pot - Aumenta a resistência do potenciômetro (aumenta o ganho do sistema) - Botão 5 - Pressionar o botão faz com que o sinal de X9c10x_INC altere de HIGH para LOW e o sinal  X9c10x_U/D fique em HIGH
	
>D6:  Down_pot - Reduz a resistência do potenciômetro (reduz o ganho do sistema) - Botão 6 - Pressionar o botão faz com que o sinal de X9c10x_INC altere de HIGH para LOW e o sinal  X9c10x_U/D fique em LOW

>D7:  X9c10x_INC - Saída digital. Responsável pelo disparo do sinal que habilita o incremento e o decremento da resistência. Alterado pelos sinais em Up_pot/Down_pot.

>D8:  X9c10x_U/D -  Saída digital. Responsável pela seleção do sinal de incremento ou decremento da resistência. Controlado pelos sinais em Up_pot/Down_pot.

>D9:  freq+   - Incrementa a frequência do sinal (a definir o tamanho do incremento) - Botão 2 - Ainda não implementado no programa.

>D10: freq-   - Decrementa a frequência do sinal (a definir o tamanho do decremento) - Botão 3 - Ainda não implementado no programa.

>D11: SPI_COPI - Saída digital. Sinal de controle do arduino para a entrada SDATA do gerador de sinais.

>D12: S_wave - Seleciona a forma de onda desejada (seno, triangular ou quadrada) - Botão 1 - Ainda não implementado no programa.

>D13: SPI_clk - Saída digital. Sinal de clock entre o arduino e o gerador de sinais


#### O potenciômetro digital

- Programa baseado em: https://www.electroniclinic.com/digital-potentiometer-x9c103s-arduino-circuit-and-programming/

- Pin Descriptions - X9c10x:

![Pin Descriptions - X9c10x](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Gerador_sinais/Datasheets/Digital-Potentiometer-X9C103s-Mode-selection.jpg)


#### O Gerador de sinais

- Programa baseado em: https://www.electroniclinic.com/ad9833-programmable-waveform-generator-using-arduino/
- Biblioteca necessária: https://github.com/Billwilliams1952/AD9833-Library-Arduino

## Esquemático

![Esquemático Gerador de sinais - Kicad](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Gerador_sinais/print/Gerador_sinais_esquematico.png)



