#include "auth.h"
#include "sha256.h"
#include "utils.h"
#include <string.h>

void init_auth(AuthSystem *auth) {
    auth->count = 0;
    auth->current_user = NULL;
    memset(auth->users, 0, sizeof(auth->users));
}

void hash_password(const char *password, char *hash_output) {
    char salted_password[MAX_PASSWORD + 50];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, SALT);
    
    uint8_t hash[SHA256_BLOCK_SIZE];
    sha256((uint8_t*)salted_password, strlen(salted_password), hash);
    hash_to_hex(hash, hash_output);
}

//register the user
int register_user(AuthSystem *auth, const char *username, const char *password) {
    if (auth->count >= MAX_USERS) {
        return 0; // User limit reached
    }
    
    if (!validate_input(username, MAX_USERNAME) || 
        !validate_input(password, MAX_PASSWORD)) {
        return 0; 
    }
    
    //Checking if username already there.
    for (int i = 0; i < auth->count; i++) {
        if (strcmp(auth->users[i].username, username) == 0) {
            return 0; 
        }
    }
    
    //Creating new user
    User *new_user = &auth->users[auth->count];
    strncpy(new_user->username, username, MAX_USERNAME - 1);
    new_user->username[MAX_USERNAME - 1] = '\0';
    
    hash_password(password, new_user->password_hash);
    new_user->is_active = 0;
    
    auth->count++;
    return 1;
}

int login_user(AuthSystem *auth, const char *username, const char *password) {
    if (!validate_input(username, MAX_USERNAME) || 
        !validate_input(password, MAX_PASSWORD)) {
        return 0;
    }
    
    for (int i = 0; i < auth->count; i++) {
        if (strcmp(auth->users[i].username, username) == 0) {
            char input_hash[HASH_HEX_LEN];
            hash_password(password, input_hash);
            
            if (strcmp(auth->users[i].password_hash, input_hash) == 0) {
                auth->users[i].is_active = 1;
                auth->current_user = &auth->users[i];
                return 1;
            }
        }
    }
    return 0;
}

//logging out user
void logout_user(AuthSystem *auth) {
    if (auth->current_user) {
        auth->current_user->is_active = 0;
    }
    auth->current_user = NULL;
}

//leet them through if they got the right stats
int is_authenticated(AuthSystem *auth) {
    return auth->current_user != NULL && auth->current_user->is_active;
}