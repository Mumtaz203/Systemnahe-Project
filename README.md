# Systemnahe-Project


## Project Description
Systemnahe-Project is a program that mimics the functionality of the `ls` command in Linux.  
It can list directory contents, recursively explore subdirectories, and utilize multithreading for efficiency.

## Features
 **List directory contents**  
 **Display file and directory permissions (`-l`)**  
 **Sort by last modified time (`-t`)**  
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
2. make all (or make)

-You can execute the program in Systemnahe-Project directory using:
1. ./program [options] [directory]

-if you want to execute the program anywhere in terminal
1. cd Systemnahe-Project 
2. sudo cp ./program /usr/local/bin/
3. program [options] [directory]


### Usage Examples:

1. program src     (Lists files in the "src" directory)
2. program -l src  (Lists files with detailed attributes (permissions, owner, size))
3. program -t src  (Lists files sorted by last modification time)
4. program -R src  (Recursively lists all subdirectories and files)
5. program -l -t src (Combines detailed listing with sorting by modification time)
6. program -l Systemnahe-Project | grep "test" (Recursively lists all subdirectories and files , and finds lines that includes .c)

##  Running Tests
The project includes unit tests written using CUnit.
- if you want to run tests you have to install CUnit library and then compile tests:
1. sudo apt-get install libcunit1-dev (to install CUnit library).
2. cd Systemnahe-Project (to enter main Project directory).
3. ./test_program (if you want to execute the test_program anywhere in terminal: sudo cp ./test_program /usr/local/bin/)

## Feedback About Project
This project took more time than we thought , we gave a lot of efford but we still have problems that we couldn't fix. 


## Contributors
This project was developed by:

- Mümtaz Erdogan 
- Erkin Caliskan
- Samet Avci
- Umut Avci


