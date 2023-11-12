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
%%%%%%%%%%%%%%%%%%%%%%%%%%%% equações Total Body Watter (TBW) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

l = 1;
eq = 6; #numero de equacoes

for idx=1:1:length(balanca); %numero de voluntarios
  a  = balanca(idx,2); #idade
  Ht = balanca(idx,3); #altura
  w  = balanca(idx,9); #peso
  Rb = prototipo(idx,2); #resistencia
  Xb = prototipo(idx,3); #reatancia
  Zb = prototipo(idx,4); #impedancia
  s  = prototipo(idx,8); #sexo

  if 1==1
    tbw(l,1) = ( (6.53 + 0.3674*Ht^2/Zb + 0.17531*w - 0.11*a + 2.83*s) / w)*100;                 #90
  else tbw(l,1) = NaN;end

  if a>34 && a<66
    tbw(l+1,1) = ( (-17.58 + 0.24*Ht^2/Rb - 0.172*w + 0.04*s*w + 0.165*Ht) /w)*100;              #78
  else tbw(l+1,1) = NaN;end

  if  a>16 && a<67 && s==1
    tbw(l+2,1) = ( (8.399 + 0.396*Ht^2/Rb + 0.143*w) /w)*100;                                    #65
  else tbw(l+2,1) = NaN;end

  if  a>16 && a<67 && s==0
    tbw(l+3,1) = ( (8.315 + 0.382*Ht^2/Rb + 0.105*w) /w)*100;                                    #65
  else tbw(l+3,1) = NaN;end

  if a>16 && a<67
    tbw(l+4,1) = ( (1.726 + 0.5561*Ht^2/Rb - 0.0955*w) /w)*100;                                  #65
  else tbw(l+4,1) = NaN;end

  if a>11 && a<95 && s==1
    tbw(l+5,1) = ( (1.203 + 0.449*Ht^2/Rb + 0.176*w) /w)*100;                                    #70
  else tbw(l+5,1) = NaN;end

 tbw(l+eq,1) = NaN;

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
csvwrite ('tbw.csv', tbw);
%csvwrite ('eqs_tbw.csv', eqs_tbw);
%csvwrite ('eqs_tbw_transposta.csv', eqs_tbw_2);


%%%%%%%%% transpor valores

l=0;
for idx=1:1:eq;
c=1;
  for idxx=1:eq+1:length(tbw);
    tbw_2(idx,c) = tbw(l+idxx,1);
    c=c+1;
  end
l=l+1;
end
csvwrite ('tbw_transposta.csv', tbw_2);










