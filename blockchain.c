#include "blockchain.h"
#include "sha256.h"  
#include "utils.h"
#include <string.h>

//lets start this engine up...RRRRRRRR
void init_blockchain(Blockchain *bc) {
    bc->head = NULL;
    bc->tail = NULL;
    bc->length = 0;
}

//first genesis block implementation.
Block* create_genesis_block() {
    Block *genesis = (Block*)malloc(sizeof(Block));
    if (!genesis) return NULL;
    
    genesis->index = 0;
    get_current_timestamp(genesis->timestamp, sizeof(genesis->timestamp));
    strcpy(genesis->task.description, "Genesis Block");
    genesis->task.completed = 1;
    strcpy(genesis->task.created, genesis->timestamp);
    strcpy(genesis->task.completed_date, genesis->timestamp);
    strcpy(genesis->previous_hash, "0");
    
    calculate_block_hash(genesis);
    genesis->next = NULL;
    
    return genesis;
}

//Progressive block hashing function
void calculate_block_hash(Block *block) {
    char data[1024];
    snprintf(data, sizeof(data), "%d%s%s%d%s%s",
             block->index,
             block->timestamp,
             block->task.description,
             block->task.completed,
             block->task.created,
             block->previous_hash);
    
    uint8_t hash[SHA256_BLOCK_SIZE];
    sha256((uint8_t*)data, strlen(data), hash);
    hash_to_hex(hash, block->hash);
}

Block* create_block(Task task, char previous_hash[]) {
    Block *new_block = (Block*)malloc(sizeof(Block));
    if (!new_block) return NULL;
    
    static int block_index = 1;
    new_block->index = block_index++;
    get_current_timestamp(new_block->timestamp, sizeof(new_block->timestamp));
    new_block->task = task;
    strcpy(new_block->previous_hash, previous_hash);
    
    calculate_block_hash(new_block);
    new_block->next = NULL;
    
    return new_block;
}

//Once created add that block to the chain
void add_block(Blockchain *bc, Block *block) {
    if (!bc->head) {
        bc->head = block;
        bc->tail = block;
    } else {
        bc->tail->next = block;
        bc->tail = block;
    }
    bc->length++;
}

int validate_blockchain(Blockchain *bc) {
    if (!bc->head) return 1;
    
    Block *current = bc->head;
    Block *prev = NULL;
    
    while (current) {
        // Verify block hash
        char calculated_hash[HASH_HEX_LEN];
        char data[1024];
        
        if (prev) {
            snprintf(data, sizeof(data), "%d%s%s%d%s%s",
                     current->index,
                     current->timestamp,
                     current->task.description,
                     current->task.completed,
                     current->task.created,
                     current->previous_hash);
        } else { // Genesis block
            snprintf(data, sizeof(data), "%d%s%s%d%s%s",
                     current->index,
                     current->timestamp,
                     current->task.description,
                     current->task.completed,
                     current->task.created,
                     "0");
        }
        
        uint8_t hash[SHA256_BLOCK_SIZE];
        sha256((uint8_t*)data, strlen(data), hash);
        hash_to_hex(hash, calculated_hash);
        
        if (strcmp(current->hash, calculated_hash) != 0) {
            return 0; 
        }
        
        //Verify previous hash completely
        if (prev && strcmp(current->previous_hash, prev->hash) != 0) {
            return 0; 
        }
        
        prev = current;
        current = current->next;
    }
    
    return 1;
}

void free_blockchain(Blockchain *bc) {
    Block *current = bc->head;
    while (current) {
        Block *next = current->next;
        free(current);
        current = next;
    }
    bc->head = NULL;
    bc->tail = NULL;
    bc->length = 0;
}