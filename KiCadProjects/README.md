# Versao do CAD: KiCad 7.0  
  
  

------------------------------------------------------------------------------------------------------------------------------------------  
  

Placa 100x100mm face simples  
  

Trilhas azuis: trilhas dispostas na face de cobre inferior  
  

Trilhas vermelhas: Representam jumpers, estao dispostas na face de cobre superior  
  
  

------------------------------------------------------------------------------------------------------------------------------------------  

## Criando simbolos, footprint e 3D  

- Editor de símbolos &rarr; Arquivo &rarr; Nova biblioteca &rarr; Global &rarr; acesse a pasta de bibliotecas do seu github &rarr; acesse a pasta dos simbolos criados por você &rarr; NOME_SIMBOLO.kicad_sym Salvar.   
 - clique em "Criar Novo Símbolo (N)"  
  
- Quando criar um novo simbolo procure seguir Reference designator: https://en.wikipedia.org/wiki/Reference_designator  
  
- Sempre utilize pinos passivos  
- Numere os pinos no desenho do símbolo, para que o footprint possa fazer a atribuição correta  
- Nome do simbolo: Duplo clique na area de trabalho &rarr; preencher o campo valor  
  

------------------------------------------------------------------------------------------------------------------------------------------  
  
  

## Como adicionar bibliotecas  
  

- Bibliotecas prontas da internet (salvar em Projeto Global): https://forum.digikey.com/t/importing-the-digi-key-kicad-library-into-kicad-5-0-0/4075  
 caminho:/PCB_projects/KiCadProjects/libraries/  
  
- Bibliotecas criadas pelo autor:  Usar o editor de simbolos e de footprint do kicad, salvar em Projeto Global  
 caminho:/PCB_projects/KiCadProjects/libraries/MyCreates  
  
- Sempre adicione as bibliotecas pelo github e não pela sua máquina local. Exemplo:  
    
 Errado: /home/name/PCB_projects/KiCadProjects/libraries/MyCreates/AD9833_module.pretty  
    
 Certo: /home/name/**github**/PCB_projects/KiCadProjects/libraries/MyCreates/AD9833_module.pretty  
    

------------------------------------------------------------------------------------------------------------------------------------------  
  

## Algumas das regras de layout PCB  
  

- Largura da trilha (default) = 50 mils (1,27 mm)  
  
 O valor mínimo é de 5 mils, mas isso gera uma trilha extremamente fina  
  
- Espaçamento entre trilhas  e entre trilhas e furos(default) = 50 mils (1,27 mm)  
  
 O valor mínimo é de 8 mils, mas isso gera  trilhas muito próximas  
  
- Para produção na CNC: O grid deve ser maior que o diâmetro da fresa utilizada (>0,2mm)  
- Definir o algoritmo de auto-roteamento no CAD como “Grid Router” ou "Freerouting" (precisa adicionar plugin)  
- Definir o diâmetro do contorno em 0,5mm  
  

#### Todas as regras e restrições para a produção pela Jlcpcb devem ser conferidas em: <https://jlcpcb.com/capabilities/pcb-capabilities>  
    

------------------------------------------------------------------------------------------------------------------------------------------  
  

## Orientações para layout PCB  
  

- Criar trilhas de alimentação, de terra e de clock.  
- Fazer as trilhas de alimentação com largura maior  
- Evitar trilhas muito longas  
- Preferir mudanças de direção de 45º nas trilhas  
- Evitar que trilhas de sinais críticos (clock e altas freqüências) fiquem paralelas por muito tempo  
- Evitar ligações diretas entre as entradas de alimentação de Cis  
- Colocar um LED indicando que a placa está energizada  
- Colocar pontos de acesso para medir com o osciloscópio  
- Usar soquetes para os CIs  
  
- Segundo ícone, ao lado do simbolo de disquete. Serve para editar as regras de furos, tamanhos de trilhas... sempre conferir.   
  
- Ícone de lista. Serve para verificar as regras RDC.  
  
  

------------------------------------------------------------------------------------------------------------------------------------------  

## Alguns footprints de componentes comuns   

#### E suas melhores  escolhas (ou até achar algo melhor)  
  

