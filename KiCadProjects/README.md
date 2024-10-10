# Versao do CAD: KiCad 7.0    

Placa 900x100mm face dupla

## Dicas gerais de uso do KiCad

- Os projetos desenvolvidos na versão Kicad 7.0 não são compatíveis com versões mais recentes.

- Sempre que for alterar um projeto abra o "arquivo_pro" específico, não o arquivo geral "KiCadProjects.kicad_pro".

- Ao realizar alguma modificação de projeto elétrico (não somente design), Faça a alteração no arquivo esquemático "arquivo_sch" e depois altere o arquivo de design "arquivo_pcb" por meio da ferramenta de "atualize a PCI com as alterações feitas no esquema - F8" (símbolo no painel superior). Modificações realizadas no sentido contrário não são atualizadas no esquema e assim sua placa confeccionada não irá corresponder ao projeto elétrico criado.

- Um bom tutorial em vídeo pode ser encontrado na playlist: <https://youtube.com/playlist?list=PL3bNyZYHcRSUhUXUt51W6nKvxx2ORvUQB&si=-wXaexDJ6YDI0aJu>

- Ao criar os seus esquemas tente separar cada estágio ou módulo e evite realizar ligações diretas de "wire", pois isso irá deixar a leitura mais confusa. Ao invés disso, utilize "rótulos globais" (Ctrl L / etiqueta no painel direito), que funcionam como conectores e ainda indicam os nós dos circuitos.

## Criando simbolos, footprint e 3D  

- Editor de símbolos &rarr; Arquivo &rarr; Nova biblioteca &rarr; Global &rarr; acesse a pasta de bibliotecas do seu github &rarr; acesse a pasta dos simbolos criados por você &rarr; NOME_SIMBOLO.kicad_sym Salvar. 
 - clique em "Criar Novo Símbolo (N)" 
  
- Quando criar um novo simbolo procure seguir Reference designator: https://en.wikipedia.org/wiki/Reference_designator 
  
- Sempre utilize pinos passivos 
- Numere os pinos no desenho do símbolo, para que o footprint possa fazer a atribuição correta 
- Nome do simbolo: Duplo clique na area de trabalho &rarr; preencher o campo valor 
  

## Como adicionar bibliotecas  
  

- Bibliotecas prontas da internet (salvar em Projeto Global): https://forum.digikey.com/t/importing-the-digi-key-kicad-library-into-kicad-5-0-0/4075 
 caminho:/PCB_projects/KiCadProjects/libraries/ 
  
- Bibliotecas criadas pelo autor:  Usar o editor de simbolos e de footprint do kicad, salvar em Projeto Global 
 caminho:/PCB_projects/KiCadProjects/libraries/MyCreates 
  
- Sempre adicione as bibliotecas pelo github e não pela sua máquina local. Exemplo: 
    
 Errado: /home/name/PCB_projects/KiCadProjects/libraries/MyCreates/AD9833_module.pretty 
    
 Certo: /home/name/**github**/PCB_projects/KiCadProjects/libraries/MyCreates/AD9833_module.pretty 
    

## Algumas das regras de layout PCB  - Fabricação JLCPCB

#### Todas as regras e restrições para a produção pela Jlcpcb devem ser conferidas em: <https://jlcpcb.com/capabilities/pcb-capabilities>

- largura dos segmentos de linha de corte ( Edge.cuts): 0.15 mm
  
- Tamanho de via: 0.30mm - 6.30mm diâmetro interno. Diâmetro externo deve ser no mínimo 0.20mm maior que o interno.

- Largura da trilha: mínimo de 0.16 mm (6.5 mils)

- Espaçamento entre trilhas: mínimo de 0.10 mm (4 mils)

- Espaçamento entre trilha e borda da via: mínimo de 0.10 mm (4 mils)

- Serigrafia: Largura mínima da linha de 0.16 mm (6 mils) e altura mínima do texto de 1.00 mm (40 mils).
    - Preferencialmente manter a proporção 1:6.


