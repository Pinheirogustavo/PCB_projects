function  [] = plot_dados()
  %[] = plot_dados()
  %
  %funcao 'plot_dados': plota todos os canais obtidos por osciloscopio.
    %
    % Gera um arquivo 'nome_do_arquivo_plot_dados_originais.pdf' com os graficos dos canais capturados por osciloscopio.
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


numero_vetores_tensoes = size(vetor_tensao_plot,2); %retorna o numero de vetores de tensoes
                %(numero de sinais-canais) presentes nos dados obtidos pelo osciloscopio.

  for idx=1:numero_vetores_tensoes
    plot(vetor_tempo_plot, vetor_tensao_plot(:,idx)) % tensoes em mV
    hold on;
    legends{idx} = sprintf('Canal %d',idx);
  endfor


  set(gca,'FontSize',16)
  %plot(vetor_tempo_plot,vetor_tensao_plot) %tempo em us ; tensoes em mV
  set(gca,'FontSize',16)
  xlabel('t(us)','FontSize',18)
  ylabel('amplitude(mV)','FontSize',18)
  title(['Sinal capturado no osciloscopio - ', nome_arquivo])
  legend(legends) % Display all the legend texts.
  hold off;

  nome_arquivo = strcat(nome_arquivo,'_plot_dados_originais.pdf');
  print(nome_arquivo,"-S1500,1500","-F:10")
      %F:?? : tamanho da fonte usada


end