Resistores -  11779 Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal  
  

Capacitores eletrolíticos - 525 Capacitor_THT:CP_Radial_D5.0mm_P2.50mm  
  

Diodos -  7485 Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal  
  

LED - 8642 LED_THT:LED_D5.0mm  
  

conectores fêmea -  5813/6090 Connector_PinSocket_2.54mm:PinSocket_1xXX_P2.54mm_Vertical  
  

conectores macho -  4855/5132 Connector_PinHeader_2.54mm:PinHeader_1xXX_P2.54mm_Vertical   
  

conector p4 de bateria - 1150 Connector_BarrelJack:BarrelJack_GCT_DCJ200-10-A_Horizontal  
  

------------------------------------------------------------------------------------------------------------------------------------------  

## Tamanho de pad de componentes comuns   

#### E suas melhores  escolhas (ou até achar algo melhor). O tamanho do furo (0,8mm) não precisa ser configurado agora pois pode ser modificado na hora da produção (FlatCAM).  
  

Resistores -  circular/oval $\geqslant$ 2,5mm   
  

Capacitores eletrolíticos -  	+ circular 2mm	-retangular2x2,5mm  
  

Diodos -   circular 2,5mm   
  

LED - 	+ circular 2mm	-retangular2x2,5mm  
  

Barra de pinos - Oval 2,5 mm X 1,8 mm ; furo 1,02 mm  
  

conector p4 de bateria - oval3x4,2mm retangular4,6x3mm  
  

------------------------------------------------------------------------------------------------------------------------------------------  
  
  

## Autoroteamento  
  

