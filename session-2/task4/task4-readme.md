# Task 4: Creating a project Makefile

## Code and basic Makefile

The code has been organised into project `src/` and `include/` folders.

The `Makefile` provided assumes files are all in the same folder.

## Step 1 - source code and header files

C-files in the `src/` folder include header files that are in a different location.

Relative to the source code the header files are in the `../include/` folder.

Modify the source code files to `#include` header files from the correct location.

## Step 2 - Makefile

The `Makefile` is in the top level folder and all the files that are used or produced are in a lower level folder. 

We have to modify occurences of each filename in the `Makfile` with the appropriate location

- Source code (.c) files should be `src/*.c`
- Header (.h) files should be `include/*.h`
- Object (.o) files should be `obj/*.o`
- Executable file should be `bin/student`

Once you have made the modifications test the `make` command.

Test the executable in the `bin/` folder.

Test `make clean`.

## Step 3 - extension

We can include the same techniques from Task 2 to define variables and wildcards
to produce a more generic Makefile. 
