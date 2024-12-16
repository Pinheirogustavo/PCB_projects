function  [] = plot_dados()
  %help of function

  predefinicoes;

  [dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight,nome_arquivo] = abre_dados;

  plot(vetor_tempo_plot,vetor_tensao_plot) %tempo em us ; tensoes em mV
  set(gca,'FontSize',16)
  xlabel('t(us)','FontSize',18)
  ylabel('amplitude(mV)','FontSize',18)
  title(['Sinal capturado no osciloscopio - ', nome_arquivo])

    nome_arquivo = strcat(nome_arquivo,'_plot_dados_originais.pdf');
    print(nome_arquivo,"-S1500,1500","-F:5")
end


