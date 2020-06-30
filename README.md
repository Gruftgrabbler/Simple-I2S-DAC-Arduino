# Simple-I2S-DAC-Arduino

This simple I2S DAC Programm is a derivation of UlrikHjort's I2S-Simple Repository which you
can find [here](https://github.com/UlrikHjort/I2S-Simple).
 
Its modified to run on Arduino UNO
and compiled via the "Arduino Support Extension" for CLion.

For testing purposes the script only write the signed 16 Bit int maximal value (0x7FFF) to the dac,
which should output a constant voltage close to VCC.

Further it prints some information's about the inner state of the machine:
the current data bit which will be wrote to the I2S_SD_PIN, the Bit Counter and the Word Select.

The output of the Serial prints is:
```
Data = 32767, Data Bit = 0, Bit Counter = 0, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 1, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 2, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 3, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 4, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 5, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 6, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 7, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 8, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 9, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 10, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 11, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 12, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 13, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 14, Word Select = 0
Data = 32767, Data Bit = 1, Bit Counter = 15, Word Select = 0
Data = 32767, Data Bit = 0, Bit Counter = 0, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 1, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 2, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 3, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 4, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 5, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 6, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 7, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 8, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 9, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 10, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 11, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 12, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 13, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 14, Word Select = 1
Data = 32767, Data Bit = 1, Bit Counter = 15, Word Select = 1
```
