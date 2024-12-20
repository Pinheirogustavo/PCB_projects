function [] = resposta_frequencia()
% AINDA NAO FINALIZADA E TESTADA

  predefinicoes;

indice_polinomio = 3;

numero_curvas = input('Digite o numero de curvas a serem analisadas: ');

for i=1:length(numero_curvas)
  nome_arquivo_sumario = input('Digite o nome do arquivo com os dados sumarizados de uma curva: ', 's');
  nome_arquivo_sumario = strcat(nome_arquivo_sumario,'.csv');
  dados(:,i) = csvread(nome_arquivo_sumario);
  disp('Proxima curva...');
end
disp('Finalizado o carregamento das curvas');

tamanho_dados_linha = size(dados(1));
numero_analises = floor(idx/12); %quantidade de analises presentes nos dados
idx_amplitude_tensao = 8; %linha em que comecam os valores de amplitude do sinal obtido

for idx=1:numero_analises
  tensao_carga(idx,1) = dados(idx_amplitude_tensao,1) %amplitude da tensao sobre a carga
  idx_amplitude_tensao = idx_amplitude_tensao+8; %passa para a proxima amplitude
end

selecao = input('As curvas serao levantadas em funcao da carga (l) ou frequencia (f)?');

switch selecao

  case 'l'
    for i=1:length(numero_curvas)
      nome_arquivo_carga = input('Digite o nome do arquivo com os dados de cargas testadas, na sequencia em que as curvas foram adicionadas no programa: ', 's');
      nome_arquivo_carga = strcat(nome_arquivo_carga,'.csv');
      vetor_carga(:,i) = csvread(nome_arquivo_carga);
      disp('Proximo dado de carga...');

      Iload(:,i) =( (dados(:,i)./vetor_x(:,i))*1000 );#corrente atraves da carga (mA)
      p(:,i) = polyfit(vetor_carga(:,i), Iload(:,i), indice_polinomio); #devolve os coeficientes do polinomio, ultimo argumento eh o grau
    end

    disp('Finalizado o carregamento das cargas');
    vetor_x = vetor_carga
    grafico = 'l'; %indica que o grafico gerado sera em funcao da carga

  case 'f'
    vetor_x = frequencia sinal salvo na funcao sumariza varios

    grafico = 'f'; %indica que o grafico gerado sera em funcao da frequencia

end


xmin = vetor_x(1);
xmax = vetor_x(length(vetor_x));

xx = xmin:0.1:xmax; #vetor de x


 for i=1:length(numero_curvas)
    yy(:,i) = polyval(p(:,i),xx); #vetor de y
 end


 switch grafico

 case 'l'

    loglog(xx,yy,'r', 'linewidth', 2, cargas, Iload, 'k*');
 end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



figure(1); hold on
loglog(xx,yy,'r', 'linewidth', 2, cargas, Iload, 'k*');
loglog(xx_1,yy_1,'b', 'linewidth', 2, cargas_1, Iload_1, 'g*');
loglog(xx_2,yy_2,'c', 'linewidth', 2, cargas_2, Iload_2, 'm*');

line ([38000 38000], [0.1 4], "linestyle", ":", "color", "r", 'linewidth', 2);
line ([5490 5490], [0.1 4], "linestyle", ":", "color", "b", 'linewidth', 2);
line ([1094 1094], [0.1 4], "linestyle", ":", "color", "c", 'linewidth', 2);
 #ponto em que ocorre saturacao do ampOp SEMPRE ALTERAR


gggggggggggggg = text(22000, 1.5,['38k \Omega \rightarrow  '])
ggggggggggg = text(6000, 1.5,['\leftarrow  5.5k \Omega  '])
ggggggggg = text(700, 1.5,['1k \Omega \rightarrow  '])



#caso queira imprimir o polinomio no gráfico:
s = sprintf('y =(%.1f) x^2 +(%.5f) x + (%.5f)',p(1),p(2), p(3));
#text(100,0.4,s) #posição do polinomio no gráfico

title('Resposta da fonte de corrente em função da carga - 50 kHz');
ylabel('Iload[mA]');
xlabel('cargas[Ω]');
h = legend ("ajuste de curva i=0.5 mA","pontos experimentais i=0.5 mA",
"ajuste de curva i=1.0 mA","pontos experimentais i=1.0 mA",
"ajuste de curva i=3.3 mA","pontos experimentais i=3.3 mA",
"saturação do AmpOp i=0.5 mA",
"saturação do AmpOp i=1.0 mA",
"saturação do AmpOp i=3.3 mA");

legend(h,'Location','southwest'	);
xlim ([xmin,40000])
ylim ([0.1,4])


grid on

saveas(1,'correnteXcarga.jpg')

#coeficientes do polinomio
p(1)
p(2)


end
