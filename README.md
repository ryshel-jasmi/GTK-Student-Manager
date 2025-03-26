# GTK-Student-Manager

A simple **Student Management System** built using **C and GTK**. This application allows users to **add, delete, search, and view students**, storing data in a text file.

## Features

- 📌 **Add Student**: Save student details (ID, Name, Age, Course, Year, Contact).  
- 🗑️ **Delete Student**: Remove a student by ID.  
- 🔍 **Search Student**: Retrieve details of a student by ID.  
- 📄 **View Students**: Display all saved student records.  

## Installation  
1. Install **GTK** on Windows.  
2. Ensure **GCC** (MinGW) is installed.  
3. Follow the compilation steps below.  

## Compilation & Execution  

### Compile using **GCC**:  
```sh
gcc student_manager.c -o student_manager `pkg-config --cflags --libs gtk+-3.0`

### Run the program:  
```sh
./student_manager
