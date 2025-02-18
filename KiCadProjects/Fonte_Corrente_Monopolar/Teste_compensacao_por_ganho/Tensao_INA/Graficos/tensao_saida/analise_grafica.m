#pkg install -forge control;
pkg load control; #carrega o pacote de controle
clear all;
close all;
clc;
set (gcf, "graphicssmoothing", "off");

Carga_R =  load("tensao_saida_Carga_R_500.txt");#tensao sobre a carga (V)
Carga_R = Carga_R; #transpoe o vetor de tensoes sobre as cargas

Carga_RC1 =  load("tensao_saida_Carga_RC_500_1_8p.txt");#tensao sobre a carga (V)
Carga_RC1 = Carga_RC1; #transpoe o vetor de tensoes sobre as cargas

Carga_RC2 =  load("tensao_saida_Carga_RC_500_100n.txt");#tensao sobre a carga (V)
Carga_RC2 = Carga_RC2; #transpoe o vetor de tensoes sobre as cargas



frequencias = load("frequencias.txt") ; #frequencias analisadas
frequencias = frequencias';



######encontrar o ajuste de curva por interpolacao polinomial######
%p = polyfit(frequencias, I_ajustada,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau
%p_1 = polyfit(frequencias, I_N_ajustada,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau

#ir testando o grau que melhor se ajusta aos pontos

xmin = frequencias(1);
xmax = frequencias(length(frequencias));

xx = xmin:0.1:xmax; #vetor de x

%xx_1 = cargas_1(1):0.1:cargas_1(length(cargas_1)); #vetor de x
%xx_2 = cargas_2(1):0.1:cargas_2(length(cargas_2)); #vetor de x


%yy = polyval(p,xx); #vetor de y
%yy_1 = polyval(p_1,xx); #vetor de y
%yy_2 = polyval(p_2,xx_2); #vetor de y

figure(1); hold on
semilogx( frequencias, Carga_R, 'b*', 'linewidth', 1);
semilogx( frequencias, Carga_RC1, 'ko', 'linewidth', 1);
semilogx( frequencias, Carga_RC2, 'rs', 'linewidth', 1);


%semilogx(xx,yy_1,'k', 'linewidth', 2, frequencias, I_N_ajustada, 'ks');
%loglog(xx_2,yy_2,'c', 'linewidth', 2, cargas_2, Iload_2, 'm*');

%line ([xmin xmax], [1 1], "linestyle", ":","color", "r", 'linewidth', 2);


%line ([38000 38000], [0.1 4], "linestyle", ":", "color", "r", 'linewidth', 2);
%line ([5490 5490], [0.1 4], "linestyle", ":", "color", "b", 'linewidth', 2);
%line ([1094 1094], [0.1 4], "linestyle", ":", "color", "c", 'linewidth', 2);
 #ponto em que ocorre saturacao do ampOp SEMPRE ALTERAR


%gggggggggggggg = text(22000, 1.5,['38k \Omega \rightarrow  '])
%ggggggggggg = text(6000, 1.5,['\leftarrow  5.5k \Omega  '])
%ggggggggg = text(700, 1.5,['1k \Omega \rightarrow  '])



#caso queira imprimir o polinomio no gráfico:
%s = sprintf('y =(%.1f) x^2 +(%.5f) x + (%.5f)',p(1),p(2), p(3));
#text(100,0.4,s) #posição do polinomio no gráfico

title('Tensão de saída do sistema de ganho da fonte de corrente em função da frequência de excitação');
ylabel('Tensão de saída [V]');
xlabel('Frequência [Hz]');
h = legend ("Carga resistiva 500Ω","Carga RC paralelo - 500Ω//1,8pF",
"Carga RC paralelo - 500Ω//100nF");

legend(h,'Location','northwest'	);
xlim ([xmin,xmax])
ylim ([0.0,9.0])


grid on

saveas(1,'correnteXfreq_Tensao_saida.jpg')

#coeficientes do polinomio
%p(1)
%p(2)

