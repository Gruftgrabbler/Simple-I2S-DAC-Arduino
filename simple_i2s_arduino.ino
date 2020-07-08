#include <Arduino.h>
#include <avr/io.h>

#define F_CPU 16000000

#include <util/delay.h>
#include <avr/interrupt.h>

#define NOP() {__asm__ __volatile__ ("nop");}

#define I2S_SCK  PB3    // Pin 11 on Arduino Uno, Pin 1 on TM8211
#define I2S_WS   PB5    // Pin 13 on Arduino Uno, Pin 2 on TM8211
#define I2S_SD   PB4    // Pin 12 on Arduino Uno, Pin 3 on TM8211
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

const unsigned int delay_time = 15;

unsigned int bit_counter = 0;
unsigned int ws_val = 0;

//int16_t data = INT16_MAX;
uint16_t data;
unsigned int data_bit;

/**
 * In diesem Projekt funktionieren beide Ansätze der DAC Ansteuerung. Ferdinands Ansatz über die Methode ShiftOut
 * funktioniert wie im Bilderbuch und mein Ansatz auch. Allerdings sind beide Programme von der delay Funktion abhängig,
 * was mit dem PDK nicht wirklich zuverlässig umsetzbar ist. So, dass eine Interruptbasierte Lösung wohl die beste ist
 *
 */
void setup() {
    // Setup Pins as OUTPUT via Port Modulation
    DDRB |= (1 << I2S_SCK);  // CLK
    DDRB |= (1 << I2S_WS);  // WS
    DDRB |= (1 << I2S_SD);  // Data

    data = INT16_MIN;

    PORTB &= I2S_WS_LOW;
    PORTB &= I2S_SD_LOW;
    PORTB &= I2S_SCK_LOW;

    Serial.begin(DEFAULT_BAUD_RATE);
}

void printDebugData() {
    Serial.print("Data = ");
    Serial.print(data);
    Serial.print(", Data Bit = ");
    Serial.print(data_bit);
    Serial.print(", Bit Counter = ");
    Serial.print(bit_counter);
    Serial.print(", Word Select = ");
    Serial.print((ws_val + 1) % 2);
    Serial.print("\n");
}

void loop() {
    // Word select out:
    if (!bit_counter) {
        if (ws_val == 0) {
            PORTB &= I2S_WS_LOW;
            ws_val = 1;
        } else {
            PORTB |= I2S_WS_HIGH;
            ws_val = 0;
        }
    }

    // Data out:
    data_bit = (data >> (DAC_BITS - bit_counter - 1)) & 0x1;

    if (data_bit == 0) {
        PORTB &= I2S_SD_LOW;
    } else
        PORTB |= I2S_SD_HIGH;

    // Clock out:
    PORTB |= I2S_SCK_HIGH;
    _delay_us(delay_time);

    PORTB &= I2S_SCK_LOW;
    _delay_us(delay_time);

    //printDebugData();

    bit_counter++;
    bit_counter %= DAC_BITS;
}

/**
 * Shifts out 2 byte of data one bit at a time. Starts from the most (i.e. the leftmost)
 * significant bit. Each bit is written in turn to the data pin, after which
 * a clock pin is pulsed (taken high, then low) to indicate that the bit is available.
 * @param data_pin: the pin on which to output each bit. Allowed data types: int.
 * @param clock_pin: the pin to toggle once the dataPin has been set to the correct value.
 * Allowed data types: int.
 * @param data_: the data to shift out. Allowed data types: uint16_t or int16_t.
 *
 * TODO Verify this function description to be valid
 * TODO Implement the function parameters in a way so its using them.
 * TODO Refactor the function to work on a PDK173
 */
void shiftOutData(uint16_t data_pin, uint16_t clock_pin, uint16_t data_) {
    for (byte i = 0; i < DAC_BITS; i++) {
        data_bit = data_ & (1 << DAC_BITS - 1 - i);
        if (data_bit)
            PORTB |= (1 << data_pin);   // digitalWrite(data_pin, HIGH);
        else
            PORTB &= ~(1 << data_pin);  // digitalWrite(data_pin, LOW);


        PORTB |= (1 << clock_pin);          // digitalWrite(clock_pin, HIGH);
        delayMicroseconds(15);
        PORTB &= ~(1 << clock_pin);         // digitalWrite(clock_pin, LOW);
        delayMicroseconds(15);
    }
}

void loop_ferdinand() {
    shiftOutData(I2S_SD, I2S_SCK, data);
    PORTB |= I2S_WS_HIGH;
    shiftOutData(I2S_SD, I2S_SCK, data);
    //delayMicroseconds(500);
    PORTB &= I2S_WS_LOW;
}
