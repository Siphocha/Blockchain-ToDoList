#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "todo.h"
#include "storage.h"
#include "utils.h"

//
void display_menu();
void handle_auth_menu(AuthSystem *auth);
void handle_main_menu(TodoSystem *todo, AuthSystem *auth);

int main() {
    printf("!!!!! Blockchain Transact App(To Do One) !!!!!\n\n");
    
    AuthSystem auth;
    TodoSystem todo;
    
    init_auth(&auth);
    init_todo_system(&todo);
    
    //Load that users saved data.
    if (!load_users(&auth)) {
        printf("user data found.\n");
    }
    if (!load_blockchain(&todo.blockchain)) {
        printf("No saved blockchain found. Creating new blockchain!\n");
        //Create genesis block if none already present.
        Block *genesis = create_genesis_block();
        if (genesis) {
            add_block(&todo.blockchain, genesis);
        }
    }
    
    while (1) {
        if (!is_authenticated(&auth)) {
            handle_auth_menu(&auth);
        } else {
            handle_main_menu(&todo, &auth);
        }
    }
    
    return 0;
}

void display_menu() {
    printf("\n!!!!! MENU !!!!!\n");
    printf("1. Adding New Task\n");
    printf("2. View Tasks\n");
    printf("3. Mark as Complete\n");
    printf("4. Saving Data\n");
    printf("5. Log out\n");
    printf("6. Exit NOWWWW\n");
    printf("!!!!!!!!!!!!!!!!!!!\n");
    printf("Choice: ");
}

void handle_auth_menu(AuthSystem *auth) {
    int choice;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    printf("\n!!!!! AUTHENTICATION !!!!!\n");
    printf("1. Registering\n");
    printf("2. Logging in\n");
    printf("3. Exiting\n");
    printf("!!!!!!!!!!!!!!!!!!!!!\n");
    printf("Choice: ");
    
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        printf("Invalid input.\n");
        return;
    }
    clear_input_buffer();
    
    switch (choice) {
        case 1: 
            printf("Username: ");
            if (!fgets(username, sizeof(username), stdin)) {
                printf("Input error.\n");
                break;
            }
            username[strcspn(username, "\n")] = 0;
            
            printf("Password: ");
            if (!fgets(password, sizeof(password), stdin)) {
                printf("Input error.\n");
                break;
            }
            password[strcspn(password, "\n")] = 0;
            
            if (register_user(auth, username, password)) {
                printf("Successfully Registered!\n");
                save_users(auth);
            } else {
                printf("Registration failed, name already there maybe.\n");
            }
            break;
            
        case 2: // Login
            printf("Username: ");
            if (!fgets(username, sizeof(username), stdin)) {
                printf("Input error.\n");
                break;
            }
            username[strcspn(username, "\n")] = 0;
            
            printf("Password: ");
            if (!fgets(password, sizeof(password), stdin)) {
                printf("Input error.\n");
                break;
            }
            password[strcspn(password, "\n")] = 0;
            
            if (login_user(auth, username, password)) {
                printf("Successfully in, welcome!!! %s\n", username);
            } else {
                printf("Login failed man. idk what you want.\n");
            }
            break;
            
        case 3:
            printf("Goodbye!\n");
            exit(0);
            
        default:
            printf("Pick a proper option\n");
    }
}

void handle_main_menu(TodoSystem *todo, AuthSystem *auth) {
    int choice;
    char description[MAX_TASK];
    int task_index;
    
    display_menu();
    
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        printf("Invalid input.\n");
        return;
    }
    clear_input_buffer();
    
    switch (choice) {
        case 1: { 
            printf("Task description: ");
            if (!fgets(description, sizeof(description), stdin)) {
                printf("Input error.\n");
                break;
            }
            description[strcspn(description, "\n")] = 0;
            
            if (add_task(todo, description)) {
                printf("Added successfully!\n");
            } else {
                printf("Invalid input.\n");
            }
            break;
        }
            
        case 2: 
            display_tasks(todo);
            break;
            
        case 3: { // Complete task
            printf("Enter task number to complete: ");
            if (scanf("%d", &task_index) != 1) {
                clear_input_buffer();
                printf("Invalid input.\n");
                break;
            }
            clear_input_buffer();
            
            if (complete_task(todo, task_index)) {
                printf("Task complete!\n");
            } else {
                printf("Invalid task number!\n");
            }
            break;
        }
            
        case 4: 
            if (save_blockchain(&todo->blockchain) && save_users(auth)) {
                printf("Data saved successfully!\n");
            } else {
                printf("Error saving data\n");
            }
            break;
            
        case 5: 
            logout_user(auth);
            printf("Logged out!\n");
            break;
            
        case 6: 
            printf("Saving data before exit...\n");
            save_blockchain(&todo->blockchain);
            save_users(auth);
            printf("See ya!!\n");
            exit(0);
            
        default:
            printf("Invalid choice.\n");
    }
}