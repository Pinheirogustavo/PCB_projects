# Bibliotecas para uso de microcontroladores (.h)

Aqui estão reunidas todas as bibliotecas empregadas nos microcontroladores presentes no projeto de tomógrafo por impedância elétrica desse repositório. A intenção é permitir que se rastreie quais versões das bibliotecas estão implementadas nesse projeto, visto que elas são utilizadas e modificadas por outros pesquisadores do grupo.

A seguir a descrição dessas bibliotecas:

## AD9833.h

> Autoria: Bill Williams

> Modificado por: não modificado

Biblioteca para controle do módulo gerador de onda AD9833 por meio de comunicação SPI. Funciona apenas com o microcontrolador Arduino Nano. **É necessário, como próximo passo, adaptá-la para o microcontrolador stm32**.

## ad9850.h

> Autoria:  Erick León

> Modificado por: Gustavo Pinheiro

Biblioteca para controle do módulo gerador de onda AD9850 por meio de saídas digitais de um microcontrolador qualquer. As únicas alterações foram justamente nos pinos digitais utilizados em cada projeto de placa.

**Para futuras aplicações** deve-se apenas alterar os pinos digitais utilizados para o controle (linhas 8 a 11).

## demux.h

> Autoria: Gustavo Pinheiro

> Modificado por:

Biblioteca para o uso da placa demux "Demux.V01". Permitindo selecionar os canais de injeção e drenagem de corrente num universo de 128 eletrodos.

A seleção do canal é feita a partir de um byte, dividido da seguinte forma:

> In (injeção): 0000 0000 to 0111 1111 or 00 to 7F or 0 to 127

> Out (drenagem): 1000 0000 to 1111 1111 or 80 to FF or 128 to 255

Uma  pode ser encontrada em:
Você pode consultar uma [tabela ASCII](https://web.cecs.pdx.edu/~harry/compilers/ASCIIChart.pdf) para verificar o valor hexadecimal de um eletrodo específico, uma vez que os bytes enviados pela comunicação I2C estão nesse formato.

**Atualmente os projetos de placas se limitam a 32 canais, 5 mux's em cascata. A integração de mais placas ou aumento de canais em cada uma delas necessita de alteração da Biblioteca para expansão na manipulação dos bits**

## dft.h

> Autoria:  Erick León

> Modificado por:

A Biblioteca permite o cálculo de uma componente da DFT de um sinal qualquer, se amostrado um sinal com ciclos completos (ou seja, em uma frequência que seja múltipla inteira da frequência de amostragem).

Retorna:

> Valor medio do sinal

> A amplitude do sinal

> A fase do sinal

## gerador.h

> Autoria: Gustavo Pinheiro

> Modificado por:

A Biblioteca permite controlar a placa de gerador de sinais "AD9850.V01", alterando a frequência do sinal emitido pelo módulo ad9850 e controle do ganho de sinal, por meio de alteração do potenciômetro implementado no amplificador inversor.

As funções presentes são:

> incrementa_frequencia(): Aumenta a frequência do sinal emitido, percorrendo um array de valores.

> decrementa_frequencia(): Diminui a frequência do sinal emitido, percorrendo um array de valores.

> aumenta_ganho(): Aumenta o ganho do sinal emitido, percorrendo para baixo os valores do potenciômetro digital (wiper_down).

> diminui_ganho(): Diminui o ganho do sinal emitido, percorrendo para cima os valores do potenciômetro digital (wiper_up).

> ganho_minimo(): Configura o circuito para o ganho mínimo possível.

> ganho_maximo(): Configura o circuito para o ganho máximo possível.

> printa_dados(): Exibe no monitor serial os valores de resitência do potenciômetro digital e a frequência do sinal atuais.

## serial_debug.h

> Autoria: Erick León

> Modificado por:

## stm32_adc_dual_mode.h

> Autoria: Erick León

> Modificado por:

Biblioteca para uso do ADC do STM32F103.
