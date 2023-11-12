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
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% equaçõesFat-free mass (FFM) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

l = 1;
eq = 14; #numero de equacoes


for idx=1:1:length(balanca); %numero de voluntarios
  a  = balanca(idx,2); #idade
  Ht = balanca(idx,3); #altura
  w  = balanca(idx,9); #peso
  Rb = prototipo(idx,2); #resistencia
  Xb = prototipo(idx,3); #reatancia
  Zb = prototipo(idx,4); #impedancia
  s  = prototipo(idx,8); #sexo

  if a>17 && a<95
    ffm(l,1) = ( (-4.104 + 0.518*(Ht^2/Rb) + 0.231*w + 0.130*Xb + 4.229*s) / w)*100;               #74
  else ffm(l,1) = NaN;end

  if a>17 && a<30 && s==0
    ffm(l+1,1) = ( (5.49 + 0.476*(Ht^2/Rb) + 0.295*w) /w)*100;                                       #75
  else ffm(l+1,1) = NaN;end

  if a>29 && a<40 && s==0
    ffm(l+2,1) = ( (11.59 + 0.493*(Ht^2/Rb) +0.141*w) /w)*100;                                       #75
  else ffm(l+2,1) = NaN;end

  if  s==0
    ffm(l+3,1) = ( (0.07 + 0.88*(Ht^1.97/Zb^0.49)*(1.0/22.22) + 0.081*w) /w)*100;                    #58
  else ffm(l+3,1) = NaN;end

  if a>15
    ffm(l+4,1) = ( (-12.44 + 0.34*(Ht^2/Rb) + 0.1534*Ht  + 0.273*w - 0.127*a + 4.56*s) /w)*100;      #76
  else ffm(l+4,1) = NaN;end

  if a>17 && a<61 && s==0
    ffm(l+5,1) = ( (20.05 - 0.04904*Rb + 0.001254*Ht^2 + 0.1555*w + 0.1417*Xb - 0.0833*a) /w)*100;   #77
  else ffm(l+5,1) = NaN;end

  if a>49 && a<71 && s==0
    ffm(l+6,1) = ( (6.34 + 0.474*Ht^2/Rb + 0.18*w) /w)*100;                                          #75
  else ffm(l+6,1) = NaN;end

  if a>17 && a<30 && s==1
    ffm(l+7,1) = ( (5.32 + 0.485*Ht^2/Rb + 0.338*w) /w)*100;                                         #75
  else ffm(l+7,1) = NaN;end

  if a>11 && a<95 &&s ==0
  ffm(l+8,1) = ( (-9.529 + 0.696*Ht^2/Rb + 0.168*w + 0.016*Rb) /w)*100;                            #70
  else ffm(l+8,1) = NaN;end

  if s==1
  ffm(l+9,1) = ( (0.49 + 0.5*(Ht^1.48/Zb^55)*(1/1.21) + 0.42*w) /w)*100;                          #58
  else ffm(l+9,1) = NaN;end

  if a>29 && a<50 && s==1
    ffm(l+10,1) = ( (4.51 + 0.549*Ht^2/Rb + 0.163*w + 0.092*Xb) /w)*100;                             #75
  else ffm(l+10,1) = NaN;end

  if a>34 && a<66
    ffm(l+11,1) = ( (-14.94 + 0.279*Ht^2/Rb + 0.181*w + 0.231*Ht + 0.064*s*w -0.077*a) /w)*100;      #78
  else ffm(l+11,1) = NaN;end

  if a>49 && a<71 && s==1
    ffm(l+12,1) = ( (-11.41 + 0.6*Ht^2/Rb + 0.186*w + 0.226*Xb) /w)*100;                             #75
  else ffm(l+12,1) = NaN;end

  if a>11 && a<95 && s==1
    ffm(l+13,1) = ( (-10.678 + 0.652*Ht^2/Rb + 0.262*w + 0.015*Rb) /w)*100;                          #70
  else ffm(l+13,1) = NaN;end

 ffm(l+eq,1) = NaN;

  l=l+eq+1;

end

###################valores da balanca###################################################
l=0;
for idx=1:1:length(balanca);
  for idxx=1:1:eq;
    ffm(l+idxx,2) = 100-balanca(idx,11);
  end
ffm(l+idxx+1,2)=NaN;
l=l+eq+1;
end

#################### erro relativo#################################################
l=0;
for idx=1:1:length(balanca);
  for idxx=1:1:eq;
    ffm(l+idxx,3) = ( abs(( ffm(l+idxx,2) - ffm(l+idxx,1) )) / ffm(l+idxx,2))*100;
  end
ffm(l+idxx+1,3)=NaN;
l=l+eq+1;
end

csvwrite ('ffm.csv', ffm);

######### erro de cada equação (linha: n da eq; coluna: n do voluntario)########
l=0;
for idx=1:1:eq;
c=1;
  for idxx=1:eq+1:length(ffm);
    eqs_ffm(idx,c) = ffm(l+idxx,3);
    c=c+1;
  end
l=l+1;
end

eqs_ffm_2 = eqs_ffm';

csvwrite ('eqs_ffm.csv', eqs_ffm);
csvwrite ('eqs_ffm_transposta.csv', eqs_ffm_2);














