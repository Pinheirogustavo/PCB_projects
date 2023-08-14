# PCB Projects

## V01

Apresenta um único pino de terra

## V02 

- Apresenta diversos pontos de terras, separados em terras dos sinais analógicos (AGND) e terras dos sinais digitais (DGND).
- As alimentações dos circuitos analógicos foram separadas das alimentações dos circuitos digitais.

## Conexões presentes nas barras de pinos

### "tensoes"

- AGND: Terra virtual implementado com LM675 - circuitos analógicos
- DGND: Terra virtual implementado com LM675 - circuitos digitais
- VCC: +(MaxTensao da fonte utilizada / 2) Tensao NÃO regulada
- VEE:-(MaxTensao da fonte utilizada / 2)  Tensao NÃO regulada
- +9V: regulador 7809
- -9V: regulador 7909
- +5V: regulador 7805
- -5V: regulador 7905
- +3.3V: regulador 1117T-3.3

### "Sinais analogicos"
- I1: corrente 1 dada pela fonte Howland
- I2: corrente 2 dada pela fonte Howland (caso bipolar)
- Ampl1: Tensão de saída condicionada do INA que monitora a corrente I1
- Ampl2: Tensão de saída condicionada do INA que monitora a corrente I2
- Sin1: Sinal alternado 1 gerado por AD9833/9850. Sem amplificação
- Sin2: Sinal alternado 2 gerado por AD9833/9850. Sem amplificação
- SinA: Sinal alternado 1 com controle de amplitude (talvez freq e fase)
- SinB: Sinal alternado 2 com controle de amplitude (talvez freq e fase)

### "comunicacao"
- SINC: Sinal de sincronismo (ainda a definir)
- SDA(1-3)/SCL(1-3): Três pares de pinos reservados para comunicação - I2C
- SPI_COPI: comunicação SPI Controller Out Peripheral In
- SPI_CIPO: comunicação SPI Controller In, Peripheral Out
- SPI_clk: pino de clock que estabelece o sincronismo da comunicação SPI
- CS(x): pinos para selecionar o chip desejado (Chip Select)
> CS (AD9833): seleciona o gerador de sinais AD9833

> CS (X9c10x): seleciona o potenciometro digital do circuito de controle da corrente



