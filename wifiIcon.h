#if defined(__AVR__)
    #include <avr/pgmspace.h>
#elif defined(__PIC32MX__)
    #define PROGMEM
#elif defined(__arm__)
    #define PROGMEM
#endif

static const uint16_t wifiicon[315] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2145, 0x42ef, 0x3bd4, 0x3c57, 0x44b9, 0x44b9, 0x44b9, 0x3c57, 0x43f4, 0x3b0f, 0x2966, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x31e9, 0x43f4, 0x34da, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x34da, 0x3bf4, 0x3209, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x10c3, 0x43b3, 0x24da, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x2cda, 0x43d3, 0x10c3, 0x0000, 
    0x2167, 0x4457, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x1cfb, 0x3c99, 0x4477, 0x3bf5, 0x3c57, 0x3cb9, 0x1cdb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x4477, 0x2987, 
    0x4c77, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x3498, 0x3b51, 0x3a09, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31c8, 0x4351, 0x3c98, 0x0cfb, 0x04fb, 0x04fb, 0x04fb, 0x4c77, 
    0x3a6b, 0x34da, 0x04fb, 0x24da, 0x4351, 0x1081, 0x0000, 0x1040, 0x2187, 0x42cd, 0x42ee, 0x42ad, 0x29a8, 0x1060, 0x0000, 0x18a2, 0x4371, 0x2cda, 0x04fb, 0x34da, 0x3a6b, 
    0x0000, 0x3a6b, 0x4498, 0x324b, 0x0000, 0x18c3, 0x4350, 0x3c98, 0x2cfb, 0x04fb, 0x04fb, 0x04fb, 0x2cfb, 0x3c78, 0x4351, 0x18e3, 0x0000, 0x326b, 0x4498, 0x3a8c, 0x0000, 
    0x0000, 0x0000, 0x1082, 0x0000, 0x320a, 0x3c78, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x3c78, 0x320a, 0x0000, 0x18a2, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x18e3, 0x44b8, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fc, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x04fb, 0x4498, 0x18e3, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x3a8c, 0x34da, 0x04fb, 0x2cda, 0x43f5, 0x430f, 0x3a8c, 0x42ef, 0x4415, 0x2cda, 0x04fb, 0x34da, 0x3a8c, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3aad, 0x4456, 0x3209, 0x0000, 0x0000, 0x3165, 0x0000, 0x0000, 0x31e9, 0x4457, 0x3aad, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0861, 0x0000, 0x18e4, 0x3c57, 0x1cdb, 0x4457, 0x2125, 0x0000, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3b10, 0x04fb, 0x04fb, 0x04fb, 0x3b0f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3b0f, 0x04fb, 0x04fb, 0x04fb, 0x3aef, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10a2, 0x43d4, 0x44b9, 0x43d4, 0x10a2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};