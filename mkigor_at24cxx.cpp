#include <at24cxx.h>

uint8_t AT24Cxx_addr = 0x57;

bool AT24Cxx::begin(uint8_t _i2c_addr) {
    AT24Cxx_addr = _i2c_addr;
    Wire.begin();
    Wire.beginTransmission(_i2c_addr);
    if (Wire.endTransmission() == 0)  return true;
    else                              return false;
}

uint8_t AT24Cxx::read(uint16_t _lv_mem_addr) { // Read byte  
    uint8_t _tv_msb = _lv_mem_addr >> 8;
    uint8_t _tv_lsb = _lv_mem_addr & 0xFF;
    Wire.beginTransmission(AT24Cxx_addr);
    if (Wire.endTransmission() == 0) {
        Wire.beginTransmission(AT24Cxx_addr);
        Wire.write(_tv_msb);
        Wire.write(_tv_lsb);
        if (Wire.endTransmission() == 0) {
            Wire.requestFrom(AT24Cxx_addr, 1);
            if (Wire.available() > 0) {
                return Wire.read();
            }
        }
    }
    return 0xFF;
}

bool AT24Cxx::write(uint16_t _lv_mem_addr, uint8_t data) {   // Write byte
    uint8_t _tv_msb = _lv_mem_addr >> 8;
    uint8_t _tv_lsb = _lv_mem_addr & 0xFF;
    Wire.beginTransmission(AT24Cxx_addr);
    if (Wire.endTransmission() == 0) {
        Wire.beginTransmission(AT24Cxx_addr);
        Wire.write(_tv_msb);
        Wire.write(_tv_lsb);
        Wire.write(data);
        Wire.endTransmission();
        return true;
    }
    else return false;
}

bool AT24Cxx::read_arr(uint16_t _lv_mem_addr, uint16_t _lv_size_dim, char* _lv_dim) { // Read array  
  uint8_t _tv_msb = (uint8_t)_lv_mem_addr >> 8;
  uint8_t _tv_lsb = (uint8_t)_lv_mem_addr & 0x00FF;
  Wire.beginTransmission(AT24Cxx_addr);
  if (Wire.endTransmission() == 0) {
    Wire.beginTransmission(AT24Cxx_addr);
    Wire.write(_tv_msb);
    Wire.write(_tv_lsb);
    if (Wire.endTransmission() == 0) {
      Wire.requestFrom(AT24Cxx_addr, _lv_size_dim);
      if (Wire.available() == _lv_size_dim) {
        for (uint16_t i = 0; i < _lv_size_dim; i++) _lv_dim[i] = Wire.read();
        return true;
      }
    }
  }
  return false;
}

bool AT24Cxx::write_arr(uint16_t _lv_mem_addr, uint16_t _lv_size_dim, char* _lv_dim) {   // Write baray
  // write to at24cxx can only by pages 32 bytes. Memory address must be aligned to 32 and set to the begin every page,
  // otherwise it will be rotated inside page = collapse!!! Next code do it by restrict.
  if (_lv_size_dim>32 )  _lv_size_dim = 32;
   _lv_mem_addr = _lv_mem_addr & 0xFFE0;
  
  uint8_t _tv_msb = _lv_mem_addr >> 8;
  uint8_t _tv_lsb = _lv_mem_addr & 0xFF;
  Wire.beginTransmission(AT24Cxx_addr);
  if (Wire.endTransmission() == 0) {
    Wire.beginTransmission(AT24Cxx_addr);
    Wire.write(_tv_msb);
    Wire.write(_tv_lsb);
    for (uint16_t i = 0; i < _lv_size_dim; i++) {
      Wire.write(_lv_dim[i]);
    }
    Wire.endTransmission();
    return true;
  }
  return false;
}

AT24Cxx::AT24Cxx() {};
