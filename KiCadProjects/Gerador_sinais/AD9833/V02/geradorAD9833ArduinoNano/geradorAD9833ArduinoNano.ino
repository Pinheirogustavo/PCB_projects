//Esquema ligacao SPI https://www.electroniclinic.com/ad9833-programmable-waveform-generator-using-arduino/
// codigo de: https://create.arduino.cc/projecthub/mariogianota/the-ad9833-dds-signal-generator-and-arduino-uno-9286e3
// caso ocorra o erro "avrdude: stk500_getsync() attempt 1 of 10: not in sync: resp=0x00" Tools --> Processor --> ATmega328P (oldbootloader)

#include <AD9833.h>     // Include the library

// Gerador de sinais
    // Existem dois registradores, REG0 REG1, que podem ser programados: 
        //   Signal type - SINE_WAVE, TRIANGLE_WAVE, SQUARE_WAVE, and HALF_SQUARE_WAVE
        //   Frequency - 0 to 12.5 MHz
        //   Phase - 0 to 360 degress (this is only useful if it is 'relative' to some other signal
        //                             such as the phase difference between REG0 and REG1).

#define FNC_PIN 4       // Can be any digital IO pin
AD9833 gen(FNC_PIN);       // Defaults to 25MHz internal reference frequency

void setup() {
   // This MUST be the first command after declaring the AD9833 object
   gen.Begin();     // inicia a sinal senoidal de 1000 Hz  em REG0 fase 0.          
   // Apply a 1 MHz square wave using REG0 (register set 0). There are two register sets,
   // REG0 and REG1. 
   // Each one can be programmed for:
   //   Signal type - SINE_WAVE, TRIANGLE_WAVE, SQUARE_WAVE, and HALF_SQUARE_WAVE
   //   Frequency - 0 to 12.5 MHz
   //   Phase - 0 to 360 degress (this is only useful if it is 'relative' to some other signal
   //           such as the phase difference between REG0 and REG1).
   // In ApplySignal, if Phase is not given, it defaults to 0.
   gen.ApplySignal(SINE_WAVE,REG0,50000);
   gen.EnableOutput(true);   // Turn ON the output - it defaults to OFF
   // There should be a 50 kHz square wave on the PGA output of the AD9833
}

void loop() {
    // To change the signal, you can just call ApplySignal again with a new frequency and/or signal
    // type.
}
