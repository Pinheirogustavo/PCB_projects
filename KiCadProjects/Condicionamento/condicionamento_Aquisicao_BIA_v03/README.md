# Circuito de condicionamento e aquisição de sinal

## Descrição Geral do projeto

Sistema projetado para permitir a aquisição de sinais por meio dos dois ADCs presentes em cada microcontrolador STM32.

Estágios: Sinais a serem condicionados &rarr; buffer &rarr; offset (valor médio do limite de entrada do ADC) &rarr; diodos de proteção ( limites de entrada do ADC) &rarr; Filtro anti-aliasing &rarr; sinal condicionado &rarr; ADC@STM32

## Sinais do circuito:

- AmplI1: Tensão de saída **já condicionada** do INA que monitora a corrente I1
- Amp_E1: Tensão medida pelo eletrodo proximal do pé/mão
- Amp_E2: Tensão medida pelo eletrodo proximal do pé/mão
	
	
##Cuidados a serem tomados

O conjunto de pinos **Vref** permite selecionar sinais e 3.3V e 5.0V. A escolha do sinal deve ser adequada ao limite de entrada dos pinos ADCs do microcontrolador utilizado. Para o STM32 esse limite é de 3.3V.

Todos os sinais que são enviados aos pinos de ADCs dos microcontroladores devem estar devidamente condicionados.

Sobre a alimentação dos microcontroladores: O par de pinos "alimentacao_Master" fornece uma alimentação de +5V  ao Master quando é fechado. Esse  par de pinos deve permanecer aberto quando o microcontrolador Master estiver conectado ao computador por meio de cabo USB, pois o pino de 5V do STM32 é diretamente conectada à alimentação fornecida por USB, sem qualquer circuito de proteção. O microcontrolador Slave está sempre conectado à alimentação de 5V do sistema. Somente conecte esse dispositivo ao computador se o sistema estiver desligado. 

## Estágios do circuito

#### Circuito de condicionamento

O circuito de condicionamento permite a adequada aquisição de sinal por meio de microcontrolador, garantindo que os sinais aplicados nas entradas do dispositivo não ultrapassem os limites de tensão e corrente suportados, além da adequada amostragem do sinal, por meio de filtro anti-aliasing. Esse circuito emprega o amplificador operacional dual AD826/828, o que permite o condicionamento de dois canais. Os estágios do circuito são: 

- buffer: amplificador operacional no modo seguidor, configuração de alta impedância de entrada que permite o adequado acoplamento entre os estágios do sistema, minimizando a interação entre eles.

- Offset: estágio que realiza um deslocamento (offset) do sinal de entrada, adequando os sinais alternados de correntes do circuito aos ADCs do microcontrolador, adicionando um sinal DC equivalente ao valor médio do limite de entrada dos ADCS. O valor de Vref deve ser definido pelo operador de acordo com esse limite.


- Diodos de proteção: não permitem que o sinal de entrada ultrapasse  os limites de entrada do conversor ADC. O valor de Vref deve ser definido pelo operador de acordo com esse limite.

- filtro anti-alising: Frequência de corte $F_c$:

$$F_c = \frac{1}{2\cdot\pi\cdot R\cdot C} = \frac{1}{2\cdot\pi\cdot220\cdot470\cdot10 ^{-12}} = 1,5 MHz$$


#### Microcontroladores

Dois microcontroladores são empregados nesse sistema de BIA, permitindo a leitura de 4 canais de medição. A comunicação entre eles é feita por meio do protocolo I2C. Ambos leem o sinal de amplitude da corrente medida pelo INA (AmpI1) em seus ADCs.

- STM32 Master

O par de pinos "alimentacao_Master" fornece uma alimentação de +5V quando é fechado. Esse  par de pinos deve permanecer aberto quando o microcontrolador estiver conectado ao computador por meio de cabo USB, pois o pino de 5V do STM32 é diretamente conectada à alimentação fornecida por USB, sem qualquer circuito de proteção.

> ADC1: Pino B0 recebe o sinal de amplitude de corrente AmpI1

> ADC2: Pino B1 recebe o sinal de amplitude de tensão do eletrodo de medição E1.

- STM32 Slave

O microcontrolador está sempre conectado à alimentação de 5V do sistema. Somente conecte esse dispositivo ao computador se o sistema estiver desligado. 

> ADC1: Pino B0 recebe o sinal de amplitude de corrente AmpI1

> ADC2: Pino B1 recebe o sinal de amplitude de tensão do eletrodo de medição E2.




## Esquemático

![Legenda Esquematico- Kicad](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Condicionamento/condicionamento_Aquisicao_BIA_v01/prints/Condicionamento_aquisicao_BIA_esquematico.png)


## PCB

![Legenda  PCB- Kicad](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Condicionamento/condicionamento_Aquisicao_BIA_v01/prints/Condicionamento_aquisicao_BIA_PCB.png)

## PCB-3D

![legenda PCB 3D - Kicad](link)

## PCB Máscara

![legenda PCB Máscara - Kicad](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Condicionamento/condicionamento_Aquisicao_BIA_v01/prints/Condicionamento_aquisicao_BIA_mascara.png)

