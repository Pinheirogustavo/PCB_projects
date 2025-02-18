#pkg install -forge control;
pkg load control; #carrega o pacote de controle
clear all;
close all;
clc;
%set (gcf, "graphicssmoothing", "off");

%I_ajustada_R =  load("corrente_INA_ajustada_R.txt");#corrente INA COM sistema de ajuste - R 504 ohm
%I_ajustada_R = I_ajustada_R'*1000; #transpoe e transforma para mA

%I_N_ajustada_R =  load("corrente_INA_nao_ajustada_R.txt");#corrente INA SEM sistema de ajuste - R 504 ohm
%I_N_ajustada_R = I_N_ajustada_R'*1000; #transpoe o vetor de tensoes sobre as cargas

I_ajustada_RC1 =  load("corrente_INA_ajustada_RC1.txt");#corrente INA COM sistema de ajuste - RC paralelo 504 ohm 1,8pF
I_ajustada_RC1 = I_ajustada_RC1'*1000; #transpoe e transforma para mA

I_N_ajustada_RC1 =  load("corrente_INA_nao_ajustada_RC1.txt");#corrente INA SEM sistema de ajuste - RC paralelo 504 ohm 1,8pF
I_N_ajustada_RC1 = I_N_ajustada_RC1'*1000; #transpoe e transforma para mA

I_ajustada_RC2 =  load("corrente_INA_ajustada_RC2.txt");#corrente INA COM sistema de ajuste - RC paralelo 504 ohm 100nF
I_ajustada_RC2 = I_ajustada_RC2'*1000; #transpoe e transforma para mA

I_N_ajustada_RC2 =  load("corrente_INA_nao_ajustada_RC2.txt"); #corrente INA SEM sistema de ajuste - RC paralelo 504 ohm 100nF
I_N_ajustada_RC2 = I_N_ajustada_RC2'*1000; #transpoe e transforma para mA

frequencias = load("frequencias.txt") ; #frequencias analisadas
frequencias = frequencias';



######encontrar o ajuste de curva por interpolacao polinomial######
%p_R = polyfit(frequencias, I_ajustada_R,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau
%p_1_R = polyfit(frequencias, I_N_ajustada_R,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau

p_RC1 = polyfit(frequencias, I_ajustada_RC1,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau
p_1_RC1 = polyfit(frequencias, I_N_ajustada_RC1,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau

p_RC2 = polyfit(frequencias, I_ajustada_RC2,5); #devolve os coeficientes do polinomio, ultimo argumento eh o grau
p_1_RC2 = polyfit(frequencias, I_N_ajustada_RC2,5); #devolve os coeficientes do polinomio, ultimo argumento eh o grau

#ir testando o grau que melhor se ajusta aos pontos

xmin = frequencias(1);
xmax = frequencias(length(frequencias));

xx = xmin:0.1:xmax; #vetor de x




%yy_R = polyval(p_R,xx); #vetor de y
%yy_1_R = polyval(p_1_R,xx); #vetor de y

yy_RC1 = polyval(p_RC1,xx); #vetor de y
yy_1_RC1 = polyval(p_1_RC1,xx); #vetor de y

yy_RC2 = polyval(p_RC2,xx); #vetor de y
yy_1_RC2 = polyval(p_1_RC2,xx); #vetor de y

figure(1); hold on
%semilogx(xx,yy_R,'b', 'linewidth', 2, frequencias, I_ajustada_R, 'bs', 'linewidth', 1);
%semilogx(xx,yy_1_R,':b', 'linewidth', 2, frequencias, I_N_ajustada_R, 'bo');

semilogx(xx,yy_RC1,'k', 'linewidth', 1, frequencias, I_ajustada_RC1, 'ks', 'linewidth', 1);
semilogx(xx,yy_1_RC1,'--k', 'linewidth', 1, frequencias, I_N_ajustada_RC1, 'ko', 'linewidth', 1);


semilogx(xx,yy_RC2,'b', 'linewidth', 1, frequencias, I_ajustada_RC2, 'bs', 'linewidth', 1);
semilogx(xx,yy_1_RC2,'--b', 'linewidth', 1, frequencias, I_N_ajustada_RC2, 'bo', 'linewidth', 1);


line ([xmin xmax], [1 1], "linestyle", ":","color", "r", 'linewidth', 2);

hold off




%title('Carga RC paralelo');
ylabel('Current [mA]');
xlabel('frequency [Hz]');
h = legend (
%"Com ajuste de ganho - 504 Ω","pontos experimentais com ajuste de ganho - 504 Ω",
%"Sem ajuste de ganho - 504 Ω","pontos experimentais sem ajuste de ganho - 504 Ω",
"gain adjustment - 504 Ω // 1,8pF","trial points - gain adjustment -504 Ω // 1,8pF",
"without adjustment - 504 Ω // 1,8pF","trial points - without adjustment - 504 Ω // 1,8pF",
"gain adjustment - 504 Ω // 100nF","trial points - gain adjustment - 504 Ω // 100nF",
"without adjustment - 504 Ω // 100nF","trial points - without adjustment - 504 Ω // 100nF",
"Ideal");

legend(h,'Location','southwest'	);
xlim ([xmin,xmax])
ylim ([0.001,2])


grid on

saveas(1,'current.jpg')

#coeficientes do polinomio
%p(1)
%p(2)
print('current.jpg', '-djpg', '-S872,654');

