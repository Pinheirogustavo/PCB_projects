/*
 * Funções para uso do gerador de onda senoidal (DDS) AD9850.
 * Baseado em https://www.electrodragon.com/w/AD9850_Module_DDS_Signal_Generator_V2
 * 
 * Autor: Erick León
 * 

#define W_CLK PA5   //  - connect to AD9850 module word load clock pin (CLK)
#define FQ_UD PA4   //  - connect to freq update pin (FQ)
#define DATA  PA3   //  - connect to serial data load pin (DATA)
#define RESET PA2   //  - connect to reset pin (RST)

*/

#define W_CLK PC14   //  - connect to AD9850 module word load clock pin (CLK)
#define FQ_UD PC15   //  - connect to freq update pin (FQ)
#define DATA  PA0   //  - connect to serial data load pin (DATA)
#define RESET PA1   //  - connect to reset pin (RST)

#define _pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); }

// transfers a byte, a bit at a time, LSB first to the 9850 via serial DATA line
void _tfr_byte(byte data){
    for (int i=0; i<8; i++, data>>=1) {
        digitalWrite(DATA, data & 0x01);
        _pulseHigh(W_CLK); //after each bit sent, CLK is pulsed high
    }
}



// frequency calc from datasheet page 8 = <sys clock> * <frequency tuning word>/2^32
void ad9850_sendFrequency(double frequency) {
    int32_t freq = frequency * 4294967295/125000000; // note 125 MHz clock on 9850
    for (int b=0; b<4; b++, freq>>=8) {
        _tfr_byte(freq & 0xFF);
    }
    _tfr_byte(0x000);  // Final control byte, all 0 for 9850 chip
    _pulseHigh(FQ_UD); // Done! Should see output
}

void ad9850_setup() {
    pinMode(FQ_UD, OUTPUT);
    pinMode(W_CLK, OUTPUT);
    pinMode(DATA, OUTPUT);
    pinMode(RESET, OUTPUT);
    _pulseHigh(RESET);
    _pulseHigh(W_CLK);
    _pulseHigh(FQ_UD); // this pulse enables serial mode - Datasheet page 12 figure 10
}
