#include <Arduino.h>
#include <avr/io.h>

#define F_CPU 16000000

#include <util/delay.h>
#include <avr/interrupt.h>

#define NOP() {__asm__ __volatile__ ("nop");}

#define I2S_SCK  PB2
#define I2S_WS   PB1
#define I2S_SD   PB0
#define DAC_BITS 16

#define INT16_MAX 0x7FFF
#define INT16_MIN 0x8000
#define UINT16_MAX 0xFFFF

#define DEFAULT_BAUD_RATE 9600

unsigned int I2S_SCK_LOW = ~(1 << I2S_SCK);
unsigned int I2S_SCK_HIGH = (1 << I2S_SCK);

unsigned int I2S_WS_LOW = ~(1 << I2S_WS);
unsigned int I2S_WS_HIGH = (1 << I2S_WS);

unsigned int I2S_SD_LOW = ~(1 << I2S_SD);
unsigned int I2S_SD_HIGH = (1 << I2S_SD);

const unsigned int delay_time = 63;

unsigned int WS = 0;
unsigned int ws_val = 0;

int16_t data = INT16_MAX;
unsigned int data_bit;

void setup() {
    DDRB |= 1 << I2S_SCK;  // CLK
    DDRB |= 1 << I2S_WS;  // WS
    DDRB |= 1 << I2S_SD;  // Data

    Serial.begin(DEFAULT_BAUD_RATE);
}

void loop() {
    // Word select out:
    if (!WS) {
        if (ws_val == 0) {
            PORTB &= I2S_WS_LOW;
            ws_val = 1;
        } else {
            PORTB |= I2S_WS_HIGH;
            ws_val = 0;
        }
    }

    // Clock out:
    PORTB &= I2S_SCK_LOW;
    _delay_us(delay_time);

    PORTB |= I2S_SCK_HIGH;
    _delay_us(delay_time);

    // data out:
    data_bit = (data >> (DAC_BITS - WS -1 )) & 0x1;

    Serial.print("Data = "); Serial.print(data);
    Serial.print(", Data Bit = "); Serial.print(data_bit);
    Serial.print(", Bit Counter = "); Serial.print(WS);
    Serial.print(", Word Select = "); Serial.print((ws_val+1)%2);
    Serial.print("\n");

    if (data_bit == 0) {
        PORTB &= I2S_SD_LOW;
    } else {
        PORTB |= I2S_SD_HIGH;
    }

    WS++;
    WS %= DAC_BITS;
}