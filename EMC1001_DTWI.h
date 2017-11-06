#ifndef _EMC1001_DTWI_H
#define _EMC1001_DTWI_H

#include <Arduino.h>
#include <DTWI.h>

#define EMC1001_ADDRESS 0x38
#define EMC1001_TEMP_HIGH       0x00
#define EMC1001_STATUS          0x01
#define EMC1001_TEMP_LOW        0x02
#define EMC1001_CONFIG          0x03
#define EMC1001_RATE            0x04
#define EMC1001_HIGH_LIMIT_HIGH 0x05
#define EMC1001_HIGH_LIMIT_LOW  0x06
#define EMC1001_LOW_LIMIT_HIGH  0x07
#define EMC1001_LOW_LIMIT_LOW   0x08
#define EMC1001_ONE_SHOT        0x0F
#define EMC1001_THERM_LIMIT     0x20
#define EMC1001_THERM_HYST      0x21
#define EMC1001_TIMEOUT         0x22
#define EMC1001_PID             0xFD
#define EMC1001_MID             0xFE
#define EMC1001_REV             0xFF

#define EMC1001_STATUS_THERM    0b00000001
#define EMC1001_STATUS_TLOW     0b00100000
#define EMC1001_STATUS_THIGH    0b01000000
#define EMC1001_STATUS_BUSY     0b10000000

class EMC1001 {
    private:
        DTWI *_dtwi;
        uint8_t _address;

        uint8_t readRegister(uint8_t reg);
        void writeRegister(uint8_t reg, uint8_t val);


    public:

        EMC1001(DTWI *d) : _dtwi(d), _address(EMC1001_ADDRESS) {}
        EMC1001(DTWI &d) : _dtwi(&d), _address(EMC1001_ADDRESS) {}
        EMC1001(DTWI *d, uint8_t a) : _dtwi(d), _address(a) {}
        EMC1001(DTWI &d, uint8_t a) : _dtwi(&d), _address(a) {}
        
        void begin();
        float getTemperature();
};

#endif
