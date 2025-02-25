/*
 * Biblioteca para uso do ADC do STM32F103.
 * 
 * Modo Dual Channel:
 *  - até 6 canais por ADC;
 * 
 * Escrito por: Erick León
 * 
 * Referências:
 * 
 * [1] STM32F10xxx Reference Manual (RM0008), disponível em www.st.com;
 * [2] Application note (AN3116), STM32's ADC modes and theis applications, disponível em www.st.com;
 * [3] Problems with regular simultaneous dual ADC conversion with DMA transfer, Spark Logic Forum,
 * disponível em https://sparklogic.ru/arduino-for-stm32/problems-with-regular-simultaneous-dual-adc.html
 * [4] https://github.com/rogerclarkmelbourne/Arduino_STM32/blob/master/STM32F1/libraries/STM32ADC/src/STM32ADC.cpp
 * 
 */


#include <libmaple/dma.h>


//////////////////////////////////////////////////////////////////////////////////////////////
// Cálculo do ADC_SQR3 (ADC regular sequence register 3). Ver [1], pág 249.
// Função baseada em [3].
// Calculate values for SQR3. Function could be extended to also work for SQR2 and SQR1.
// There are 6 available sequences in SQR3 (SQR2 also 6, and 4 in SQR1).
// As is, you can sequence only 6 sequences per ADC.
//
uint32 calc_adc_SQR3(uint8 adc_sequence[6]){
  int SQR3=0;

  for (int i=0;i<6;i++)     
  {
    //each sequence is 5 bits
    SQR3 |= adc_sequence[i] << ((i*5));  
  } 
  return SQR3;
} 


//////////////////////////////////////////////////////////////////////////////////////////////
// Inicializa DMA1, canal 1 (ADC1), para uso em dual_channel (32bits)
// Função baseada em [3].
// Argumentos:
//   - data32: buffer to hold samples, ADC1 16bit, ADC2 16 bit. Tamanho (BufLen+1). [ToDo: Verificar se +1 é necessário]
//   - BufLen: number of samples for each ADCx. Each channel will be sampled NUM_SAMPLES/CHANNELS_PER_ADC.
//
void set_dma_dual_channel(uint32 *data32,  uint16 BufLen) {
  dma_init(DMA1);
  // adc_dma_enable() não parece necessário, mas é utilizado em [4]; [ToDo: Verificar...]
  //adc_dma_enable(ADC1);
  dma_setup_transfer(DMA1, DMA_CH1, &ADC1->regs->DR, DMA_SIZE_32BITS, data32, DMA_SIZE_32BITS, DMA_MINC_MODE);
  dma_set_num_transfers(DMA1, DMA_CH1, BufLen);
  dma_set_priority(DMA1, DMA_CH1, DMA_PRIORITY_VERY_HIGH);
  dma_enable(DMA1, DMA_CH1);
}



