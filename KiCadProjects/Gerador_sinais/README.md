# Gerador de Sinais

### Descrição Geral do projeto

Sistema que gera um sinal senoidal com controle de amplitude e frequência.
Estágios: Gerador de sinais &rarr Filtro  passa-alta&rarr SinA &rarr buffer &rarr  amplificador não-inversor &rarr Sin1

### Componentes do circuito:

- Arduino nano: controlador do sistema
- AD9833: gerador de sinais confeccionado em módulo. Gera uma onda senoidal de amplitude fixa de 300mA e offset
- Ad828: Amplificador operacional dedicado ao ganho de sinal. 
	>Amplificador 1 é buffer entre o filtro passa-alta e o circuito de ganho.
	>Amplificador 2 é um amplificador não inversor. Vout = (1+pot/R2)*Vin
- X9c10x: potenciometro digital dedicado ao ganho de sinal

### Estágios do circuito

#### Entradas digitais do arduino nano:
>D2:  cs (X9X104) - Sinal de Chip Select do potenciômetro digital - Botão 4 (pulldown)

>D4:  cs (AD9833) - Sinal de Chip Select do gerador de sinais

>D5:  Up_pot - Aumenta a resistência do potenciômetro (aumenta o ganho do sistema) - Botão 5
	
>D6:  Down_pot - Reduz a resistência do potenciômetro (reduz o ganho do sistema) - BOtão 6

>D7:  X9c10x_INC

>D8:  X9c10x_U/D

>D9:  freq+   - Incrementa a frequência do sinal (a definir o tamanho do incremento) - Botão 2

>D10: freq-   - Decrementa a frequência do sinal (a definir o tamanho do decremento) - Botão 3

>D11: SPI_COPI -Sinal de controle do arduino para a entrada SDATA do gerador de sinais

>D12: S_wave -Seleciona a forma de onda desejada (seno, triangular ou quadrada) - Botão 1

>D13: SPI_clk - Sinal de clock entre o arduino e o gerador de sinais

#### O potenciômetro digital

- Programa de inspiração: https://www.electroniclinic.com/digital-potentiometer-x9c103s-arduino-circuit-and-programming/


#### O Gerador de sinais

- Programa de inspiração: https://www.electroniclinic.com/ad9833-programmable-waveform-generator-using-arduino/
- Biblioteca necessária: https://github.com/Billwilliams1952/AD9833-Library-Arduino
