#ifndef STORAGE_H
#define STORAGE_H

#include "blockchain.h"
#include "auth.h"

#define BLOCKCHAIN_FILE "blockchain.dat"
#define USERS_FILE "users.dat"

int save_blockchain(Blockchain *bc);
int load_blockchain(Blockchain *bc);
int save_users(AuthSystem *auth);
int load_users(AuthSystem *auth);

#endif