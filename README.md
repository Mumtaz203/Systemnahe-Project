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
make

-You can execute the program using:
./program [options] <directory>

-if you want to execute the program anywhere in terminal 
sudo cp Systemnahe-Project/program /usr/local/bin/
program [options] <directory>


### Usage Examples:

program src     | Lists files in the "src" directory |
program -l src  | Lists files with detailed attributes (permissions, owner, size) |
program -T src  | Lists files sorted by last modification time |
program -R src  | Recursively lists all subdirectories and files |
program -l -T src | Combines detailed listing with sorting by modification time |
-You can use it without ./ too

##  Running Tests
The project includes unit tests written using CUnit.
- if you want to run tests you have to install CUnit library and then compile tests:
sudo apt-get install libcunit1-dev
cd Systemnahe-Project
make clean 
make
make test

## Contributors
This project was developed by:

Mümtaz Erdogan
Erkin Caliskan
Samet Avci
Umut Avci


