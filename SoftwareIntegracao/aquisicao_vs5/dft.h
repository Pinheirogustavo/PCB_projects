/*
    dft.h
    Versão 1 
    Autora: Mirela de Oliveira Tomazini
    Última atualização: 19 de agosto de 2021
    Descrição: O objetivo desse código e o desenvolvimento de funcoes que envolvam a transformada discreta de Fourier
*/


float sinal_medio (uint16_t *data){
  // a funcao recebe o vetor de dados e adquiridos e calcula o valor medio.
  float media = 0;
  for (int i=0; i<NUM_SAMPLES; i++){
    media = media + data[i];
  }
  media = media/NUM_SAMPLES;
  return media;
} 


double calc_dft_singfreq(uint16_t *data,float freq, float sample_freq, float media, int factor_z=1, float pontos=NUM_SAMPLES){
  
  double Freal     = 0;        
  double Fimag     = 0;
  double amplit    = 0;
  float phase     = 0;
  float nreal     = pontos;                           //definindo o tamanho do vetor, ou seja, quantidade de dados 
  float n         = nreal*factor_z;                   // criando um n que é produto da quantidade real de pontos e o fator z
  float df        = sample_freq/n;                    // definindo a df entre 2 amostras subsequentes (em frequencia)
  float k         = round(freq/df);                   // definindo k em termos de frequencia de amostragem e frequencia do sinal

  for (int m = 0; m<nreal; m++){
    Freal = Freal + (data[m]-media)*cos(k*m*2.0*M_PI/n);
    Fimag = Fimag + (data[m]-media)*sin(k*m*2.0*M_PI/n);
  }
  amplit = (sqrt(pow(Freal,2)+pow(Fimag,2))/(nreal/2.0))*3.3/4096.0;
  phase = atan2(Fimag,Freal);

  Serial.print(freq);
  Serial.print(" ");
  Serial.println(amplit, 7);
  
  return amplit;

}

float search_fpeak (uint16_t *data,float f_peak, float sample_freq, int factor = 10000, float faixa = 0.1, int n_p = 50, int pontos = NUM_SAMPLES){
  // funcao procura pelo frequencia de pico 
  float media = 0;
  media = sinal_medio(data);
  
  int sttep       = (f_peak*faixa)/(n_p/2);
  int num         = ((f_peak*(1+faixa))-(f_peak*(1-faixa)))/sttep;
  
  float freq_value[num];
  float freq_datadft[num];
  
  float f_peak_real = 0;
  float peak        = 0;

  

  for(int cont=0; cont<num; cont++){
    freq_value[cont]    = (f_peak*(1-faixa)) + cont*sttep;
    freq_datadft[cont]  = calc_dft_singfreq(data,freq_value[cont],sample_freq,media,factor, pontos);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft[cont]>peak){
      peak          = freq_datadft[cont];
      f_peak_real   = freq_value[cont];
    }
  }

  return f_peak_real;

}


float search_fpeak_initial (uint16_t *data, float sample_freq, int factor = 10000, int n_p = 50, float f_peak_i = 100, float f_peak_f =20000,float sttep = 100, float pontos=NUM_SAMPLES){
  float media = 0;
  media = sinal_medio(data);
  int num         = (f_peak_f-f_peak_i)/sttep;
  float f_peak_real = 0;
  float peak        = 0;

  float freq_value[num];
  float freq_datadft[num];
  

  for(int cont=0; cont<num; cont++){
    freq_value[cont]    = f_peak_i + cont*sttep;
    freq_datadft[cont]  = calc_dft_singfreq(data,freq_value[cont],sample_freq,media,factor,pontos);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft[cont]>peak){
      peak          = freq_datadft[cont];
      f_peak_real   = freq_value[cont];
    }
    
  }
  //Serial.print(peak, 6);
  //Serial.print(" *** ");
  //Serial.println(f_peak_real, 2);

  return f_peak_real;

}
float search_fpeak_initial_faster (uint16_t *data, float sample_freq, float fpeak){
  // funcao procura pelo frequencia de pico na inicialização do programa

  float minim       = 0;

  if (1==2){
    
    if((fpeak-40000)>0){
      minim = fpeak-40000;
    }
    
    fpeak = search_fpeak_initial (data, sample_freq, 10000, 50, minim, fpeak+40000,10000); //realiza 8 calculos
    
    if((fpeak-10000)>0){
      minim = fpeak-10000;
    }
    
    fpeak = search_fpeak_initial (data, sample_freq, 10000, 50, minim, fpeak+10000,1000); //realiza 10 calculos

  }
  if((fpeak-1000)>0){
    minim = fpeak-1000;
  }
  fpeak = search_fpeak_initial (data, sample_freq, 10000, 50, minim, fpeak+1000,100); //realiza 10 calculos
  
  if((fpeak-100)>0){
    minim = fpeak-100;
  }
  fpeak = search_fpeak_initial (data, sample_freq, 10000, 50, minim, fpeak+100,10); //realiza 10 calculos
  
  if((fpeak-10)>0){
    minim = fpeak-10;
  }
  fpeak = search_fpeak_initial (data, sample_freq, 10000, 50, minim, fpeak+10,1); //realiza 10 calculos

  return fpeak;
}

