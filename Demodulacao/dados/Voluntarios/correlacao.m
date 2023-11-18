#Octave 8.0.0
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
pkg load control; pkg load signal; pkg load io; pkg load statistics; %carrega pacotes

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Dados %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

HBF = [60.5	71.4	75.3	65.8	84.4	80.7	72.1	68.7	78.1	73.6;
       58.9	67.5	65.1	63.6	68.8	78.9	71.8	76.3	74.4	59.4];
       #linha 1: dados de FFM(%) dos 10 homens com a balanca comercial hbf
              #linha 2: dados de FFM(%) das 10 mulheres com a balanca comercial hbf

Equipamento_homens = [64.5	74.3	81.6	74.7	78.2	79.4	72.5	71.7	78.7	72.1;
                      64.7	73.5	80.6	72.2	83.7	82.1	74.5	72.1	79.0	71.6;
                      69.2	76.1	78.3	72.6	83.4	79.1	76.4	73.9	81.6	75.0];
# linha 1: eq 1
# linha 2: eq 5
# linha 3: eq 14

Equipamento_mulheres = [62.5	67.1	65.8	65.9	65.5	78.8	70.6	72.1	68.3	60.9;
                        65.0	67.7	70.4	68.8	70.5	78.1	74.1	76.7	75.8	64.4;
                        60.7	63.3	64.9	62.8	65.5	77.2	70.6	71.4	67.7	59.4;
                        64.5	67.2	71.1	70.9	70.8	80.6	75.2	76.5	75.6	62.0];

# linha 1: eq 1
# linha 2: eq 5
# linha 3: eq 6
# linha 4: eq 9

%%%%%%%%%%%% analise outliers

######homens
figure(1);
x = size(HBF,1)-1;
y = size(Equipamento_homens,1);

temp = [1,5,14];
for idx = 1:x+y-1
subplot(1,x+y,1)
boxplot(HBF(1,:))
title('HBF-514')
ylabel('FFM(%)')
axis([0.5 1.5])

subplot(1,x+y,1+idx)
boxplot(Equipamento_homens(idx,:))
title(['Eq ',num2str(temp(idx))])

axis([0.5 1.5])
end
saveas(gcf,'boxplot_FFM_homens.png')

######mulheres
figure(2);
x = size(HBF,1)-1;
y = size(Equipamento_mulheres,1);

temp = [1,5,6,9];
for idx = 1:x+y-1
subplot(1,x+y,1)
boxplot(HBF(2,:))
title('HBF-514')
ylabel('FFM(%)')
axis([0.5 1.5])

subplot(1,x+y,1+idx)
boxplot(Equipamento_mulheres(idx,:))
title(['Eq ',num2str(temp(idx))])

axis([0.5 1.5])
end
saveas(gcf,'boxplot_FFM_mulheres.png')

%%%%%%%%%%%%%% analise de correlacao

################# homens ##############

x = size(HBF,1)-1;
y = size(Equipamento_homens,1);

figure(4)
temp = [1,5,14]; #numeros das equaçoes

for idx=1:y
 p = polyfit( HBF(1,:) , Equipamento_homens(idx,:) , 1 ); #devolve os coeficientes do polinomio de 1 grau

[R,P] = corrcoef (HBF(1,:) , Equipamento_homens(idx,:)); #coeficiente de pearson e pvalor

printf(['R2 e p-valor Equação  ',num2str(temp(idx))])
printf('\n')
R2= R(2)^2
p_valor = P(2)

 xx = HBF(1,:); #vetor de x, dados dos homens
 yy = Equipamento_homens(idx,:); #vetor de y
 yyy = polyval(p,xx); #vetor de y reta

 subplot(1,y,idx)
 plot( xx , yy , 'bo' ,'linewidth', 1.5)
 hold on;
 plot(xx,yyy, 'r', 'linewidth', 2)

 equacao = sprintf('y =%.2f x + %.2f',p(1),p(2));
 text(65,80,equacao) #posição do polinomio no gráfico
 R2 = sprintf('R² = %.2f',R2);
 text(66,79,R2) #posição do polinomio no gráfico

 grid on
 title(['Relação entre HBF-514 e Equação  ',num2str(temp(idx))]);
 ylabel('FFM(%) - Equipamento desenvolvido');
 xlabel('FFM(%) - HBF-514');
 legend(' ponto experimental','curva ajustada','Location','southeast');


 hold off
end
saveas(gcf,'correlacao_FFM_homens.png')


################# mulheres ##############

x = size(HBF,1)-1;
y = size(Equipamento_mulheres,1);

figure(5)
temp = [1,5,6,9]; #numeros das equaçoes

for idx=1:y
 p = polyfit( HBF(2,:) , Equipamento_mulheres(idx,:) , 1 ); #devolve os coeficientes do polinomio de 1 grau

[R,P] = corrcoef (HBF(2,:) , Equipamento_mulheres(idx,:)); #coeficiente de pearson e pvalor

printf(['R2 e p-valor Equação  ',num2str(temp(idx))])
printf('\n')
R2= R(2)^2
p_valor = P(2)

 xx = HBF(2,:); #vetor de x, dados das mulheres
 yy = Equipamento_mulheres(idx,:); #vetor de y
 yyy = polyval(p,xx); #vetor de y reta

 subplot(1,y,idx)
 plot( xx , yy , 'bo' ,'linewidth', 1.5)
 hold on;
 plot(xx,yyy, 'r', 'linewidth', 2)

 equacao = sprintf('y =%.2f x + %.2f',p(1),p(2));
 text(60,75,equacao) #posição do polinomio no gráfico
 R2 = sprintf('R² = %.2f',R2);
 text(61,74,R2) #posição do polinomio no gráfico

 grid on
 title(['Relação entre HBF-514 e Equação  ',num2str(temp(idx))]);
 ylabel('FFM(%) - Equipamento desenvolvido');
 xlabel('FFM(%) - HBF-514');
 legend(' ponto experimental','curva ajustada','Location','southeast');


 hold off
end


saveas(gcf,'correlacao_FFM_mulheres.png')


