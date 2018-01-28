#include <EMC1001_DTWI.h>

uint8_t EMC1001::readRegister(uint8_t reg) {
    uint8_t state = 0;
    uint8_t val = 0;
    uint32_t ts = millis();
    while (1) {
        if (millis() - ts > 100) {
            _dtwi->stopMaster();
            return 0;
        }
        switch (state) {
            case 0: // begin write 
                if (_dtwi->startMasterWrite(_address)) {
                    state = 1;
                }
                break;
            case 1: // Send register address
                if (_dtwi->write(&reg, 1) == 1) {
                    state = 2;
                }
                break;
            case 2: // Stop Master
                if (_dtwi->stopMaster()) {
                    state = 3;
                }
                break;
            case 3:
                if (_dtwi->startMasterRead(_address, 1)) {
                    state = 4;
                }
                break;
            case 4:
                if (_dtwi->available()) {
                    _dtwi->read(&val, 1);
                    state = 5;
                }
                break;
            case 5:
                if (_dtwi->stopMaster()) {
                    return val;
                }
                break;
        }
    }
}

void EMC1001::writeRegister(uint8_t reg, uint8_t val) {
    uint8_t state = 0;
    uint32_t ts = millis();
    while (1) {
        if (millis() - ts > 100) {
            _dtwi->stopMaster();
        }
        switch (state) {
            case 0: // begin write 
                if (_dtwi->startMasterWrite(_address)) {
                    state = 1;
                }
                break;
            case 1: // Send register address
                if (_dtwi->write(&reg, 1) == 1) {
                    state = 2;
                }
                break;
            case 2: // Send register address
                if (_dtwi->write(&val, 1) == 1) {
                    state = 3;
                }
                break;
            case 3: // Stop Master
                if (_dtwi->stopMaster()) {
                    return;
                }
                break;
        }
    }
}

void EMC1001::begin() {
    _dtwi->beginMaster();
    writeRegister(EMC1001_CONFIG, 0b000010); // Standby mode
}

void EMC1001::end() {
    _dtwi->endMaster();
}

float EMC1001::getTemperature() {
    writeRegister(EMC1001_ONE_SHOT, 1);
    uint8_t status = readRegister(EMC1001_STATUS);
    while (status & EMC1001_STATUS_BUSY) {
        status = readRegister(EMC1001_STATUS);
    }
    uint8_t h = readRegister(EMC1001_TEMP_HIGH);
    uint8_t l = readRegister(EMC1001_TEMP_LOW);
    uint16_t v = (h << 8) | l;
    v >>= 6;
    v |= (v & 0b0000001000000000) ? 0b1111110000000000 : 0;
    return (float)v * 0.25;
}