/*
float test1 (uint16_t *data, float sample_freq, int factor = 10000, int n_p = 50, float f_peak_i = 100, float f_peak_f =3000,float sttep = 100, float pontos=NUM_SAMPLES){
  float media = 0;
  media = sinal_medio(data);
  int num         = (f_peak_f-f_peak_i)/sttep;
  
  float f_peak_real0 = 0;
  float peak0        = 0;
  float freq_value0[num];
  float freq_datadft0[num];
  

  for(int cont=0; cont<num; cont++){
    freq_value0[cont]    = f_peak_i + cont*sttep;
    freq_datadft0[cont]  = calc_dft_singfreq(data,freq_value0[cont],sample_freq,media,factor,6000);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft0[cont]>peak0){
      peak0          = freq_datadft0[cont];
      f_peak_real0   = freq_value0[cont];
    }
    
  }
  Serial.print(peak0, 6);
  Serial.print(" ******** ");
  Serial.print(f_peak_real0, 2);
  Serial.print(" ");

  float f_peak_real1 = 0;
  float peak1        = 0;
  float freq_value1[num];
  float freq_datadft1[num];


  for(int cont=0; cont<num; cont++){
    freq_value1[cont]    = f_peak_i + cont*sttep;
    freq_datadft1[cont]  = calc_dft_singfreq(data,freq_value1[cont],sample_freq,media,factor,3000);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft1[cont]>peak1){
      peak1          = freq_datadft1[cont];
      f_peak_real1   = freq_value1[cont];
    }
    
  }

  Serial.print(peak1, 6);
  Serial.print(" ******** ");
  Serial.print(f_peak_real1, 2);
  Serial.print(" ");

  float f_peak_real2 = 0;
  float peak2        = 0;
  float freq_value2[num];
  float freq_datadft2[num];

  
  for(int cont=0; cont<num; cont++){
    freq_value2[cont]    = f_peak_i + cont*sttep;
    freq_datadft2[cont]  = calc_dft_singfreq(data,freq_value2[cont],sample_freq,media,factor,600);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft2[cont]>peak2){
      peak2          = freq_datadft2[cont];
      f_peak_real2   = freq_value2[cont];
    }
    
  }

  Serial.print(peak2, 6);
  Serial.print(" ******** ");
  Serial.print(f_peak_real2, 2);
  Serial.print(" ");
  

  float f_peak_real3 = 0;
  float peak3        = 0;
  float freq_value3[num];
  float freq_datadft3[num];

  for(int cont=0; cont<num; cont++){
    freq_value3[cont]    = f_peak_i + cont*sttep;
    freq_datadft3[cont]  = calc_dft_singfreq(data,freq_value3[cont],sample_freq,media,factor,300);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft3[cont]>peak3){
      peak3          = freq_datadft3[cont];
      f_peak_real3   = freq_value3[cont];
    }
    
  }

  Serial.print(peak3, 6);
  Serial.print(" ******** ");
  Serial.print(f_peak_real3, 2);
  Serial.print(" ");

  
  float f_peak_real4 = 0;
  float peak4        = 0;
  float freq_value4[num];
  float freq_datadft4[num];

  for(int cont=0; cont<num; cont++){
    freq_value4[cont]    = f_peak_i + cont*sttep;
    freq_datadft4[cont]  = calc_dft_singfreq(data,freq_value4[cont],sample_freq,media,factor,60);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft4[cont]>peak4){
      peak4          = freq_datadft4[cont];
      f_peak_real4   = freq_value4[cont];
    }
    
  }

  Serial.print(peak4, 6);
  Serial.print(" ******** ");
  Serial.print(f_peak_real4, 2);
  Serial.print(" ");


  
  
  float f_peak_real5 = 0;
  float peak5        = 0;
  float freq_value5[num];
  float freq_datadft5[num];

  for(int cont=0; cont<num; cont++){
    freq_value5[cont]    = f_peak_i + cont*sttep;
    freq_datadft5[cont]  = calc_dft_singfreq(data,freq_value5[cont],sample_freq,media,factor,30);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft5[cont]>peak5){
      peak5          = freq_datadft5[cont];
      f_peak_real5   = freq_value5[cont];
    }
    
  }

  Serial.print(peak5, 6);
  Serial.print(" ******** ");
  Serial.print(f_peak_real5, 2);
  Serial.print(" ");

  float f_peak_real6 = 0;
  float peak6        = 0;
  float freq_value6[num];
  float freq_datadft6[num];

  for(int cont=0; cont<num; cont++){
    freq_value6[cont]    = f_peak_i + cont*sttep;
    freq_datadft6[cont]  = calc_dft_singfreq(data,freq_value6[cont],sample_freq,media,factor,3);
  }
  
  for(int cont=0; cont<num; cont++){
    if(freq_datadft6[cont]>peak6){
      peak6          = freq_datadft6[cont];
      f_peak_real6   = freq_value6[cont];
    }
    
  }

  Serial.print(peak6, 6);
  Serial.print(" ******** ");
  Serial.print(f_peak_real6, 2);
  Serial.println(" DADOS ");

  if(1==2){
    for (int i=0; i<6000; i++){
      Serial.print(data[i]);
      Serial.print(" ");
    }
    
    Serial.println(" ");
  }
  return f_peak_real6;

}*/
