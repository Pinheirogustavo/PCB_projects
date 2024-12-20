#Octave 7.1.0
#Autor: Gustavo Pinheiro

%%%%%%%%%%%%%%%%%%%%%%%%%%%% Descricao do codigo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%{
xxxxxxxx
%}

#pre-defifinicoes do octave
clear all; more off;clc; close all; %limpa o ambiente de trabalho
pkg load control; pkg load signal;  %carrega pacotes


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Dados %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



dados_original = csvread('dados.csv',2,0); %abre o arquivo de dados csv
                                        %pula as duas primeiras linhas (cabecalho)

vetor_tempo = dados_original(:,1);  %vetor de tempo (coluna 1 dos dados)
vetor_tempo_plot = vetor_tempo.*1000000;  %vetor de tempo em us

vetor_tensao = dados_original(:,2); %vetor de tensoes (coluna 2 dos dados)
vetor_tensao_plot = vetor_tensao.*1000; %vetor de tensoes em mV


Ts = abs(vetor_tempo(11)-vetor_tempo(10)); %periodo de amostragem
Fs = 1/Ts; %frequencia de amostragem

L = length(vetor_tensao); %tamanho do vetor de tensoes

%%%%%%%%%%%%%%%%%%%%%%%%%% plot dos dados %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(1); %figura 1

subplot(5,1,1);
plot(vetor_tempo_plot,vetor_tensao_plot)
set(gca,'FontSize',16)
xlabel('t(us)','FontSize',18)
ylabel('amplitude(mV)','FontSize',18)
title('Ruido proviniente do circuito de ganho baseado em digpot')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FFT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Y = fft(vetor_tensao); %computes the discrete Fourier transform of vetor_tensao

%plot magnitude fft
subplot(5,1,2);
plot(Fs/L*(0:L-1),abs(Y),"LineWidth",3)
title("Magnitude complexa do espectro da fft")
xlabel("f (Hz)")
ylabel("|fft(X)|")

%plot espectro fft
subplot(5,1,3);
plot(Fs/L*(-L/2:L/2-1),abs(fftshift(Y)),"LineWidth",3)
title("fft Spectrum in the Positive and Negative Frequencies")
xlabel("f (Hz)")
ylabel("|fft(sinal)|")



%plot freqs fft
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1 = P2(1:L/2+1).*1000;       %em mX;
P1(2:end-1) = 2*P1(2:end-1);

subplot(5,1,4);

%plot picos
f = Fs/L*(0:(L/2));
plot(f,P1,"LineWidth",3)
title("Single-Sided Amplitude Spectrum of X(t)")
xlabel("f (Hz)")
ylabel("|sinal|")

axis([0 3e6])

MinPeakHeight=0.001.*1000;

[pks,locs] = findpeaks(P1,"MinPeakHeight",MinPeakHeight);
    %{
    retorna os picos (pks) e suas posicoes (locs) do sinal
    %dois picos consecutivos sao distintos se a distancia entre eles for maior
    do que 2 segundos
    %}

subplot(5,1,5);

plot(f,P1 )
hold on

title("Single-Sided Amplitude Spectrum of X(t)")
xlabel("f (Hz)")
ylabel("|sinal|")

 idx = length(pks);
 for i = 1:idx
   plot(f(locs(i)),pks(i), "o" )
   pico =  f(locs(i))/1000 ;%kHz
   legends{1} = sprintf('fft signal');
   legends{i+1} = sprintf('frequencia (kHz): %d', pico);
end
legends{i+1} = sprintf('frequencia (kHz): %d', pico);

legend(legends) % Display all the legend texts.

axis([0 3e6])

hold off

print -dpdfwrite 'ruido.pdf' "-S1500,6000" "-F:5"


