# Systemnahe-Project


## Project Description
Systemnahe-Project is a program that mimics the functionality of the `ls` command in Linux.  
It can list directory contents, recursively explore subdirectories, and utilize multithreading for efficiency.

## Features
 **List directory contents**  
 **Display file and directory permissions (`-l`)**  
 **Sort by last modified time (`-T`)**  
 **Recursive directory listing (`-R`)**  
 **Multithreading support**  
 **File reading/writing operations**

## Installation & Usage

### **Requirements**
- **Linux operating system**
- **GCC compiler**
- **CUnit test framework (optional)**

### **Steps**
- Clone the repository:
1. git clone https://github.com/Mumtaz203/Systemnahe-Project.git

- Once cloned, navigate into the project directory:
1. cd Systemnahe-Project

- Compile the program:
1. make clean
2. make

-You can execute the program in Systemnahe-Project directory using:
1. ./program [options] <directory>

-if you want to execute the program anywhere in terminal
1. cd Systemnahe-Project 
2. sudo cp ./program /usr/local/bin/
3. program [options] <directory>


### Usage Examples:

1. program src     (Lists files in the "src" directory)
2. program -l src  (Lists files with detailed attributes (permissions, owner, size))
3. program -T src  (Lists files sorted by last modification time)
4. program -R src  (Recursively lists all subdirectories and files)
5. program -l -T src (Combines detailed listing with sorting by modification time)
6. program -R Systemnahe-Project | grep "\.c" (Recursively lists all subdirectories and files , and finds lines that includes .c)

##  Running Tests
The project includes unit tests written using CUnit.
- if you want to run tests you have to install CUnit library and then compile tests:
1. sudo apt-get install libcunit1-dev (to install CUnit library).
2. cd Systemnahe-Project (to enter main Project directory).
3. cd tests (to enter tests directory).
4. gcc -o test_program test_cases.c -lcunit (to compile tests).
6. cd .. (now you are in Systemnahe-Project directory)
7. make clean
8. make 
9. make test (we couldn't implement a failed or passed test , we wanted to compare results of ls and our program.)


## Feedback About Project
This project took more time than we thought , we gave a lot of efford but we still have problems that we couldn't fix. 


## Contributors
This project was developed by:

- Mümtaz Erdogan 
- Erkin Caliskan
- Samet Avci
- Umut Avci


