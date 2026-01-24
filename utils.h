#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>  

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_TASK 200
#define HASH_HEX_LEN 65
#define MAX_USERS 100  
#define SALT "blockchain_todo_salt"

void get_current_timestamp(char *buffer, size_t size);
void hash_to_hex(const uint8_t *hash, char *hex);
int hex_to_hash(const char *hex, uint8_t *hash);
int validate_input(const char *input, int max_len);
void clear_input_buffer();

#endif