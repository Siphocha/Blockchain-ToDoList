#include "utils.h"
#include "sha256.h"
#include <ctype.h>  

void get_current_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

void hash_to_hex(const uint8_t *hash, char *hex) {
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        sprintf(hex + (i * 2), "%02x", hash[i]);
    }
    hex[64] = '\0';
}

int hex_to_hash(const char *hex, uint8_t *hash) {
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        if (sscanf(hex + 2*i, "%2hhx", &hash[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

int validate_input(const char *input, int max_len) {
    if (!input || strlen(input) == 0 || strlen(input) > max_len) {
        return 0;
    }
    
    for (int i = 0; input[i]; i++) {
        if (!isprint((unsigned char)input[i]) || 
            input[i] == ';' || input[i] == '\'' || input[i] == '\"') {
            return 0;
        }
    }
    return 1;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}