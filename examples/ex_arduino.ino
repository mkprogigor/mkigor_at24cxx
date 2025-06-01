#include <Arduino.h>
#include <Wire.h>
#include <at24cxx.h>

#define i2c_addr_at24 0x57

AT24Cxx at24;

// =============================================================================
char gf_byte2char(uint8_t lv_byte1) {   // translate 0xBA => 'A'
  uint8_t lv_b1 = lv_byte1 & 0x0F;
  if (lv_b1>9) lv_b1 = lv_b1+55;
  else         lv_b1 = lv_b1+48;
  return lv_b1;
}
void gf_prn_byte(uint8_t lv_byte) {   // print byte like "FCh "
  Serial.print(gf_byte2char(lv_byte>>4));
  Serial.print(gf_byte2char(lv_byte));
  Serial.print("h ");
}

// =============================================================================
// setup
// =============================================================================
void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.print("\n\nAT24Cxx check => ");
  Serial.print(" address:"); Serial.print(i2c_addr_at24, HEX);
  if (at24.begin(i2c_addr_at24))    Serial.println(" FOUND!");
  else                              Serial.println(" not found.");
}

// =============================================================================
// main loop
// =============================================================================
void loop() {
  uint16_t lv_sd = 256;   //  Size of array in bytes
  uint16_t i;
  uint8_t k;
  bool res;
  char lv_dim[lv_sd + 1];   // array must be +1 byte = 0, end of array of char
  uint32_t lv_timest;       // time stamp

  Serial.println("=========================================================================================");
  Serial.println("Write/Read from AT24C by byte.");
  Serial.println("Generate array =>");
  for (i = 0; i < lv_sd; i++) lv_dim[i] = (uint8_t)random(256);   //  Fill array with randomise numbers
  
  for (uint16_t i = 0; i < lv_sd; i++) {
    Serial.print(gf_byte2char((uint8_t)(i >> 12)));
    Serial.print(gf_byte2char((uint8_t)(i >> 8)));
    Serial.print(gf_byte2char((uint8_t)(i >> 4)));
    Serial.print(gf_byte2char((uint8_t)(i)));
    Serial.print(": ");
    for (k = 0; k < 32; k++) {
      gf_prn_byte(lv_dim[i]);
      i++;
    }
    i--;
    Serial.println();
  }

  Serial.print("Write to AT24C by byte => , It is takes time = ");
  lv_timest = millis();
  for (i = 0; i < lv_sd; i++) {   // Write array to AT24Cxx memoty by byte
    at24.write(i, lv_dim[i]);
    delay(10);                    // need to wait to chip finish write command !!!
  }
  Serial.print(millis() - lv_timest);
  Serial.println(" ms.");

  for (i = 0; i < lv_sd; i++) lv_dim[i]=0;

  Serial.print("Read from AT24C by byte => , It is takes time = ");
  lv_timest = millis();
  for (i = 0; i < lv_sd; i++) lv_dim[i] = at24.read(i);        // Write array to AT24Cxx memoty by byte
  Serial.print(millis() - lv_timest);
  Serial.println(" ms.");

  for (i = 0; i < lv_sd; i++) {
    Serial.print(gf_byte2char((uint8_t)(i >> 12)));
    Serial.print(gf_byte2char((uint8_t)(i >> 8)));
    Serial.print(gf_byte2char((uint8_t)(i >> 4)));
    Serial.print(gf_byte2char((uint8_t)(i)));
    Serial.print(": ");
    for (k = 0; k < 32; k++) {
      gf_prn_byte(lv_dim[i]);
      i++;
    }
    i--;
    Serial.println();
  }
  Serial.println("=========================================================================================\n");

  delay(3000);

  Serial.println("=========================================================================================");
  Serial.println("Write/Read from AT24C by array.");
  Serial.println("Generate array =>");
  for (i = 0; i < lv_sd; i++) lv_dim[i] = (uint8_t)random(256);   //  Fill array with randomise numbers
  for (i = 0; i < lv_sd; i++) {
    Serial.print(gf_byte2char((uint8_t)(i >> 12)));
    Serial.print(gf_byte2char((uint8_t)(i >> 8)));
    Serial.print(gf_byte2char((uint8_t)(i >> 4)));
    Serial.print(gf_byte2char((uint8_t)(i)));
    Serial.print(": ");
    for (k = 0; k < 32; k++) {
      gf_prn_byte(lv_dim[i]);
      i++;
    }
    i--;
    Serial.println();
  }

  Serial.print("Write to AT24C by array => , It is takes time = ");
  lv_timest = millis();
  res = at24.write_arr(0, lv_sd, lv_dim);        // Write array to AT24Cxx memoty at once
  Serial.print(millis() - lv_timest);
  Serial.println(" ms.");
  // Serial.println(res);
  delay(10);    // need to wait to chip finish write command !!!

  for (i = 0; i < lv_sd; i++) lv_dim[i]=0;

  Serial.print("Read from AT24C by array => , It is takes time = ");
  lv_timest = millis();
  res = at24.read_arr(0, lv_sd, lv_dim);
  Serial.print(millis() - lv_timest);
  Serial.println(" ms.");
  // Serial.println(res);

  for (uint16_t i = 0; i < lv_sd; i++) {
    Serial.print(gf_byte2char((uint8_t)(i >> 12)));
    Serial.print(gf_byte2char((uint8_t)(i >> 8)));
    Serial.print(gf_byte2char((uint8_t)(i >> 4)));
    Serial.print(gf_byte2char((uint8_t)(i)));
    Serial.print(": ");
    for (k = 0; k < 32; k++) {
      gf_prn_byte(lv_dim[i]);
      i++;
    }
    i--;
    Serial.println();
  }
  Serial.println("=========================================================================================");

  delay(900000);
}