//////////////////////////////////////////////////////////////////////////////////////////////
// calibrate ADC1 and ADC2, then set all registers for regular simultaneous dual ADC conversion with DMA transfer
// Função baseada em [3].
// Argumentos:
//   - ADC_Prescaler_divider: Prescaler do ADC. "RCC_ADCPRE_PCLK_DIV_2", "RCC_ADCPRE_PCLK_DIV_4", "RCC_ADCPRE_PCLK_DIV_6" ou "RCC_ADCPRE_PCLK_DIV_8".
//   - smp_rate: ADC sample Rate. "ADC_SMPR_XXX", onde XXX é "1_5", "7_5", "13_5", "28_5", "41_5", "55_5", "71_5", ou "239_5".
//   - ChannelsPerADC: number of channels for each ADC. Must match values in ADCx_Sequence array below
//   - ADC1_Sequence: ADC1 channels sequence, left to right. Unused values must be 0. Note that these are ADC channels, not pins
//   - ADC2_Sequence: ADC2 channels sequence, left to right. Unused values must be 0
//   - Fast_Interleave_Mode: Set scan mode. Se 'false', habilita "Regular simultaneous mode". Se 'true', habilita "Fast interleaved mode". Ver [2], págs 9 e 10.
//
void set_adc_dual_channel(uint32 ADC_Prescaler_divider, adc_smp_rate smp_rate, uint8 ChannelsPerADC, uint8 ADC1_Sequence[6], uint8 ADC2_Sequence[6], bool Fast_Interleave_Mode) {

  //set all used pins as INPUT_ANALOG
  for (int i=0;i<ChannelsPerADC;i++){
    pinMode(ADC1_Sequence[i],INPUT_ANALOG);
    pinMode(ADC2_Sequence[i],INPUT_ANALOG);
  }

  // sets sample rate for all channels, all identical (critical in dual mode, even if only pairs sampled together need to be identical)
  rcc_set_prescaler(RCC_PRESCALER_ADC, ADC_Prescaler_divider);
  adc_set_sample_rate(ADC1, smp_rate);
  adc_set_sample_rate(ADC2, smp_rate);

  //adc_calibrate(ADC1);
  //adc_calibrate(ADC2);

  // Set scan mode.
  // Ver página 238 do "Reference Manual"
  ADC1->regs->CR1 = 1 << 8;  
  if (Fast_Interleave_Mode){
    ADC1->regs->CR1 |= 7 << 16;      // Fast interleaved mode. Required for ADC1 only, ADC2 is slave
  }
  else {
    ADC1->regs->CR1 |= 6 << 16;      // Regular simultaneous mode. Required for ADC1 only, ADC2 is slave
  }
  
  
  ADC1->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_DMA | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0102; cont conversion, DMA, right aligned, disable external; EXTSEL, exttrig=0,jswstart=0

    
  adc_set_reg_seqlen(ADC1, ChannelsPerADC);  // how many channels per ADC
  //ADCx->regs->SQR3-1 holds the sequence of channels to convert. A conversion function is provided calc_adc_sequence(ADC1_Sequence) only for SQR3. 
  //If more than 6 channels are needed, repeat the same for SQR2 and SQR1 (SQR1 only holds 4 sequences)
  ADC1->regs->SQR3 |= calc_adc_SQR3(ADC1_Sequence);                //200; for IN8 and IN6, on Maple Mini these are D3, D5

  ADC2->regs->CR1 = 1 << 8;  // Set scan mode 
  ADC2->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0003; 

  adc_set_reg_seqlen(ADC2, ChannelsPerADC);
  ADC2->regs->SQR3 |= calc_adc_SQR3(ADC2_Sequence);                //= 167 forIN7 and IN5, on Maple Mini these are D4, D6 respectively

  ADC1->regs->CR2 |= ADC_CR2_ADON;  // it is critical to enable ADC (bit 0=1) independently of all other changes to the CR2 register
  ADC2->regs->CR2 |= ADC_CR2_ADON;  // enabling all at once (i.e. ADC_CR2_ADON | ADC_CR2_CONT | ADC_CR2_EXTSEL ) will cause problems when used with continuous mode

  delay(50);
  adc_calibrate(ADC1);
  adc_calibrate(ADC2);
}



//////////////////////////////////////////////////////////////////////////////////////////////
// set only the registers that need to be reset before each conversion
// Função baseada em [3].
//
void adc_to_ready_dual_channel() {
  ADC1->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_DMA | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0102; cont conversion, DMA, right aligned, disable external; EXTSEL, exttrig=0,jswstart=0
  ADC2->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0002; 
  ADC1->regs->CR2 |= ADC_CR2_ADON;  // it is critical to enable ADC (bit 0=1) independently of all other changes to the CR2 register
  ADC2->regs->CR2 |= ADC_CR2_ADON;  // enabling all at once (i.e. ADC_CR2_ADON | ADC_CR2_CONT | ADC_CR2_EXTSEL ) will cause problems when used with continuous mode   
}




//////////////////////////////////////////////////////////////////////////////////////////////
// check for DMA transfer finished, resetting isr bit
// Função baseada em [3].
//
uint8 dma_transfer_finished() {
  if(dma_get_isr_bits(DMA1,DMA_CH1)==0x07) {
    int result=dma_get_irq_cause(DMA1,DMA_CH1);//<--clears isr bits
    return 1;
  }
  return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////
// Inicializa a conversão do ADC em Dual Channel
// Função baseada em [3].
// Argumentos:
//   - data32: buffer to hold samples, ADC1 16bit, ADC2 16 bit. Tamanho (BufLen+1). [ToDo: Verificar se +1 é necessário]
//   - BufLen: number of samples for each ADCx. Each channel will be sampled NUM_SAMPLES/CHANNELS_PER_ADC.
//
void start_convertion_dual_channel(uint32 *data32,  uint16 BufLen){
  // it is critical to set ADC before DMA, to avoid partial DMA transfers being stored.
  // If the ADC is in continuous mode while DMA is being set
  // the DMA transfer will be triggered and the DMA counter will start from the wrong value.
  adc_to_ready_dual_channel();
  set_dma_dual_channel(data32, BufLen);

  //start conversion, STM32 will reset this bit immediately. Only ADC1 (master) needs to be started
  ADC1->regs->CR2 |= ADC_CR2_SWSTART;
}



//////////////////////////////////////////////////////////////////////////////////////////////
// Espera finalização da conversão
void wait_convertion_dual_channel(){
  while(!dma_transfer_finished());
  dma_disable(DMA1,DMA_CH1); //stop dma transfer
}



//////////////////////////////////////////////////////////////////////////////////////////////
