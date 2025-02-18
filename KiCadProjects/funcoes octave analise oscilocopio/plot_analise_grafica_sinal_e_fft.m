function  [] = plot_analise_grafica_completa()
  %[] = plot_analise_grafica_completa()
  %
  %funcao 'plot_analise_grafica_completa': plota todos os canais obtidos por osciloscopio e a fft do canal desejado.
    %
    % Gera um arquivo 'nome_do_arquivo_plot_analise_grafica_completa.pdf' com os graficos dos canais capturados por osciloscopio e da fft do canal desejado.
    %
    %Retorna: nada.
    %%%%
    %%%%
    %%%%
    #Autor: Gustavo Pinheiro
    #email: gustavo.pinheiro.ebm@gmail.com / gustavopinheirozz@gmail.com
    #versao octave: 8.0

  predefinicoes;

  [dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight,nome_arquivo] = abre_dados;

 canal = input('Digite o numero do canal a ser analisado: ');

    figure(1); %figura 1

    subplot(2,1,1);
    plot(vetor_tempo_plot,vetor_tensao_plot(:,canal)) %tempo em us ; tensoes em mV
    set(gca,'FontSize',16)
    xlabel('t(us)','FontSize',18)
    ylabel('amplitude(mV)','FontSize',18)
    title(['Sinal - ',nome_arquivo])

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FFT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    Y = fft(vetor_tensao(:,canal)); %computes the discrete Fourier transform of vetor_tensao

    %{
    %plot magnitude fft
    subplot(4,1,2);
    plot(Fs/L*(0:L-1),abs(Y),"LineWidth",3)
    title(["Magnitude complexa do espectro da fft - ", nome_arquivo])
    xlabel("f (Hz)")
    ylabel("|fft(X)|")

    %plot espectro fft
    subplot(4,1,3);
    plot(Fs/L*(-L/2:L/2-1),abs(fftshift(Y)),"LineWidth",3)
    title(["fft Spectrum in the Positive and Negative Frequencies - ", nome_arquivo])
    xlabel("f (Hz)")
    ylabel("|fft(sinal)|")
%}

    %plot freqs fft e picos
    P2 = abs(Y/L);
    P1 = P2(1:L/2+1);
    P1 = P2(1:L/2+1).*1000;       %em mX;
    P1(2:end-1) = 2*P1(2:end-1);

    f = Fs/L*(0:(L/2));

    %MinPeakHeight=0.001.*1000; %tamanho minimo para o pico ser detectado (1mV)
    [pks,locs] = findpeaks(P1,"MinPeakHeight",MinPeakHeight);
        %{
        retorna os picos (pks) e suas posicoes (locs) do sinal
        %dois picos consecutivos sao distintos se a distancia entre eles for maior
        do que 2 segundos
        %}

    subplot(2,1,2);

    plot(f,P1 )
    hold on

    %title(["Single-Sided Amplitude Spectrum of X(t) - ", nome_arquivo])
    title(["Espectro de amplitudes unilateral X(t) - ", nome_arquivo])

    xlabel("f (Hz)")
    ylabel("|sinal|(mV)")

     idx = length(pks);
     for i = 1:idx
       plot(f(locs(i)),pks(i), "o" )
       pico =  f(locs(i))/1000 ;%kHz
       legends{1} = sprintf('fft signal');
       legends{i+1} = sprintf('frequencia (kHz): %d', pico);
    end
    legends{i+1} = sprintf('frequencia (kHz): %d', pico);

    legend(legends) % Display all the legend texts.

    x_limit = ceil(log(abs(f(locs(i))))./log(10)); %devolve a ordem da frequencia
                                                     %do ultimo pico observado
    axis([0 f(locs(i))+10^(x_limit) ]) %forca o eixo 'x' a ficar uma ordem de
                                        %grandeza acima do ultimo pico
    grid on;

    hold off

    nome_arquivo = strcat(nome_arquivo,'_plot_analise_grafica_completa.pdf');
    print(nome_arquivo,"-S850,450","-F:10")
        %F:?? : tamanho da fonte usada



end
