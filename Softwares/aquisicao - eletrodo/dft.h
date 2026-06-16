/* **********************************************************************
 * Biblioteca com funções para cálculo de uma
 * componente da DFT de um sinal qualquer.
 * **********************************************************************/

/* **********************************************************************
 * Calcula o valor médio de um sinal.
 * Corresponde ao offset no caso de ciclos completos.
 * **********************************************************************/
float sinal_medio (uint16_t *data, int n_pontos){
  float media = 0;
  for (int i=0; i<n_pontos; i++){
    media = media + data[i];
  }
  media = media/n_pontos;
  return media;
}


/* **********************************************************************
 * Calcula a amplitude e fase de um sinal em uma dada frequência a
 * partir da componente da DFT nessa frequência.
 * É possível adicionar zeros ao sinal (zero-padding) para aumentar a
 * resolução em frequência da DFT.
 * **********************************************************************/
void calc_dft_singfreq(uint16_t *data,float freq, float sample_freq, float media, float &amplit, float &phase, int factor_z, int n_pontos){

  float Freal = 0;        
  float Fimag = 0;
  int nreal   = n_pontos;               // número de pontos do sinal
  long int n  = nreal*factor_z;         // número de pontos após o zero-padding                 
  float df    = sample_freq/((float)n); // definindo a df entre 2 amostras subsequentes da DFT
  float k     = round(freq/df);         // definindo k em termos de frequencia de amostragem e frequencia do sinal

  for (int m = 0; m<nreal; m++){        // somatória da DFT
    Freal = Freal + (data[m]-media)*cos(k*m*2.0*M_PI/n); // componente real
    Fimag = Fimag + (data[m]-media)*sin(k*m*2.0*M_PI/n); // componente imaginária
  }
  amplit = (sqrt(pow(Freal,2)+pow(Fimag,2))/(nreal/2.0))*3.3/4096.0; // cálculo da amplitude
  phase = atan2(Fimag,Freal);                                        // cálculo da fase
  if (phase > 3.141529) phase -= 2*3.141529;
  if (phase <= -3.141529) phase += 2*3.141529;
  
}
