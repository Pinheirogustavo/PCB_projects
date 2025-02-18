#pkg install -forge control;
pkg load control; #carrega o pacote de controle
clear all;
close all;
clc;
set (gcf, "graphicssmoothing", "off");

I_ajustada =  load("corrente_INA_ajustada.txt");#tensao sobre a carga (V)
I_ajustada = I_ajustada'*1000; #transpoe o vetor de tensoes sobre as cargas

I_N_ajustada =  load("corrente_INA_nao_ajustada.txt");#tensao sobre a carga (V)
I_N_ajustada = I_N_ajustada'*1000; #transpoe o vetor de tensoes sobre as cargas


frequencias = load("frequencias.txt") ; #frequencias analisadas
frequencias = frequencias';



######encontrar o ajuste de curva por interpolacao polinomial######
p = polyfit(frequencias, I_ajustada,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau
p_1 = polyfit(frequencias, I_N_ajustada,6); #devolve os coeficientes do polinomio, ultimo argumento eh o grau

#ir testando o grau que melhor se ajusta aos pontos

xmin = frequencias(1);
xmax = frequencias(length(frequencias));

xx = xmin:0.1:xmax; #vetor de x

%xx_1 = cargas_1(1):0.1:cargas_1(length(cargas_1)); #vetor de x
%xx_2 = cargas_2(1):0.1:cargas_2(length(cargas_2)); #vetor de x


yy = polyval(p,xx); #vetor de y
yy_1 = polyval(p_1,xx); #vetor de y
%yy_2 = polyval(p_2,xx_2); #vetor de y

figure(1); hold on
semilogx(xx,yy,'b', 'linewidth', 2, frequencias, I_ajustada, 'bs', 'linewidth', 1);
semilogx(xx,yy_1,'k', 'linewidth', 2, frequencias, I_N_ajustada, 'ks');
%loglog(xx_2,yy_2,'c', 'linewidth', 2, cargas_2, Iload_2, 'm*');

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

title('Resposta da fonte de corrente em função da frequência de excitação');
ylabel('Corrente fornecida [mA]');
xlabel('Frequência [Hz]');
h = legend ("Com ajuste de ganho","pontos experimentais com ajuste de ganho",
"Sem ajuste de ganho","pontos experimentais sem ajuste de ganho");

legend(h,'Location','southwest'	);
xlim ([xmin,xmax])
ylim ([0.001,2])


grid on

saveas(1,'correnteXcarga.jpg')

#coeficientes do polinomio
%p(1)
%p(2)

