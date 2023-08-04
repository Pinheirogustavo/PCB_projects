# Fonte de tensão

## Versão atual em protótipo: 03

## Descrição Geral do projeto

Sistema que a partir de uma fonte de tensão comum gera uma fonte de tensão simétrica com diferentes saídas de tensões reguladas para alimentação de todo o EITduino.

Estágios: Fonte de tensão comum ($\geqslant$ 24V) &rarr; Terra virtual &rarr; saída simétrica não regulada VCC VEE &rarr;
	> Saídas reguladas simétricas para alimentação analógica: +9V/-9V 
	> Saídas reguladas; +5V/-5V
	> Saída regulada:+3.3V

## Componentes do circuito:

- LM675
- LM78XX
- LM79XX
- LM117T-3.3
	
	
## Cuidados a serem tomados

Os reguladores da série 78XX podem ser agrupados em um único dissipador, o mesmo vale para os reguladores da série 79XX. Todos os outros dissipadores devem ser mantidos afastados pois suas carcaças não se encontram no mesmo potencial do sistema. 

O AmpOp LM675 apresenta elevada dissipação de energia, sempre utilize um dissipador de calor. 

## Estágios do circuito

#### Terra virtual

O terra virtual é feito com o amplificador operacional LM675, que fornece uma corrente máxima de 1,5A. Sua saída é simétrica em VCC +(MaxTensao da fonte utilizada / 2) e em VEE -(MaxTensao da fonte utilizada / 2).

Essas tensões não são reguladas, sofrendo oscilações e não devem ser utilizadas para alimentação de outros subsistemas do EITduino.


#### Reguladores 78XX

Reguladores de tensão positivos que também fornecem corrente máxima de 1,5A. São utilizados CIs que fornecem +9V e +5V.

#### Reguladores 79XX

Reguladores de tensão negativos que também fornecem corrente máxima de 1,5A. São utilizados CIs que fornecem -9V e -5V.

#### Regulador LM117T-3.3

Regulador de tensão positivo que  fornece corrente máxima de 800mA. Fornece +3.3V.




