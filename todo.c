#include "todo.h"
#include "sha256.h"  
#include "utils.h"
#include <stdio.h>

void init_todo_system(TodoSystem *todo) {
    init_blockchain(&todo->blockchain);
    todo->task_count = 0;
    
    //Creation of gensis block
    Block *genesis = create_genesis_block();
    if (genesis) {
        add_block(&todo->blockchain, genesis);
    }
}

int validate_task_input(const char *description) {
    return validate_input(description, MAX_TASK);
}

int add_task(TodoSystem *todo, const char *description) {
    if (!validate_task_input(description)) {
        return 0;
    }
    
    Task new_task;
    strncpy(new_task.description, description, MAX_TASK - 1);
    new_task.description[MAX_TASK - 1] = '\0'; 
    new_task.completed = 0;
    get_current_timestamp(new_task.created, sizeof(new_task.created));
    strcpy(new_task.completed_date, "");
    
    char previous_hash[HASH_HEX_LEN];
    if (todo->blockchain.tail) {
        strcpy(previous_hash, todo->blockchain.tail->hash);
    } else {
        strcpy(previous_hash, "0");
    }
    
    Block *new_block = create_block(new_task, previous_hash);
    if (!new_block) {
        return 0;
    }
    
    add_block(&todo->blockchain, new_block);
    todo->task_count++;
    return 1;
}

int complete_task(TodoSystem *todo, int task_index) {
    Block *current = todo->blockchain.head;
    int current_index = 0;
    
    //Skipping genesis block
    if (current) {
        current = current->next;  
    }
    
    while (current) {
        if (current_index == task_index && !current->task.completed) {
            current->task.completed = 1;
            get_current_timestamp(current->task.completed_date, 
                                 sizeof(current->task.completed_date));
            
            calculate_block_hash(current);
            return 1;
        }
        current = current->next;
        current_index++;
    }
    return 0;
}

void display_tasks(TodoSystem *todo) {
    printf("\n!!!!! Overall LIST !!!!!!!!!!!\n");
    printf("Blockchain Valid: %s\n", 
           validate_blockchain(&todo->blockchain) ? "Yes" : "No (Tampered!)");
    printf("Total Blocks: %d\n", todo->blockchain.length);
    printf("!!!!!!!!!!!!!!!!!!!!\n\n");
    
    Block *current = todo->blockchain.head;
    int task_num = 0;
    
    if (current && current->index == 0) {
        current = current->next;
    }
    
    while (current) {
        printf("[%d] %s\n", task_num, current->task.description);
        printf("    Status: %s\n", 
               current->task.completed ? "Completed" : "Pending");
        printf("    Created: %s\n", current->task.created);
        if (current->task.completed) {
            printf("    Completed: %s\n", current->task.completed_date);
        }
        printf("    Block #%d | Hash: %.8s...\n", 
               current->index, current->hash);
        printf("    Prev Hash: %.8s...\n\n", current->previous_hash);
        
        current = current->next;
        task_num++;
    }
    
    if (task_num == 0) {
        printf("No tasks available!\n\n");
    }
}