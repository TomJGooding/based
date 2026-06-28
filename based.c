#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char base64_table[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "+/";

char *base64_encode(const char *input, size_t len) {
    size_t out_len = 4 * ((len + 2) / 3);
    char *out = malloc(out_len + 1);
    size_t out_i = 0;

    char prev = 0;
    for (size_t i = 0; i < len; i++) {
        char curr = input[i];
        switch (out_i % 4) {
        case 0:
            out[out_i++] = base64_table[curr >> 2];
            break;
        case 1:
            out[out_i++] = base64_table[((prev & 0x03) << 4) + (curr >> 4)];
            break;
        case 2:
            out[out_i++] = base64_table[((prev & 0x0f) << 2) + (curr >> 6)];
            out[out_i++] = base64_table[curr & 0x3f];
            break;
        }
        prev = curr;
    }

    switch (out_i % 4) {
    case 1:
        out[out_i++] = base64_table[((prev & 0x03) << 4)];
        out[out_i++] = '=';
        out[out_i++] = '=';
        break;
    case 2:
        out[out_i++] = base64_table[((prev & 0x0f) << 2)];
        out[out_i++] = '=';
        break;
    }

    out[out_i] = 0;

    return out;
}

int main() {
    char *input = "Hi";
    printf("Input:\n%s\n", input);

    char *encoded = base64_encode(input, strlen(input));
    printf("Encoded:\n%s\n", encoded);
}