- Utilize o plugin Freerouting ou Grid Router  
- Antes de tudo sempre realize primeiramente a atualiação da PCB a partir do esquemático e a verifcação das regras de desenho  
- Caso deseje refazer o roteamento, exclua todas as trilhas e vias geradas anteriormente: Editar &rarr; Exclusões globais &rarr; Vias e trilhas/Todas as camadas.  
- Caso tenha criado uma "zona" (linha tracejada) para o plano terra, a remova antes de realizar novo Autoroteamento (Ver mais em: https://www.reddit.com/r/KiCad/comments/5eu7fo/freerouting_left_a_lot_of_grounds_unreachable/)  
  
  
  

# Versao do CAD: KiCad 7.0

----------

Placa 100x100mm face simples

Trilhas azuis: trilhas dispostas na face de cobre inferior

Trilhas vermelhas: Representam jumpers, estao dispostas na face de cobre superior

----------

## Criando simbolos, footprint e 3D

-   Editor de símbolos → Arquivo → Nova biblioteca → Global → acesse a pasta de bibliotecas do seu github → acesse a pasta dos simbolos criados por você → NOME_SIMBOLO.kicad_sym Salvar.
    
    -   clique em “Criar Novo Símbolo (N)”
-   Quando criar um novo simbolo procure seguir Reference designator:  [https://en.wikipedia.org/wiki/Reference_designator](https://en.wikipedia.org/wiki/Reference_designator)
    
-   Sempre utilize pinos passivos
    
-   Numere os pinos no desenho do símbolo, para que o footprint possa fazer a atribuição correta
    
-   Nome do simbolo: Duplo clique na area de trabalho → preencher o campo valor
    

----------

## Como adicionar bibliotecas

-   Bibliotecas prontas da internet (salvar em Projeto Global):  [https://forum.digikey.com/t/importing-the-digi-key-kicad-library-into-kicad-5-0-0/4075](https://forum.digikey.com/t/importing-the-digi-key-kicad-library-into-kicad-5-0-0/4075)  
    caminho:/PCB_projects/KiCadProjects/libraries/
    
-   Bibliotecas criadas pelo autor: Usar o editor de simbolos e de footprint do kicad, salvar em Projeto Global  
    caminho:/PCB_projects/KiCadProjects/libraries/MyCreates
    
-   Sempre adicione as bibliotecas pelo github e não pela sua máquina local. Exemplo:
    
    Errado: /home/name/PCB_projects/KiCadProjects/libraries/MyCreates/AD9833_module.pretty
    
    Certo: /home/name/**github**/PCB_projects/KiCadProjects/libraries/MyCreates/AD9833_module.pretty
    

----------

## Algumas das regras de layout PCB

-   Largura da trilha (default) = 50 mils (1,27 mm)
    
    ```
      O valor mínimo é de 5 mils, mas isso gera uma trilha extremamente fina
    
    ```
    
-   Espaçamento entre trilhas e entre trilhas e furos(default) = 50 mils (1,27 mm)
    
    ```
      O valor mínimo é de 8 mils, mas isso gera  trilhas muito próximas
    
    ```
    
-   Para produção na CNC: O grid deve ser maior que o diâmetro da fresa utilizada (>0,2mm)
    
-   Definir o algoritmo de auto-roteamento no CAD como “Grid Router” ou “Freerouting” (precisa adicionar plugin)
    
-   Definir o diâmetro do contorno em 0,5mm
    

#### Todas as regras e restrições para a produção pela Jlcpcb devem ser conferidas em:  [https://jlcpcb.com/capabilities/pcb-capabilities](https://jlcpcb.com/capabilities/pcb-capabilities)

----------

## Orientações para layout PCB

-   Criar trilhas de alimentação, de terra e de clock.
    
-   Fazer as trilhas de alimentação com largura maior
    
-   Evitar trilhas muito longas
    
-   Preferir mudanças de direção de 45º nas trilhas
    
-   Evitar que trilhas de sinais críticos (clock e altas freqüências) fiquem paralelas por muito tempo
    
-   Evitar ligações diretas entre as entradas de alimentação de Cis
    
-   Colocar um LED indicando que a placa está energizada
    
-   Colocar pontos de acesso para medir com o osciloscópio
    
-   Usar soquetes para os CIs
    
-   Segundo ícone, ao lado do simbolo de disquete. Serve para editar as regras de furos, tamanhos de trilhas… sempre conferir.
    
-   Ícone de lista. Serve para verificar as regras RDC.
    

----------

## Alguns footprints de componentes comuns

#### E suas melhores escolhas (ou até achar algo melhor)

Resistores - 11779 Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal

Capacitores eletrolíticos - 525 Capacitor_THT:CP_Radial_D5.0mm_P2.50mm

Diodos - 7485 Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal

LED - 8642 LED_THT:LED_D5.0mm

conectores fêmea - 5813/6090 Connector_PinSocket_2.54mm:PinSocket_1xXX_P2.54mm_Vertical

conectores macho - 4855/5132 Connector_PinHeader_2.54mm:PinHeader_1xXX_P2.54mm_Vertical

conector p4 de bateria - 1150 Connector_BarrelJack:BarrelJack_GCT_DCJ200-10-A_Horizontal

----------

## Tamanho de pad de componentes comuns

#### E suas melhores escolhas (ou até achar algo melhor). O tamanho do furo (0,8mm) não precisa ser configurado agora pois pode ser modificado na hora da produção (FlatCAM).

Resistores - circular/oval  ⩾⩾  2,5mm

Capacitores eletrolíticos - + circular 2mm -retangular2x2,5mm

Diodos - circular 2,5mm

LED - + circular 2mm -retangular2x2,5mm

Barra de pinos - Oval 2,5 mm X 1,8 mm ; furo 1,02 mm

conector p4 de bateria - oval3x4,2mm retangular4,6x3mm

----------

## Autoroteamento

-   Utilize o plugin Freerouting ou Grid Router
-   Antes de tudo sempre realize primeiramente a atualiação da PCB a partir do esquemático e a verifcação das regras de desenho
-   Caso deseje refazer o roteamento, exclua todas as trilhas e vias geradas anteriormente: Editar → Exclusões globais → Vias e trilhas/Todas as camadas.
-   Caso tenha criado uma “zona” (linha tracejada) para o plano terra, a remova antes de realizar novo Autoroteamento (Ver mais em:  [https://www.reddit.com/r/KiCad/comments/5eu7fo/freerouting_left_a_lot_of_grounds_unreachable/](https://www.reddit.com/r/KiCad/comments/5eu7fo/freerouting_left_a_lot_of_grounds_unreachable/))
