# PCB Projects

## Conexões presentes nas barras de pinos

### Barra "tensoes"

- Earth: Terra virtual implementado com LM675
- VCC: +(MaxTensao da fonte utilizada / 2) Tensao NÃO regulada
- VEE:-(MaxTensao da fonte utilizada / 2)  Tensao NÃO regulada
- +9V: regulador 7809
- -9V: regulador 7909
- +5V: regulador 7805
- -5V: regulador 7905
- +3.3V: regulador 1117T-3.3

### Barra "Sinais analogicos"
- I1: corrente 1 dada pela fonte Howland
- I2: corrente 2 dada pela fonte Howland (caso bipolar)
- Ampl1: Tensão de saída condicionada do INA que monitora a corrente I1
- Ampl2: Tensão de saída condicionada do INA que monitora a corrente I2
- Sin1: Sinal alternado 1 gerado por AD9833/9850. Sem amplificação
- Sin2: Sinal alternado 2 gerado por AD9833/9850. Sem amplificação
- SinA: Sinal alternado 1 com controle de amplitude (talvez freq e fase)
- SinB: Sinal alternado 2 com controle de amplitude (talvez freq e fase)

### Barra "comunicacao"
- SINC: Sinal de sincronismo (ainda a definir)
- SDA(1-3)/SCL(1-3): Três pares de pinos reservados para comunicação - I2C
- SPI_COPI: comunicação SPI Controller Out Peripheral In
- SPI_CIPO: comunicação SPI Controller In, Peripheral Out
- SPI_clk: pino de clock que estabelece o sincronismo da comunicação SPI
- CS(x): pinos para selecionar o chip desejado (Chip Select)
> CS (AD9833): seleciona o gerador de sinais AD9833

> CS (X9c10x): seleciona o potenciometro digital do circuito de controle da corrente

I2C arduino: https://docs.arduino.cc/learn/communication/wire

SPI arduino https://docs.arduino.cc/learn/communication/spi?_gl=1*1



