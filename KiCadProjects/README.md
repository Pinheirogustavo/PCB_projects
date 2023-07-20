# Versao do CAD: KiCad 7.0

------------------------------------------------------------------------------------------------------------------------------------------
## Como adicionar bibliotecas

- Bibliotecas prontas da internet (salvar em Projeto Global): https://forum.digikey.com/t/importing-the-digi-key-kicad-library-into-kicad-5-0-0/4075
	caminho:/PCB_projects/KiCadProjects/libraries/

- Bibliotecas criadas pelo autor:  Usar o editor de simbolos e de footprint do kicad, salvar em Projeto Global
	caminho:/PCB_projects/KiCadProjects/libraries/MyCreates
------------------------------------------------------------------------------------------------------------------------------------------

Placa 90x100mm face simples

Trilhas azuis: trilhas dispostas na face de cobre inferior

Trilhas vermelhas: Representam jumpers, estao dispostas na face de cobre superior


------------------------------------------------------------------------------------------------------------------------------------------

## Regras de layout PCB

- largura da trilha = 50 mils (1,27 mm)
 	O valor mínimo é de 8 mils, mas isso gera uma trilha extremamente fina
- Espaçamento entre trilhas = 50 mils (1,27 mm)
	O grid deve ser maior que o diâmetro da fresa utilizada (>0,2mm)
- Definir o algoritmo de auto-roteamento no CAD como “Grid Router” (precisa adicionar plugin)
- Definir o diâmetro do contorno em 0,5mm
 
 
------------------------------------------------------------------------------------------------------------------------------------------

## Orientações para layout PCB

- Criar trilhas de alimentação, de terra e de clock.
- Fazer as trilhas de alimentação com largura maior
- Evitar trilhas muito longas
- Preferir mudanças de direção de 45º nas trilhas
- Evitar que trilhas de sinais críticos (clock e altas freqüências) fiquem paralelas por muito tempo
- Evitar ligações diretas entre as entradas de alimentação de Cis
- Colocar um LED indicando que a placa está energizada
-Colocar pontos de acesso para medir com o osciloscópio
- Usar soquetes para os CIs

------------------------------------------------------------------------------------------------------------------------------------------
## Alguns footprints de componentes comuns 
##### E suas melhores  escolhas (ou até achar algo melhor)

Resistores -  11779 Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal
Capacitores eletrolíticos - 525 Capacitor_THT:CP_Radial_D5.0mm_P2.50mm
Diodos -  7485 Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal
LED - 8642 LED_THT:LED_D5.0mm
conectores fêmea -  5813/6090 Connector_PinSocket_2.54mm:PinSocket_1xXX_P2.54mm_Vertical
conectores macho -  4855/5132 Connector_PinHeader_2.54mm:PinHeader_1xXX_P2.54mm_Vertical 
conector p4 de bateria - 1150 Connector_BarrelJack:BarrelJack_GCT_DCJ200-10-A_Horizontal

------------------------------------------------------------------------------------------------------------------------------------------
## Tamanho de pad de componentes comuns 
##### E suas melhores  escolhas (ou até achar algo melhor). O tamanho do furo (0,8mm) não precisa ser configurado agora pois pode ser modificado na hora da produção (FlatCAM).

Resistores -  circular 2,5mm 

Capacitores eletrolíticos -  	+ circular 2mm	-retangular2x2,5mm

Diodos -   circular 2,5mm 

LED - 	+ circular 2mm	-retangular2x2,5mm

Barra de pinos - circular 2mm

conector p4 de bateria - oval3x4,2mm retangular4,6x3mm

------------------------------------------------------------------------------------------------------------------------------------------
### FONTE DE TENSAO


v01;v02 SW1: Botão DPDT com trava para ligar e desligar a fonte. https://www.multcomercial.com.br/chave-push-button-7x7-com-trava.html
v03;v04 Chave gangorra kcd1 para ligar e desligar a fonte.

Os reguladores estao localizados na borda da placa, alinhados e igualmente espaçados, sendo possivel utilizar único dissipador

Segundo icone, ao lado do simbolo de disquete. Para editar as regras de furos, tamanhos de trilhas... sempre conferir. 

Icone de lista. Verifica as regras.

------------------------------------------------------------------------------------------------------------------------------------------
