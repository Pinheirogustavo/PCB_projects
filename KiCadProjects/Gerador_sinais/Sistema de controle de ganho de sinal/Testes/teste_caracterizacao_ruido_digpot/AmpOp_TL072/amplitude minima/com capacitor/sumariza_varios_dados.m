function  [] = sumariza_varios_dados()
  %help of function

  predefinicoes;

[dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight,nome_arquivo] = abre_dados;



t=nome_arquivo;
i=1;
while(t !='1')

words(i,1)={t};
%%%%%%%%%%%%%%%%%%%%%%%%% Tensao pico a pico%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%PeakToPeak_Amplitude = max(abs(dados_original))*2 - mean(dados_original)*2
pico_a_pico = peak2peak(dados_original);
fprintf('tensao pico a pico(V): %f\n', pico_a_pico(2));
memoria(i,1)=pico_a_pico(2);

%%%%%%%%%%%%%%%%%%%%%%%%% amplitude %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fprintf('amplitude do sinal(V): %f\n', pico_a_pico(2)/2);
memoria(i,2)=pico_a_pico(2)/2;

%%%%%%%%%%%%%%%%%%%%%%%%% Tensao rms%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

RMS_Amplitude = sqrt(mean(dados_original.^2));
fprintf('tensao RMS(V): %f\n', RMS_Amplitude(2));
memoria(i,3)=RMS_Amplitude(2);

%%%%%%%%%%%%%%%%%%%%%%%%% maximo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

maximo = max(dados_original);
fprintf('tensao maxima(V): %f\n', maximo(2));
memoria(i,4)=maximo(2);

%%%%%%%%%%%%%%%%%%%%%%%%% minimo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
minimo = min(dados_original);
fprintf('tensao minima(V): %f\n', minimo(2));
memoria(i,5)=minimo(2);

%%%%%%%%%%%%%%%%%%%%%%%%% media %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
media = mean(dados_original);
fprintf('tensao media(V): %f\n', media(2));
memoria(i,6)=media(2);

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
i=i+1;
    prompt = 'Digite o nome do arquivo de dados: ';
  t = input(prompt,'s');
     endwhile

clc;

diary('sumariza_varios_dados.txt')
diary on

for p=1:i-1
  disp(words(p,1));
    disp(memoria(p,1));
    disp(memoria(p,2));
    disp(memoria(p,3));
    disp(memoria(p,4));
    disp(memoria(p,5));
    disp(memoria(p,6));
endfor



diary off

end


