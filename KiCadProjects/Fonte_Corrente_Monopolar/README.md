# Fonte de corrente monopolar

## Descrição Geral do projeto

Fonte de corrente monopolar do tipo Howoland aperfeiçoada. O Sistema é excitado por um sinal senoidal e fornece uma corrente alternada de amplitude constante frente uma banda de resistências. Há um sistema de monitoramento da amplitude da corrente (Ampl1) que é implementado com um circuito de condicionamento dedicado.

Estágios Fonte de Corrente: Sinal de entrada(Sin1 ou SinA) &rarr; buffer &rarr; arquitetura fonte Howland &rarr; Resistor Sentinela//Amplificador de Instrumentação &rarr;  corrente I1.

Estágios monitoramento: Amplificador de Instrumentação &rarr; AmpOp &arrar; circuito de condicionamento &rarr; amplitude da corrente Ampl1.

## Componentes do circuito:

- Amplificador Operacional Dual AD826/828: Amplificador operacional duplo implementado como buffer na entrada do sistema e de acordo com a arquitetura da fonte Howland aperfeiçoada.
	>Amplificador 1: buffer.
	>Amplificador 2: arquitetura da fonte Howland aperfeiçoada.
- Resistor sentinela: Resistor de baixa resistência em série com a saída da fonte Howland. Implementado para monitorar a corrente gerada.
- Amplificador de Instrumentação INA: Amplificador de Instrumentação verifica a tensão sobre o resistor sentinela e aplica alto ganho fixo. A tensão de saída é condicionada e indica a amplitude da corrente (Ampl1).  Implementado para monitorar a corrente gerada. 
- Circuito de condicionamento: Condiciona o sinal para os limites do ADC do controlador (Selecionado com jumpers nos pinos "Vref" 3.3/5V). 



##Cuidados a serem tomados


## Estágios do circuito

#### XX:

>XX

>XX





## Esquemático

![Fonte de corrente howland aperfeiçoada monopolar - Kicad](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Fonte_Corrente_Monopolar/prints/Fonte_corrente_monopolar_esquematico.png)


