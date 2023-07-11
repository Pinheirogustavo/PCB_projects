Versao do CAD: KiCad 7.0

------------------------------------------------------------------------------------------------------------------------------------------
Como adicionar bibliotecas

- Bibliotecas prontas da internet (salvar em Projeto Global): https://forum.digikey.com/t/importing-the-digi-key-kicad-library-into-kicad-5-0-0/4075
	caminho:/PCB_projects/KiCadProjects/libraries/

- Bibliotecas criadas pelo autor:  Usar o editor de simbolos e de footprint do kicad, salvar em Projeto Global
	caminho:/PCB_projects/KiCadProjects/libraries/MyCreates
------------------------------------------------------------------------------------------------------------------------------------------

Placa 90x100mm face simples

Trilhas azuis: trilhas dispostas na face de cobre inferior

Trilhas vermelhas: Representam jumpers, estao dispostas na face de cobre superior


------------------------------------------------------------------------------------------------------------------------------------------

Regras de layout PCB

- largura da trilha = 50 mils (1,27 mm)
 	O valor mínimo é de 8 mils, mas isso gera uma trilha extremamente fina
- Espaçamento entre trilhas = 50 mils (1,27 mm)
	O grid deve ser maior que o diâmetro da fresa utilizada (>0,2mm)
- Definir o algoritmo de auto-roteamento no CAD como “Grid Router” (precisa adicionar plugin)
- Definir o diâmetro do contorno em 0,5mm
 
 
------------------------------------------------------------------------------------------------------------------------------------------

Orientações para layout PCB

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

FONTE DE TENSAO


v01;v02 SW1: Botão DPDT com trava para ligar e desligar a fonte. https://www.multcomercial.com.br/chave-push-button-7x7-com-trava.html
v03;v04 Chave gangorra kcd1 para ligar e desligar a fonte.

Os reguladores estao localizados na borda da placa, alinhados e igualmente espaçados, sendo possivel utilizar único dissipador

Segundo icone, ao lado do simbolo de disquete. Para editar as regras de furos, tamanhos de trilhas... sempre conferir. 

Icone de lista. Verifica as regras.

------------------------------------------------------------------------------------------------------------------------------------------
