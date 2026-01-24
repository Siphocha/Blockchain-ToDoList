#include "storage.h"
#include <stdio.h>

int save_blockchain(Blockchain *bc) {
    FILE *file = fopen(BLOCKCHAIN_FILE, "wb");
    if (!file) return 0;
    
    Block *current = bc->head;
    while (current) {
        fwrite(current, sizeof(Block), 1, file);
        current = current->next;
    }
    
    fclose(file);
    return 1;
}

int load_blockchain(Blockchain *bc) {
    FILE *file = fopen(BLOCKCHAIN_FILE, "rb");
    if (!file) return 0;
    
    init_blockchain(bc);
    
    Block *prev = NULL;
    Block block;
    
    while (fread(&block, sizeof(Block), 1, file) == 1) {
        Block *new_block = (Block*)malloc(sizeof(Block));
        if (!new_block) {
            fclose(file);
            return 0;
        }
        
        *new_block = block;
        new_block->next = NULL;
        
        if (!prev) {
            bc->head = new_block;
        } else {
            prev->next = new_block;
        }
        
        prev = new_block;
        bc->tail = new_block;
        bc->length++;
    }
    
    fclose(file);
    
    // Validate loaded blockchain
    if (bc->head && !validate_blockchain(bc)) {
        printf("Warning: Loaded blockchain may be corrupted!\n");
    }
    
    return 1;
}

int save_users(AuthSystem *auth) {
    FILE *file = fopen(USERS_FILE, "wb");
    if (!file) return 0;
    
    fwrite(&auth->count, sizeof(int), 1, file);
    fwrite(auth->users, sizeof(User), auth->count, file);
    
    fclose(file);
    return 1;
}

int load_users(AuthSystem *auth) {
    FILE *file = fopen(USERS_FILE, "rb");
    if (!file) return 0;
    
    init_auth(auth);
    
    if (fread(&auth->count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    if (auth->count > MAX_USERS) {
        fclose(file);
        auth->count = 0;
        return 0;
    }
    
    size_t read_count = fread(auth->users, sizeof(User), auth->count, file);
    fclose(file);
    
    return read_count == auth->count;
}