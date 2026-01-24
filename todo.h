#ifndef TODO_H
#define TODO_H

#include "blockchain.h"

typedef struct {
    Blockchain blockchain;
    int task_count;
} TodoSystem;

void init_todo_system(TodoSystem *todo);
int add_task(TodoSystem *todo, const char *description);
int complete_task(TodoSystem *todo, int task_index);
void display_tasks(TodoSystem *todo);
int validate_task_input(const char *description);

#endif