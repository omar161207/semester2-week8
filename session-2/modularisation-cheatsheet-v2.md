# Modularisation and Makefiles Cheat Sheet

## File Structure

### Header File (.h)
- Contains **declarations** (not definitions)
- Protected by include guards
- Includes only what's necessary

```c
#ifndef MY_MODULE_H
#define MY_MODULE_H

/* Constants and typedefs */
#define MAX_SIZE 100
typedef struct { /* ... */ } MyStruct;

/* Function prototypes */
/**
 * @brief Description of what the function does
 * @param param Description of the parameter
 * @return Description of the return value
 */
void my_function(int param);

#endif /* MY_MODULE_H */
```

### Implementation File (.c)
- Contains **definitions** (actual code)
- Includes its own header first, then others
- Implements all functions declared in header

```c
#include "my_module.h"
#include <stdio.h>

void my_function(int param) {
    /* Function implementation */
}
```

### Main Program File (main.c)
- Contains the main() function
- Includes necessary headers
- Focuses on program flow, not implementation details

## Include Guards

```c
#ifndef UNIQUE_NAME_H  /* Typically based on filename */
#define UNIQUE_NAME_H

/* Header content */

#endif /* UNIQUE_NAME_H */
```

## Directory Structure

```
project/
├── include/       (Header files)
│   ├── module1.h
│   └── module2.h
├── src/           (Source files)
│   ├── module1.c
│   ├── module2.c
│   └── main.c
├── obj/           (Object files)
├── bin/           (Executable)
└── Makefile
```

## Compilation Process

1. **Preprocessing:** Handle #include, #define, etc.
   ```
   gcc -E source.c -o source.i
   ```

2. **Compiling:** Translate to assembly code
   ```
   gcc -S source.i -o source.s
   ```

3. **Assembly:** Convert to object code
   ```
   gcc -c source.s -o source.o
   ```

4. **Linking:** Combine object files into executable
   ```
   gcc source.o -o program
   ```

5. **All-in-one:** (For convenience)
   ```
   gcc source.c -o program
   ```

## Makefile Syntax

### Basic Structure
```make
target: dependencies
<tab>commands
```

### Variables
```make
CC = gcc
CFLAGS = -Wall -g
TARGET = program
```

### Using Variables
```make
$(TARGET): main.o
	$(CC) $(CFLAGS) main.o -o $(TARGET)
```

### Automatic Variables
- `$@`: Target name
- `$<`: First dependency
- `$^`: All dependencies
- `$*`: Stem in pattern rule

### Pattern Rules
```make
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

### Phony Targets
```make
.PHONY: clean all
clean:
	rm -f *.o $(TARGET)
```

## Common Makefile Recipes

### Simple Program
```make
program: main.o helper.o
	gcc main.o helper.o -o program

main.o: main.c helper.h
	gcc -c main.c

helper.o: helper.c helper.h
	gcc -c helper.c

clean:
	rm -f *.o program
```

### Directory Structure
```make
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TARGET = program

$(TARGET): $(OBJ_DIR)/main.o $(OBJ_DIR)/helper.o
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
```

### Automatic Source Discovery
```make
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@
```

### Automatic Dependencies
```make
DEPS = $(OBJ_FILES:.o=.d)

%.d: %.c
	$(CC) -MM -MF $@ -MP -MT "$*.o $@" $<

-include $(DEPS)
```
This automatically tracks header dependencies, ensuring proper rebuilds when headers change.

## Make Command Options

- `make`: Build the default target
- `make target`: Build a specific target
- `make -n`: Dry run (show commands without executing)
- `make -B`: Force rebuild of all targets
- `make -j4`: Parallel build using 4 processes
- `make -f filename`: Use a specific makefile
- `make -d`: Debug mode (show details about decisions)

## Common Errors

- **"missing separator"** → Check for tabs (not spaces) in makefiles (use `cat -e Makefile` to see tabs as ^I)
- **"undefined reference"** → Missing implementation or linking issue
- **"redefinition"** → Missing or incorrect include guards
- **"No such file or directory"** → Incorrect include path or missing file
- **"No rule to make target"** → Missing dependency or typo in makefile

## Best Practices

### Modularisation
- One module per logical component
- Keep interfaces minimal
- Hide implementation details in .c files
- Define clear module boundaries
- Document interfaces in header files

### Documentation Styles
```c
/**
 * @brief Short description of the function
 *
 * Detailed description if needed with more information
 * about what the function does and any edge cases.
 *
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
int function_name(int param1, char param2);
```

### Makefiles
- Use variables for flexibility
- Specify all dependencies correctly
- Include header dependencies
- Use pattern rules for similar targets
- Create phony targets for utility operations
- Document non-obvious rules
- Use tabs (not spaces) for command indentation
