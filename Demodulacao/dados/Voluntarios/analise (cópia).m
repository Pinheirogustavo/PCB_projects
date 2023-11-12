#Octave 7.1.0
#Autor: Gustavo Pinheiro

%%%%%%%%%%%%%%%%%%%%%%%%%%%% Descricao do codigo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%{
Analise dos dados de bioimpedancia dos voluntarios do experimento
CAAE: 78985417.0.0000.5594
XXXXXXXXX
%}

#pre-defifinicoes do octave
clear all; more off;clc; close all; %limpa o ambiente de trabalho
#clearvars -except A ##### apaga todas as variaveis, menos a tabela A
pkg load control; pkg load signal; pkg load io;  %carrega pacotes

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Dados %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

balanca = xlsread('voluntarios.ods');  %arquivo com dados dos voluntarios obtidos a
%partir da balança omron hbf-514c
%{
label_A= [Voluntario(a)	Idade	Altura(cm)	cintura(cm)	bracoE(cm)	bracoD(cm)
pernaE(cm)	pernaD(cm)	Peso(kg)	IMC	BodyFat(%)	Musculo(%)	ritmo(kcal)
IdadeCorporal	GorduraVisceral
%}

prototipo = xlsread('dados_bioimpedancia.ods'); %arquivo com dados dos voluntarios
%obtidos apartir do prototipo.
%{
label_B = [voluntario	Rb_ohm	Xb_ohm	Zb_ohm	fase_º	Zc_ohm	fase_º	sexo]
sexo:  0-feminino ; 1-masculino
%}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% equações extracellular water (ECW) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% equações body cell mass (BCW) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

l = 1;
eq = 3; #numero de equacoes


for idx=1:1:length(balanca); %numero de voluntarios
  a  = balanca(idx,2); #idade
  Ht = balanca(idx,3); #altura
  w  = balanca(idx,9); #peso
  Rb = prototipo(idx,2); #resistencia
  Xb = prototipo(idx,3); #reatancia
  Zb = prototipo(idx,4); #impedancia
  s  = prototipo(idx,8); #sexo

  if 1==1
    cw(l,1) = ( (-5.22 + 0.2*Ht^2/Rb + 0.005*Ht^2/Xb + 0.08*w + 1.9 + 1.86*s) / w)*100;          #95
  else cw(l,1) = NaN;end

  if  s==1
    cw(l+1,1) = ( (1/120*(0.76*(59.06*Ht^1.6/Xb^0.5)+(18.52*w)-386.66)) /w)*100;                 #58
  else cw(l+1,1) = NaN;end

  if s==0
    cw(l+2,1) = ( (1/120*(0.96*(1.3*Ht^2.07/Xb^0.36)+(5.79*w)-230.51)) /w)*100;                  #58
  else cw(l+2,1) = NaN;end



 cw(l+eq,1) = NaN;

  l=l+eq+1;

end

###################valores da balanca###################################################
%{
l=0;
for idx=1:1:length(balanca);
  for idxx=1:1:eq;
    tbw(l+idxx,2) = 100-balanca(idx,11);
  end
tbw(l+idxx+1,2)=NaN;
l=l+eq+1;
end

#################### erro relativo#################################################
l=0;
for idx=1:1:length(balanca);
  for idxx=1:1:eq;
    tbw(l+idxx,3) = ( abs(( tbw(l+idxx,2) - tbw(l+idxx,1) )) / tbw(l+idxx,2))*100;
  end
tbw(l+idxx+1,3)=NaN;
l=l+eq+1;
end

csvwrite ('tbw.csv', tbw);

######### erro de cada equação (linha: n da eq; coluna: n do voluntario)########
l=0;
for idx=1:1:eq;
c=1;
  for idxx=1:eq+1:length(tbw);
    eqs_tbw(idx,c) = tbw(l+idxx,3);
    c=c+1;
  end
l=l+1;
end

eqs_tbw_2 = eqs_tbw';
%}
csvwrite ('cw.csv', cw);
%csvwrite ('eqs_tbw.csv', eqs_tbw);
%csvwrite ('eqs_tbw_transposta.csv', eqs_tbw_2);


%%%%%%%%% transpor valores

l=0;
for idx=1:1:eq;
c=1;
  for idxx=1:eq+1:length(cw);
    cw_2(idx,c) = cw(l+idxx,1);
    c=c+1;
  end
l=l+1;
end
csvwrite ('cw_transposta.csv', cw_2);













