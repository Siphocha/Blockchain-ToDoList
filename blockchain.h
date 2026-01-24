#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "utils.h"  

typedef struct {
    char description[MAX_TASK];
    int completed;
    char created[20];
    char completed_date[20];
} Task;

typedef struct Block {
    int index;
    char timestamp[20];
    Task task;
    char previous_hash[HASH_HEX_LEN];
    char hash[HASH_HEX_LEN];
    struct Block *next;
} Block;

typedef struct {
    Block *head;
    Block *tail;
    int length;
} Blockchain;

// Blockchain functions
void init_blockchain(Blockchain *bc);
Block* create_genesis_block();
Block* create_block(Task task, char previous_hash[]);
void add_block(Blockchain *bc, Block *block);
int validate_blockchain(Blockchain *bc);
void calculate_block_hash(Block *block);
void free_blockchain(Blockchain *bc);

#endif