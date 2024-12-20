function  [] = sumariza_varios_dados()
%[] = sumariza_varios_dados()
  %
  %funcao 'sumariza_varios_dados': permite obter sumario de diferentes dados obtidos por osciloscopio.
  %
  %Retorna: nada.
  %
  %Exibe no prompt de comando os seguintes dados do canal desejado de cada dado:
    % - Nome do dado analisado;
    % - Canal analisado dentro do conjunto de dados considerado;
    % - Tensao pico a pico (V);
    % - Amplitude do sinal(V);
    % - Tensao RMS(V);
    % - Tensao maxima(V);
    % - Tensao minima(V);
    % - Tensao media(V).
    %
    % Gera um arquivo 'nome_do_arquivo_sumariza_varios_dados.txt' com todos os dados exibidos no prompt de comando.
      %
  %ATENCAO: O arquivo .txt gerado adiciona novos dados abaixo dos ja existentes
  %no arquivo .txt presente no mesmo diretorio.
    %%%%
    %%%%
    %%%%
    #Autor: Gustavo Pinheiro
    #email: gustavo.pinheiro.ebm@gmail.com / gustavopinheirozz@gmail.com
    #versao octave: 8.0

  predefinicoes;

[dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight,nome_arquivo] = abre_dados;

canal = input('Digite o numero do canal a ser analisado: '); %numero do canal a
                                                    %ser considerado na primeira analise


t='s'; %variavel para parar as analises (continua == 's' ; para == 'n')
i=1; %variavel para alocacao de dados nos vetores word e memoria
  while(t !='n') %condicao para realizar analises

  words(i,1)={nome_arquivo}; %salva o nome do dado a ser analisado
  words(i,2)={strcat('canal ',num2str(canal))}; %salva o numero do canal que esta sendo analisado

  %%%%%%%%%%%%%%%%%%%%%%%%% Tensao pico a pico%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  %PeakToPeak_Amplitude = max(abs(dados_original))*2 - mean(dados_original)*2
  pico_a_pico = peak2peak(vetor_tensao(:,canal));
  fprintf('tensao pico a pico(V): %f\n', pico_a_pico);
  memoria(i,1)=pico_a_pico; %vetor 'memoria': guarda os dados numericos de interesse

  %%%%%%%%%%%%%%%%%%%%%%%%% amplitude %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  fprintf('amplitude do sinal(V): %f\n', pico_a_pico/2);
  memoria(i,2)=pico_a_pico/2;

  %%%%%%%%%%%%%%%%%%%%%%%%% Tensao rms%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  RMS_Amplitude = sqrt(mean(vetor_tensao(:,canal).^2));
  fprintf('tensao RMS(V): %f\n', RMS_Amplitude);
  memoria(i,3)=RMS_Amplitude;

  %%%%%%%%%%%%%%%%%%%%%%%%% maximo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  maximo = max(vetor_tensao(:,canal));
  fprintf('tensao maxima(V): %f\n', maximo);
  memoria(i,4)=maximo;

  %%%%%%%%%%%%%%%%%%%%%%%%% minimo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  minimo = min(vetor_tensao(:,canal));
  fprintf('tensao minima(V): %f\n', minimo);
  memoria(i,5)=minimo;

  %%%%%%%%%%%%%%%%%%%%%%%%% media %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  media = mean(vetor_tensao(:,canal));
  fprintf('tensao media(V): %f\n', media);
  memoria(i,6)=media;

  %%%%%%%%%%%%%%%%%%%%%%%%% frequencias presentes %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%{  Y = fft(vetor_tensao); %computes the discrete Fourier transform of vetor_tensao
  %{

      P2 = abs(Y/L);
      P1 = P2(1:L/2+1);
      P1 = P2(1:L/2+1).*1000;       %em mX;
      P1(2:end-1) = 2*P1(2:end-1);

      f = Fs/L*(0:(L/2));

      MinPeakHeight=(0.02*maximo(2)).*1000; %tamanho minimo para o pico ser detectado
                                                %(20% tensao maxima)
      [pks,locs] = findpeaks(P1,"MinPeakHeight",MinPeakHeight);
          %{
          retorna os picos (pks) e suas posicoes (locs) do sinal
          %dois picos consecutivos sao distintos se a distancia entre eles for maior
          do que 2 segundos
          %}

      fprintf('Componentes presentes significativas (20@amplitudeMaxima): \n');

       idx = length(pks);
       for i = 1:idx
         pico =  f(locs(i))/1000 ;%kHz

         fprintf('frequencia (kHz): %f\n', pico);
         fprintf('amplitude (V): %f\n', pks(i)/1000);
       end
  %}
  i=i+1; %incremento na variavel para alocacao de dados nos vetores word e memoria

  t = input('Deseja adicionar algum dado? (s ou n) ','s');
    if t=='n'
      break; %termina o loop -->
    end
  [dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight,nome_arquivo] = abre_dados;

  canal = input('Digite o numero do canal a ser analisado: ');


     % prompt = 'Digite o nome do arquivo de dados: ';
    %t = input(prompt,'s');
  end

clc; % <-- apaga o prompt de comando (para nao salvar as mensagens de input no arquivo txt

diary('sumariza_varios_dados.txt') % inicia o arquivo .txt
diary on

%exibe no prompt de comando o nome do arquivo de dados considerado words(:,1)
 %o canal considerado dentro desses dados words(:,2)
  %e os dados numericos de interesse sobre os sinais (memoria)
  for p=1:i-1
    disp(words(p,1));
    disp(words(p,2));
      disp(memoria(p,1));
      disp(memoria(p,2));
      disp(memoria(p,3));
      disp(memoria(p,4));
      disp(memoria(p,5));
      disp(memoria(p,6));
  end

diary off %finaliza o arquivo .txt

end


