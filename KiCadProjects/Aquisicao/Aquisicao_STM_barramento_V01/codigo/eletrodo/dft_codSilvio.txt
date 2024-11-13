 //////////////////////////////////////////////////////////////////////////////////
float sinal_medio (uint16_t *data, uint16_t pontos){
  float media = 0;
  for (int i=0; i<pontos; i++){
    media = media + data[i];
  }
  media = media/pontos;
  return media;
}

//////////////////////////////////////////////////////////////////////////////////
float calc_dft_singfreq(uint16_t *data, float freq, float sample_freq, float media, long int factor_z, uint16_t pontos, float *phase) {
    float Freal     = 0;        
    float Fimag     = 0;
    float amplit    = 0;
    //float phase     = 0;
    float nreal     = pontos;                          //definindo o tamanho do vetor, ou seja, quantidade de dados 
    float n         = nreal*factor_z;                   
    float df        = sample_freq/n;                   //definindo a df entre 2 amostras subsequentes (em frequencia)
    float k         = round(freq/df);                  // definindo k em termos de frequencia de amostragem e frequencia do sinal
  
    for (int m = 0; m<nreal; m++){
      Freal = Freal + (float(data[m])-media)*cos(k*m*2.0*M_PI/n);
      Fimag = Fimag + (float(data[m])-media)*sin(k*m*2.0*M_PI/n);
    }
    amplit = (sqrt(pow(Freal,2)+pow(Fimag,2))/(nreal/2.0))*3.3/4096.0;
    *phase = atan2(Fimag,Freal);
    
    return amplit;
}

//////////////////////////////////////////////////////////////////////////////////
/*
float search_fpeak_initial (uint16_t *data, float sample_freq, int factor_z, float f_peak_i, float f_peak_f, float f_step, uint16_t pontos, float media){
  if(f_peak_i<0) f_peak_i=0;
  int num         = ((f_peak_f-f_peak_i)/f_step)+1;
  float f_peak_real = 0;
  float peak        = 0;

  float freq_value[num];
  float freq_datadft[num];
  

  for(int cont=0; cont<num; cont++){
    freq_value[cont]    = f_peak_i + cont*f_step;
    freq_datadft[cont]  = calc_dft_singfreq(data, freq_value[cont], sample_freq, media, factor_z, pontos);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft[cont]>peak){
      peak          = freq_datadft[cont];
      f_peak_real   = freq_value[cont];
    }
    
  }
  
  return f_peak_real;
}

//////////////////////////////////////////////////////////////////////////////////
float search_fpeak (uint16_t *data, float sample_freq, uint16_t pontos){
  float media;
  media = sinal_medio(data, pontos);
  float f_step;
  if (pontos>16) f_step = sample_freq/16;
  else f_step = sample_freq/pontos;
  float freq_estimada = search_fpeak_initial(data, sample_freq, 10000, 0, sample_freq/2, f_step, pontos, media); //sample_freq/16  -- 8 pontos

  for (byte idx=0; idx<5; idx++){
      f_step = f_step/8;
      freq_estimada = search_fpeak_initial(data, sample_freq, 10000, freq_estimada-4.0*f_step, freq_estimada+4.0*f_step, f_step, pontos, media); //sample_freq/655.360 ~ 0,3Hz   -- 45 pontos
  }

  return freq_estimada;
}
*/
