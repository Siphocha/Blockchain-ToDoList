#ifndef AUTH_H
#define AUTH_H

#include "utils.h"
//Might as well make these users 1000 plus why not? Nah keep it low.
#define MAX_USERS 100

typedef struct {
    char username[MAX_USERNAME];
    char password_hash[HASH_HEX_LEN];
    int is_active;
} User;

typedef struct {
    User users[MAX_USERS];
    int count;
    User *current_user;
} AuthSystem;

//All relevant function declarations for baseline access.
void init_auth(AuthSystem *auth);
int register_user(AuthSystem *auth, const char *username, const char *password);
int login_user(AuthSystem *auth, const char *username, const char *password);
void logout_user(AuthSystem *auth);
int is_authenticated(AuthSystem *auth);
void hash_password(const char *password, char *hash_output);

#endif