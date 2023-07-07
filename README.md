
PCB Projects

*Conexões presentes nas barras de pinos:
* Barra "tensoes":<br/>
Earth: Terra virtual implementado com LM675<br/>
VCC: +(MaxTensao da fonte utilizada / 2) Tensao NÃO regulada<br/>
VEE:-(MaxTensao da fonte utilizada / 2)  Tensao NÃO regulada<br/>
+9V: regulador 7809<br/>
-9V: regulador 7909<br/>
+5V: regulador 7805<br/>
-5V: regulador 7905<br/>
+3.3V: regulador 1117T-3.3<br/>
<br/>
* Barra "Sinais analogicos":<br/>
I1: corrente 1 dada pela fonte Howland<br/>
I2: corrente 2 dada pela fonte Howland (caso bipolar)<br/>
Ampl1: Tensão de saída do INA que monitora a corrente I1<br/>
Ampl2: Tensão de saída do INA que monitora a corrente I2<br/>
Sin1: Sinal alternado 1 gerado por AD9833/9850. Sem amplificação<br/>
Sin2: Sinal alternado 2 gerado por AD9833/9850. Sem amplificação<br/>
SinA: Sinal alternado 1 com controle de amplitude (talvez freq e fase)<br/>
SinA: Sinal alternado 2 com controle de amplitude (talvez freq e fase)<br/>
<br/>
* Barra "comunicacao":<br/>
SINC: Sinal de sincronismo (ainda a definir)<br/>
SDA(1-3)/SCL(1-3): Três pares de pinos reservados para comunicação I2C<br/>
SPI_COPI: comunicação SPI Controller Out Peripheral In<br/>
SPI_CIPO: comunicação SPI Controller In, Peripheral Out<br/>
SPI_clk: pino de clock que estabelece o sincronismo da comunicação SPI<br/>
CS(x): pinos para selecionar o chip desejado (Chip Select)<br/>
	-CS (AD9833): seleciona o gerador de sinais AD9833<br/>
	-CS (X9c10x): seleciona o potenciometro digital do circuito de controle da corrente<br/>
<br/>		
I2C arduino: https://docs.arduino.cc/learn/communication/wire<br/>
SPI arduino: https://docs.arduino.cc/learn/communication/spi?_gl=1*15adfz7*_ga*MTI2OTQ3ODg2MC4xNjg4NzY3MTg2*_ga_NEXN8H46L5*MTY4ODc2NzE4Ni4xLjAuMTY4ODc2NzE4Ni4wLjAuMA..<br/>
=======
** Barra "tensoes":
* Earth: Terra virtual implementado com LM675
VCC: +(MaxTensao da fonte utilizada / 2) Tensao NÃO regulada
VEE:-(MaxTensao da fonte utilizada / 2)  Tensao NÃO regulada
+9V: regulador 7809
-9V: regulador 7909
+5V: regulador 7805
-5V: regulador 7905
+3.3V: regulador 1117T-3.3

* Barra "Sinais analogicos":
I1: corrente 1 dada pela fonte Howland
I2: corrente 2 dada pela fonte Howland (caso bipolar)
Ampl1: Tensão de saída do INA que monitora a corrente I1
Ampl2: Tensão de saída do INA que monitora a corrente I2
Sin1: Sinal alternado 1 gerado por AD9833/9850. Sem amplificação
Sin2: Sinal alternado 2 gerado por AD9833/9850. Sem amplificação
SinA: Sinal alternado 1 com controle de amplitude (talvez freq e fase)
SinA: Sinal alternado 2 com controle de amplitude (talvez freq e fase)

* Barra "comunicacao":
SINC: Sinal de sincronismo (ainda a definir)
SDA(1-3)/SCL(1-3): Três pares de pinos reservados para comunicação I2C
SPI_COPI: comunicação SPI Controller Out Peripheral In
SPI_CIPO: comunicação SPI Controller In, Peripheral Out. 
SPI_clk: pino de clock que estabelece o sincronismo da comunicação SPI
CS(x): pinos para selecionar o chip desejado (Chip Select)
		-CS (AD9833): seleciona o gerador de sinais AD9833
		-CS (X9c10x): seleciona o potenciometro digital do circuito de controle da corrente
		
I2C arduino: https://docs.arduino.cc/learn/communication/wire
SPI arduino: https://docs.arduino.cc/learn/communication/spi?_gl=1*15adfz7*_ga*MTI2OTQ3ODg2MC4xNjg4NzY3MTg2*_ga_NEXN8H46L5*MTY4ODc2NzE4Ni4xLjAuMTY4ODc2NzE4Ni4wLjAuMA..

