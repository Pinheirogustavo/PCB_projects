function  [dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight,nome_arquivo] = abre_dados()
  %[X,Y,...,Z] = abre_dados()
  %
  %funcao 'abre_dados': permite abrir os arquivos .csv obtidos por osciloscopio.
    %Retorna os vetores:
    % -dados_original: matriz com dados de tempos e tensoes adquiridas pelo osciloscopio;
    % -vetor_tempo: vetor coluna com os tempos adquiridos pelo osciloscopio;
    % -vetor_tempo_plot: vetor coluna com os tempos (em microssegundos)adquiridos pelo osciloscopio;
    % -vetor_tensao: vetor coluna com as tensoes adquiridas pelo osciloscopio;
    % -vetor_tensao_plot:vetor coluna com as tensoes (em milivolts) adquiridas pelo osciloscopio;
    % Retorna as variaveis:
    % -Ts: periodo de amostragem;
    % -Fs: frequencia de amostragem;
    % -L: tamanho do vetor de tensoes;
    % -MinPeakHeight: tamanho minimo para o pico de frequencia (componente) ser detectado (2% tensao maxima);
    % -nome_arquivo: nome com o qual o arquivo de dados foi salvo.
    %
    %Restricoes para o nome do arquivo:
    % -Nao pode conter o caractere space.
    %%%%
    %%%%
    %%%%
    #Autor: Gustavo Pinheiro
    #email: gustavo.pinheiro.ebm@gmail.com / gustavopinheirozz@gmail.com
    #versao octave: 8.0

  prompt = 'Digite o nome do arquivo de dados: ';
  arquivo = input(prompt,'s');
  nome_arquivo = arquivo;     %retorna o nome do arquivo de dados em stg para as funcoes de plot
  arquivo = strcat(arquivo,'.csv');
  cabecalho = input('Digite o numero de linhas de cabecalho do aquivo: ');


  dados_original = csvread(arquivo,cabecalho,0); %abre o arquivo de dados csv
                                          %pula as duas primeiras linhas (cabecalho)

  numero_vetores_tensoes = size(dados_original,2) -1; %retorna o numero de vetores de tensoes
                %(numero de sinais-canais) presentes nos dados obtidos pelo osciloscopio.
                  % -1: a primeira coluna eh vetor tempo

  vetor_tempo = dados_original(:,1);  %vetor de tempo (coluna 1 dos dados)
  vetor_tempo_plot = vetor_tempo.*1000000;  %vetor de tempo em us

  for idx=1:numero_vetores_tensoes
    vetor_tensao(:,idx) = dados_original(:,idx+1); %vetor de tensoes (salva canais)
    vetor_tensao_plot(:,idx) = vetor_tensao(:,idx).*1000; %vetor de tensoes em mV
  endfor

  Ts = abs(vetor_tempo(11)-vetor_tempo(10)); %periodo de amostragem
  Fs = 1/Ts; %frequencia de amostragem

  L = length(vetor_tensao); %tamanho do vetor de tensoes


  %%% predifinicoes para fft
  maximo = max(dados_original);
  MinPeakHeight=(0.02*maximo(2)).*1000; %tamanho minimo para o pico de frequencia
                                          %(componente) ser detectado
                                            %(2% tensao maxima)

end