##### Todas essas restrições podem ser definidas por meio das "Regras de desenho" do Kicad.

 Símbolo de engrenagem (segundo no painel superior_ &rarr; Regras de desenho &rarr; tamanhos pré-definidos.
    - Permite estabelecer tamanhos de vias e trilhas que serão seguidas em todo o desenho.

 Símbolo de engrenagem (segundo no painel superior_ &rarr; Regras de desenho &rarr; restrições.
    - Permite estabalecer regras que se violadas serão indicadas pelo verificador de regras de desenho.

  Símbolo de engrenagem (segundo no painel superior_ &rarr; Texto & gráfico.
    - Permite estabelecer tamanho de Serigrafia que será seguido em todo o desenho.

##### Sempre execute o "Verificador de regras de desenho (símbolo de lista no painel superior) antes de gerar os arquivos para confecção.


- Extra: para produção na CNC - O grid deve ser maior que o diâmetro da fresa utilizada (>0,2mm).
    
 

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
  

## Alguns footprints de componentes comuns   
  

Resistor
    
    Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal 

Capacitor eletrolítico
    
    Capacitor_THT:CP_Radial_D5.0mm_P2.50mm 

Capacitor cerâmico 
    
    Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm

Capacitor tântalo 
    
    Capacitor_THT:CP_Radial_Tantal_D4.5mm_P2.50mm 

Diodo
    
    Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal

LED 
    
    LED_THT:LED_D5.0mm 

conectores fêmea

    Connector_PinSocket_2.54mm:PinSocket_1xXX_P2.54mm_Vertical 

conectores macho 
   
    Connector_PinHeader_2.54mm:PinHeader_1xXX_P2.54mm_Vertical 

conector p4 de bateria 
    
    Connector_BarrelJack:BarrelJack_GCT_DCJ200-10-A_Horizontal 

chave gangorra
    
    Chave_Gangorra:chave gangorra 2 pinos
    
L7809
    
    Package_TO_SOT_THT:TO-220-3_Vertical
    
LM7909
    
    Package_TO_SOT_THT:TO-220-3_Vertical
    
LM675
    
    Package_TO_SOT_THT:TO-220-5_P3.4x3.7mm_StaggerOdd_Lead3.8mm_Vertical
    
L7805
    
    Package_TO_SOT_THT:TO-220-3_Vertical
    
L7905
    
    Package_TO_SOT_THT:TO-220-3_Vertical
    
LM1117T-3.3
    
    Package_TO_SOT_THT:TO-220-3_Vertical
    
AD9850
    
    Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm
    
STM32-bluepill
    
    BluePill_STM32:BluePill_STM32F103C
    
AD828
    
    AD828:AD828
    
Potenciômetro Digital X9c10x
    
    X9c10X_module:X9c10X_module
    
Arduino Nano
    
    Module:Arduino_Nano
    
AD9833
    
    AD9833_module:AD9833_module
 

## Tamanho de pad de componentes comuns   

###### Caso esteja usando a CNC, todos os furos podem ser configurados diretamente no FlatCAM, não sendo necessário defini-los no projeto do Kicad.

- Resistores 

>Forma da ilha: Oval
>
>Tamanho da ilha: 2,0x1,6mm
>
>Forma do furo: circular
>
>Diâmetro do furo: 0,8mm

- Capacitores eletrolíticos 

> Forma da ilha: oval(+)            retangular(-)
>
> Tamanho da ilha:2,0x1,6mm(+)      2,0x1,6mm(-)
>
> Forma do furo: circular(+)        circular(-)
>
> Diâmetro do furo: 0,8mm(+)        0,8mm(-)

- Diodos 

> Forma da ilha: oval(+)            retangular(-)
>
> Tamanho da ilha:2,0x1,6mm(+)      2,0x1,6mm(-)
>
> Forma do furo: circular(+)        circular(-)
>
> Diâmetro do furo: 0,8mm(+)        0,8mm(-) 

- LED 

> Forma da ilha: oval(+)            retangular(-)
>
> Tamanho da ilha:2,0x1,8mm(+)      1,8x1,8mm(-)
>
> Forma do furo: circular(+)        circular(-)
>
> Diâmetro do furo: 1,1mm(+)        1,1mm(-) 

- Barra de pinos 

> Forma da ilha: oval
>
> Tamanho da ilha: 2,5x1,8mm
>
> Forma do furo:circular
>
> Diâmetro do furo: 1,02
  
- Chave gangorra

> Forma da ilha: Retangular
>
> Tamanho da ilha: 2,5x7,0mm
>
> Forma do furo: oval
>
> Diâmetro do furo: 0,8x6,0mm


- Conector p4 de bateria 

    - pad1 (vin)
    
        > Forma da ilha: retangular
	
        > Tamanho da ilha: 4,6x2,0mm
	
        > Forma do furo: oval
	
        > Diâmetro do furo: 3,6x1,0mm_P2
        
    - pad2 (vee)
    
        > Forma da ilha: Oval
	
        > Tamanho da ilha: 4,2x2,0mm
	
        > Forma do furo: oval
	
        > Diâmetro do furo: 3,2x1,0mm
        
    - pad3
    
        > Forma da ilha: Oval
	
        > Tamanho da ilha: 2,0x4,2mm
	
        > Forma do furo: oval
	
        > Diâmetro do furo: 1,0x3,2mm
        

## Autoroteamento

-   Utilize o plugin Freerouting ou Grid Router
-   Antes de tudo sempre realize primeiramente a atualiação da PCB a partir do esquemático e a verifcação das regras de desenho
-   Caso deseje refazer o roteamento, exclua todas as trilhas e vias geradas anteriormente: Editar → Exclusões globais → Vias e trilhas/Todas as camadas.
-   Caso tenha criado uma “zona” (linha tracejada) para o plano terra, a remova antes de realizar novo Autoroteamento (Ver mais em:  [https://www.reddit.com/r/KiCad/comments/5eu7fo/freerouting_left_a_lot_of_grounds_unreachable/](https://www.reddit.com/r/KiCad/comments/5eu7fo/freerouting_left_a_lot_of_grounds_unreachable/))


## Envio para produção no JLCPCB

#### Todas as orientações para a produção pela Jlcpcb a partir do Kicad 7.0 devem ser conferidas em: <https://jlcpcb.com/help/article/how-to-generate-gerber-and-drill-files-in-kicad-7>

Em resumo, você deve gerar 3 tipos de arquivos: Gerber, de perfuração (drill) e o mapeamento do projeto.

- Gerar arquivos Gerber: Files &rarr; Fabrication outputs &rarr; Gerbers (.gbr)
    As seguintes camadas devem ser selecionadas:

        F.Cu

        F.Paste

        F.Silks

        F.Mask

        B.Cu

        B.Paste

        B.Silks

        B.Mask

        Edge.Cuts

![Camadas para gerber JLCPCB - Kicad](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Imagens_tutorial/help2.png)
imagem retirada do site da JLCPCB

- Para gerar os arquivos de furo clique em "generate drill files" e siga as instruções:


![Furos para JLCPCB - Kicad](https://github.com/Pinheirogustavo/PCB_projects/blob/main/KiCadProjects/Imagens_tutorial/help3.png)
imagem retirada do site da JLCPCB

- Gere o arquivo de mapeamento clicando em "generate Map file".

- Todos os arquivos devem ser salvos em única pasta.

- Ao final a pasta deve conter 13 arquivos que são enviados para produção em .ZIP ou .RAR a partir da página inicial da fabricante.


#### Como produzir placas pequenas de modo repetido (Painel)

O tamanho mínimo das placas confeccionadas na JLCPCB é de 100x100mm. Caso a placa produzida seja menor, é possível copiar o design dentro de uma área definida. Há dois modos de realizar isso:

- Por meio do próprio site de encomenda do circuito. Em "PCB Specifications" selecione "Panel by JLCPCB". Ele irá captar as dimensões das linhas de "Edge.cuts" do projeto e assim você só precisa selecionar o número de linhas e colunas com repetição do projeto.

- Manualmente: Há um plugin, "Kikit", que auxilia esse trabalho. Uma vez instalado o circuito pode ser repetido por n linhas e m colunas com o uso da ferramenta "Kikit: Panelize PCB".

###### No momento de escrita desse tutorial não havia diferença de preço entre os modos de "panelização".
