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
git clone https://github.com/Mumtaz203/Systemnahe-Project.git

- Once cloned, navigate into the project directory:
cd Systemnahe-Project

- Compile the program:
1.make clean
2.make

-You can execute the program in Systemnahe-Project directory using:
./program [options] <directory>

-if you want to execute the program anywhere in terminal
cd Systemnahe-Project 
sudo cp ./program /usr/local/bin/
program [options] <directory>


### Usage Examples:

program src     (Lists files in the "src" directory)
program -l src  (Lists files with detailed attributes (permissions, owner, size))
program -T src  (Lists files sorted by last modification time)
program -R src  (Recursively lists all subdirectories and files)
program -l -T src (Combines detailed listing with sorting by modification time)
program -R Systemnahe-Project | grep "\.c$" (Recursively lists all subdirectories and files , and finds lines that ends with .c)

##  Running Tests
The project includes unit tests written using CUnit.
- if you want to run tests you have to install CUnit library and then compile tests:
1.sudo apt-get install libcunit1-dev (to install CUnit library).
2.cd Systemnahe-Project (to enter main Project directory).
3.cd tests (to enter tests directory).
4.gcc -o test_program test_cases.c -lcunit (to compile tests).
5.sudo cp ./test_program /usr/local/bin/ (to use tests in Systemnahe-Project)
6.cd .. (now you are in Systemnahe-Project directory)
test_program(we couldn't implement a failed or passed test , we wanted to compare results of ls and our program.)


## Feedback About Project
This project took more time than we thought , we gave a lot of efford but we still have problems that we couldn't fix. 


## Contributors
This project was developed by:

Mümtaz Erdogan
Erkin Caliskan
Samet Avci
Umut Avci


