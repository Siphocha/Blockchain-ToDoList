# Blockchain-ToDoList
Making a C based ToDoList using Blockchain principles of design and operations.

# Project Structure
main.c              
blockchain.c/.h     
auth.c/.h          
sha256.c/.h        
todo.c/.h          
storage.c/.h       
utils.c/.h         
Makefile           
blockchain.dat     
users.dat          
README.md          
Compilation Instructions

# Prerequisites
GCC compiler (You gotta at leats have C on your system.Get WSL if you dont)

Standard C library

# Running Application

1: Using Makefile (Recommended)
- make clean
- make
- make run


# Workflow Exemplar

Add tasks: Enter task descriptions

View tasks: Choose option 2 to see your blockchain-based to-do list

Complete tasks: Choose option 3 and enter task number

Save data: Choose option 4 to persist your data

Exit safely: Choose option 6 to save and exit

# Key Commands
Add Task: Creates a new blockchain block containing your task

View Tasks: Displays all tasks with blockchain  status

Mark Complete: Updates task status 

Save Data: Manually save blockchain and user data to files

Logout: End current session (data remains saved)

Exit: Save data and close application

# Security Features
Password Security: All passwords are hashed with SHA-256 and salt before storage

Blockchain Integrity: Each block contains hash of previous block, making tampering evident

Input Validation: All user inputs are validated for security and correctness

Data Encryption: Data is stored in binary format with integrity checks

# Error Handling
Error handles for 

Invalid user inputs

File I/O errors

Memory allocation failures

Blockchain corruption

Authentication failures

All errors are reported with clear messages and the application continues running where possible.


# Blockchain Implementation
Genesis Block: Created automatically on first run

Block Structure: Index, timestamp, task data, previous hash, current hash

Hash Algorithm: SHA-256

Validation: Automatic validation on load and before display
