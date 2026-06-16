// Funções usadas para debugar o programa...
//
//


void serial_debug(){
  mede_ADC();
  
  for(int i=0;i<(NUM_SAMPLES);i++) {
    Serial.print(datav1[i]);
    Serial.print("\t");        
    Serial.print(datav2[i]);
    Serial.print("\n");        
  }

  Serial.print(amplitude1);
  Serial.print("\t");
  Serial.print(amplitude2);
  Serial.print("\t");
  Serial.print(phase2-phase1);
  Serial.print("\t");
  Serial.print(phase1);
  Serial.print("\t");
  Serial.print(phase2);
  Serial.print("\t");
  Serial.print(sample_freq);
  Serial.print("\t");
  Serial.print(freq_sinal);
  
  Serial.println();

  delay(1000);
}


void imprime_na_serial(){
  Serial.print(amplitude1);
  Serial.print("\t");
  Serial.print(amplitude2);
  Serial.print("\t");
  Serial.print(phase2-phase1);
  Serial.print("\t");
  Serial.print(phase1);
  Serial.print("\t");
  Serial.print(phase2);
  Serial.print("\t");
  Serial.print(sample_freq);
  Serial.print("\t");
  Serial.print(freq_sinal);
  
  Serial.println();
}

void processacomandoserial(){
  int comandoserial = Serial.read();
   
   switch (comandoserial) {
    case 'i': // realiza medidas
      mede_ADC();
      imprime_na_serial();
      break;
      
    case 'o': // envia pontos medidos
      for(int i=0;i<(NUM_SAMPLES);i++) {
        Serial.print(datav1[i]);
        Serial.print("\t");        
        Serial.print(datav2[i]);
        Serial.print("\n");        
      }
      break;
    
    default:
      break;
  }
}

void verifica_serial(){
  if (Serial.available() > 0) {
    processacomandoserial();
  }  
}

