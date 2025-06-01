/************************************************************************************
Library for test and use in weather stations with Bosch i2c sensor bme280
by Igor Mkprog

use examples:
https://github.com/AlexGyver/GyverLibs/blob/master/GyverBME280/
https://github.com/farmerkeith/BMP280-library/
https://github.com/farmerkeith/I2CScanner/

V0.1 from 08.05.2025
************************************************************************************/
#ifndef at24cxx_h
#define at24cxx_h

#include "Arduino.h"
#include "Wire.h"

/*************************************************/
class AT24Cxx {
public:
    AT24Cxx();      // create an object of class 
    bool begin(uint8_t _i2x_addr);
    uint8_t read(uint16_t _lv_mem_addr);
    bool write(uint16_t _lv_mem_addr, uint8_t data);
    bool read_arr(uint16_t _lv_mem_addr, uint16_t _lv_size_dim, char* _lv_dim);
    bool write_arr(uint16_t _lv_mem_addr, uint16_t _lv_size_dim, char* _lv_dim);
};

#endif
