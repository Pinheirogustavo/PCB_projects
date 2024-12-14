function  [] = plot_dados()
  %help of function

  predefinicoes;

  [dados_original,vetor_tempo,vetor_tempo_plot,vetor_tensao,vetor_tensao_plot,Ts,Fs,L,MinPeakHeight] = abre_dados;

  plot(vetor_tempo_plot,vetor_tensao_plot) %tempo em us ; tensoes em mV
  set(gca,'FontSize',16)
  xlabel('t(us)','FontSize',18)
  ylabel('amplitude(mV)','FontSize',18)
  title('Sinal capturado no osciloscopio')

  print -dpdfwrite 'dados.pdf' "-S1500,1500" "-F:5"

end


