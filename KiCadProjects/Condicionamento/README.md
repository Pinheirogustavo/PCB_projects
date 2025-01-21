# Placa de condicionamento de sinal

## Versões em produção (jlcpcb):condicionamento_compacto_V01a; condicionamento_compacto_V01b; condicionamento_Aquisicao_BIA_v03


## Descrição Geral do projeto

Circuito de condicionamento de sinal para aquisição por microcontrolador.

## Versões do projeto:

### condicionamento_compacto_V01

Circuito projetado para apenas condicionar o sinal de interesse para correta aquisição do microcontrolador utilizado, buscando não alterar nenhuma característica do sinal.

Estágios: Sinais a serem condicionados &rarr; buffer &rarr; offset (valor médio do limite de entrada do ADC) &rarr; diodos de proteção ( limites de entrada do ADC) &rarr; Filtro anti-aliasing &rarr; sinal condicionado &rarr; ADC@uC

O circuito de condicionamento permite a adequada aquisição de sinal por meio de microcontrolador, garantindo que os sinais aplicados nas entradas do dispositivo não ultrapassem os limites de tensão e corrente suportados, além da adequada amostragem do sinal, por meio de filtro anti-aliasing. Esse circuito emprega o amplificador operacional dual, o que permite o condicionamento de dois canais. Os estágios do circuito são:

- buffer: amplificador operacional no modo seguidor, configuração de alta impedância de entrada que permite o adequado acoplamento entre os estágios do sistema, minimizando a interação entre eles.

- Offset: estágio que realiza um deslocamento (offset) do sinal de entrada, adequando os sinais alternados de correntes do circuito aos ADCs do microcontrolador, adicionando um sinal DC equivalente ao valor médio do limite de entrada dos ADCS. O valor de Vref pode ser escolhido por um pino de entrada do circuito.

- Diodos de proteção: não permitem que o sinal de entrada ultrapasse  os limites de entrada do conversor ADC.

**ALTERAR LEVANDO EM CONTA OS OUTROS COMPONENTES**
- filtro anti-alising: Frequência de corte $F_c$:

$$F_c = \frac{1}{2\cdot\pi\cdot R\cdot C} = \frac{1}{2\cdot\pi\cdot220\cdot470\cdot10 ^{-12}} = 1,5 MHz$$
**ALTERAR LEVANDO EM CONTA OS OUTROS COMPONENTES**

### condicionamento_compacto_V02

Circuito projeto para, além de condicionar o sinal de interesse para os limites de operação do microcontrolador, aplicar um ganho ao sinal de interesse em busca de melhorar a relação sinal-ruído obtida.

Estágios: Sinais a serem condicionados &rarr; buffer &rarr; amplificador não inversor com variação da resistência de entrada por controle eletrônico  &rarr; offset (valor médio do limite de entrada do ADC) &rarr; diodos de proteção ( limites de entrada do ADC) &rarr; Filtro anti-aliasing &rarr; sinal condicionado &rarr; ADC@uC

### condicionamento_Aquisicao_BIA_v01

Circuito projetado para condicionamento e aquisição de apenas 4 canais para um Analisador de Bioimpedância.

### condicionamento_Aquisicao_BIA_v02

Circuito projetado para condicionamento e aquisição de apenas 4 canais para um Analisador de Bioimpedância.

### condicionamento_Aquisicao_BIA_v03

Circuito projetado para condicionamento e aquisição de apenas 4 canais para um Analisador de Bioimpedância.
