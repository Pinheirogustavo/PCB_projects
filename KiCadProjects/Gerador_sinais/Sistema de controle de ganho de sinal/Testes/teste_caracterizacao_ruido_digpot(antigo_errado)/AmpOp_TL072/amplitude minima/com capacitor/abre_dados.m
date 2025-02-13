function  [dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight,nome_arquivo] = abre_dados()
  %help of function

  prompt = 'Digite o nome do arquivo de dados: ';
  arquivo = input(prompt,'s');
  nome_arquivo = arquivo;     %retorna o nome do arquivo de dados em stg para as funcoes de plot
  arquivo = strcat(arquivo,'.csv');
  cabecalho = input('Digite o numero de linhas de cabecalho do aquivo: ');


  dados_original = csvread(arquivo,cabecalho,0); %abre o arquivo de dados csv
                                          %pula as duas primeiras linhas (cabecalho)

  vetor_tempo = dados_original(:,1);  %vetor de tempo (coluna 1 dos dados)
  vetor_tempo_plot = vetor_tempo.*1000000;  %vetor de tempo em us

  vetor_tensao = dados_original(:,2); %vetor de tensoes (coluna 2 dos dados)
  vetor_tensao_plot = vetor_tensao.*1000; %vetor de tensoes em mV

  Ts = abs(vetor_tempo(11)-vetor_tempo(10)); %periodo de amostragem
  Fs = 1/Ts; %frequencia de amostragem

  L = length(vetor_tensao); %tamanho do vetor de tensoes


  %%% predifinicoes para fft
  maximo = max(dados_original);
  MinPeakHeight=(0.02*maximo(2)).*1000; %tamanho minimo para o pico de frequencia
                                          %(componente) ser detectado
                                            %(20% tensao maxima)

end


