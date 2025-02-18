function  [] = sumariza_dados()
%[] = sumariza_dados()
  %
  %funcao 'sumariza_dados': permite obter sumario dos dados obtidos por osciloscopio.
  %
  %Retorna: nada.
  %
  %Exibe no prompt de comando os seguintes dados do canal desejado:
    % - Tensao pico a pico (V);
    % - Amplitude do sinal(V);
    % - Tensao RMS(V);
    % - Tensao maxima(V);
    % - Tensao minima(V);
    % - Tensao media(V);
    % - Em relacao aos picos da fft considerados na analise (>2% tensao maxima):
          % - Amplitude(V) e frequencia(kHz).
    %
    % Gera um arquivo 'nome_do_arquivo_sumario.txt' com todos os dados exibidos no prompt de comando.
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

canal = input('Digite o numero do canal a ser analisado: ');

nome_txt = strcat(nome_arquivo,'_sumario.txt'); %comandos para salvar txt
diary(nome_txt)                                 %com os resultados sumarizados
diary on

%%%%%%%%%%%%%%%%%%%%%%%%% Tensao pico a pico%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%PeakToPeak_Amplitude = max(abs(dados_original))*2 - mean(dados_original)*2
pico_a_pico = peak2peak(vetor_tensao(:,canal));
fprintf('tensao pico a pico(V): %f\n', pico_a_pico);

%%%%%%%%%%%%%%%%%%%%%%%%% amplitude %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fprintf('amplitude do sinal(V): %f\n', pico_a_pico/2);

%%%%%%%%%%%%%%%%%%%%%%%%% Tensao rms%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

RMS_Amplitude = sqrt(mean(vetor_tensao(:,canal).^2));
fprintf('tensao RMS(V): %f\n', RMS_Amplitude);

%%%%%%%%%%%%%%%%%%%%%%%%% maximo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

maximo = max(vetor_tensao(:,canal));
fprintf('tensao maxima(V): %f\n', maximo);

%%%%%%%%%%%%%%%%%%%%%%%%% minimo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
minimo = min(vetor_tensao(:,canal));
fprintf('tensao minima(V): %f\n', minimo);
%%%%%%%%%%%%%%%%%%%%%%%%% media %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
media = mean(vetor_tensao(:,canal));
fprintf('tensao media(V): %f\n', media);

%%%%%%%%%%%%%%%%%%%%%%%%% frequencias presentes %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  Y = fft(vetor_tensao(:,canal)); %computes the discrete Fourier transform of vetor_tensao

    P2 = abs(Y/L);
    P1 = P2(1:L/2+1);
    P1 = P2(1:L/2+1).*1000;       %em mX;
    P1(2:end-1) = 2*P1(2:end-1);

    f = Fs/L*(0:(L/2));

    [pks,locs] = findpeaks(P1,"MinPeakHeight",MinPeakHeight);
        %{
        retorna os picos (pks) e suas posicoes (locs) do sinal
        %dois picos consecutivos sao distintos se a distancia entre eles for maior
        do que 2 segundos
        %}

    fprintf('Componentes presentes significativas (2@amplitudeMaxima): \n');

     idx = length(pks);
     for i = 1:idx
       pico =  f(locs(i))/1000 ;%kHz

       fprintf('frequencia (kHz): %f\n', pico);
       fprintf('amplitude (V): %f\n', pks(i)/1000);
     end


diary off

end


