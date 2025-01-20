# Placa de Aquisição 

## Versão atual em produção (jlcpcb:): 01

## Descrição Geral do projeto
 As placas de aquisição tem a função de suportar os módulos de microcontroladores stm32 modelo bluepill, empregados na demodulação de sinais.

### Versão 01

Esta versão suporta até 4 módulos stm32 bluepill. Onde é possível demodular 4 ou 8 canais externos em cada módulo.

A versão de barramento suportada é:

A alimentação de cada módulo é "dedicada". Isto é, há um regulador de tensão StepDown implementado na placa que fornece a tensão de 5V (5V_stepdown), que é regulada a 3.3V (3,3V_step) que é empregada na alimentação dos módulos. Em resumo os estágios são:

VCC (barramento) &rarr; 5V (StepDown) &rarr; 3V (regulador) &rarr; entrada 3.3V bluepill

As entradas analógicas fixas de cada módulo são:

> PA1 - Amplitude da corrente I1 (Ampl1)

> PA4 - Amplitude da corrente I2 (Ampl2)

As entradas analógicas de cada módulo referentos aos canais externos são:

> PA0 - Canal X (sign_Cx)

> PB0 - Canal X+4 (sign_Cx+4)

```mermaid
graph TD
A[Estes canais externos não estão implementados no barramento, mas sim por conectores de pinos horizontais laterais identificados por 'sign_C_' (elementos J4 e J5).]
```

As conexões de comunicação de cada módulo são (I2C):

> PB6 - SCL1 (3.3V)

> PB7 - SDA1 (3.3V)

As entradas digitais reservadas para sinais de sincronismo são:

> PA5 - SINC_A

> PA6 - SINC_B

> PA7 - SINC_C

> PB1 - SINCD

Assim, a ideia é que a placa opere em dois modos:

- Modo 1: leitura da amplitude de corrente individualmente em cada microcontrolador.
    Dado que o microcontrolador opera com dois ADCs, um estaria dedicado a ler algum sinal de corrente (I1 ou I2) e o segundo dedicado a ler um dos sinais vindos dos canais externos), possibilitando a leitura de 4 canais por placa de aquisição.

- Modo 2: leitura apenas dos canais externos por cada microcontrolador, sem leitura da corrente.
    Nesse modo os dois ADCs de cada microcontrolador realizam a leitura dos dois canais externos (X) e (X+4), possibilitando a leitura de 8 canais por placa de aquisição.

### Versao 02

### Versão 03
