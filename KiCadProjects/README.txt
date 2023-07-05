Versao do CAD: KiCad 7.0

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
- Definir o algoritmo de auto-roteamento no CAD como “Grid Router”
-definir o diâmetro do contorno em 0,5mm
 
 
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


SW1: Botão DPDT com trava para ligar e desligar a fonte. https://www.multcomercial.com.br/chave-push-button-7x7-com-trava.html

Os reguladores estao localizados na borda da placa, alinhados e igualmente espaçados, sendo possivel utilizar único dissipador

Segundo icone, ao lado do simbolo de disquete. Para editar as regras de furos, tamanhos de trilhas... sempre conferir. 

Icone de lista. Verifica as regras.

------------------------------------------------------------------------------------------------------------------------------------------
