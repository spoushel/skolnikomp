#include <math.h>
#include <stdint.h>
#include <stdio.h>

// provided functions
static float float_from_parts(uint8_t sign_bit, uint32_t mantissa_bits, uint32_t exponent_bits) {
    uint32_t mantissa = (1u << 23) | mantissa_bits;
    int32_t signed_mantissa = sign_bit ? -((int32_t)mantissa) : (int32_t)mantissa;
    int exponent = (int)exponent_bits - 127;
    return ldexpf((float)signed_mantissa, exponent - 23);
}

static double double_from_parts(uint8_t sign_bit, uint64_t mantissa_bits, uint64_t exponent_bits) {
    uint64_t mantissa = (1ull << 52) | mantissa_bits;
    int64_t signed_mantissa = sign_bit ? -((int64_t)mantissa) : (int64_t)mantissa;
    int exponent = (int)exponent_bits - 1023;
    return ldexp((double)signed_mantissa, exponent - 52);
}

int main(void) {
    int descriptor;

    while ((descriptor = getchar()) != EOF) {
        int is_float = (descriptor >> 7) & 1; // 1 float, 0 int

        if (!is_float) { // je to int
            int is_signed = (descriptor >> 6) & 1;
            int is_bigend = (descriptor >> 5) & 1;
            // extract value
            int bit4 = (descriptor >> 4) & 1;
            int bit2 = (descriptor >> 2) & 1;
            int bit0 = (descriptor >> 0) & 1;
            int size_bytes = (bit0) | (bit2 << 1) | (bit4 << 2); // zkombinuje bits dohromady
            if (size_bytes > 4) {
                fprintf(stderr, "Chyba formátu!\n");
                return 1;
            }

            if (!size_bytes) {
                continue;
            }
            int actual_size = 1 << (size_bytes - 1); // prevod z 0, 1, 2, 3 na mocniny 2

            uint64_t value = 0;

            for (int i = 0; i < actual_size; i++) {
                int byte = getchar();
                if (byte == EOF) {
                    fprintf(stderr, "Chyba formátu!\n");
                    return 1;
                }

                if (is_bigend) {
                    value = (value << 8) | byte; // posouva pred kazdou iteraci o jeden do strany
                } else {
                    value = value | ((uint64_t)byte << (i * 8)); // dava bits na spravnou pozici
                }
            }

            if (is_signed) {

                switch (actual_size) {
                case 1:
                    printf("%d\n", (int)(int8_t)value);
                    break;
                case 2:
                    printf("%d\n", (int)(int16_t)value);
                    break;
                case 4:
                    printf("%d\n", (int)(int32_t)value);
                    break;
                case 8:
                    printf("%lld\n", (long long)(int64_t)value);
                    break;
                default:
                    break;
                }
            } else { // is unsigned
                switch (actual_size) {
                case 1:
                    printf("%u\n", (unsigned)(uint8_t)value);
                    break;
                case 2:
                    printf("%u\n", (unsigned)(uint16_t)value);
                    break;
                case 4:
                    printf("%u\n", (unsigned)(uint32_t)value);
                    break;
                case 8:
                    printf("%llu\n", (unsigned long long)(uint64_t)value);
                    break;
                default:
                    break;
                }
            }
        } else { // je to float type,vzdycky bigendian
            int is_double = (descriptor >> 6) & 1; // 1 if double
            int actual_size = is_double ? 8 : 4;

            uint64_t raw_value = 0;
            for (int i = 0; i < actual_size; i++) {
                int byte = getchar();
                if (byte == EOF) {
                    fprintf(stderr, "Chyba formátu!\n");
                    return 1;
                }
                raw_value = (raw_value << 8) | byte; // big endian
            }

            if (!is_double) { // je to true float, 4 bytes
                uint32_t bits = (uint32_t)raw_value;
                uint8_t sign_bit = (bits >> 31) & 1;
                uint32_t exponent_bits = (bits >> 23) & 0xFF;
                uint32_t mantissa_bits = bits & 0x7FFFFF;
                if (exponent_bits == 0 && mantissa_bits == 0) {
                    printf("%.8g\n", 0.0);
                } else {
                    float result = float_from_parts(sign_bit, mantissa_bits, exponent_bits);
                    printf("%.8g\n", result);
                }
            } else { // je to double, 8 bytes
                uint8_t sign_bit = (raw_value >> 63) & 1;
                uint64_t exponent_bits = (raw_value >> 52) & 0x7FF;
                uint64_t mantissa_bits = raw_value & 0xFFFFFFFFFFFFFull;
                if (exponent_bits == 0 && mantissa_bits == 0) {
                    printf("%.17g\n", 0.0);
                } else {
                    double result = double_from_parts(sign_bit, mantissa_bits, exponent_bits);
                    printf("%.17g\n", result);
                }
            }
        }
    }
    return 0;
}
