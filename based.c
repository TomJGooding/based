#include <stddef.h>
#include <stdio.h>

const char base64_table[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "+/";

int main() {
    char *input = "ABC";
    size_t input_len = 3;

    printf("'%s' in binary:\n", input);
    for (size_t i = 0; i < input_len; i++) {
        printf("%08b ", input[i]);
    }
    printf("\n\n");
    // 01000001 01000010 01000011

    printf("6-bit transformation:\n");
    printf("%06b ", input[0] >> 2);
    printf("%06b ", ((input[0] & 0x03) << 4) + (input[1] >> 4));
    printf("%06b ", ((input[1] & 0x0f) << 2) + (input[2] >> 6));
    printf("%06b ", input[2] & 0x3f);
    printf("\n\n");
    // 010000 010100 001001 000011

    printf("Base64 encoded: \n");
    printf("%c", base64_table[input[0] >> 2]);
    printf("%c", base64_table[((input[0] & 0x03) << 4) + (input[1] >> 4)]);
    printf("%c", base64_table[((input[1] & 0x0f) << 2) + (input[2] >> 6)]);
    printf("%c", base64_table[input[2] & 0x3f]);
    printf("\n");
    // QUJD
    //
    // Same output as `echo -n "ABC" | base64`!
}
