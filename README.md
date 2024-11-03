# Rope Data Structure in C

This project implements a Rope Data Structure in C, allowing operations such as insertion, appending, deletion, concatenation, and printing of strings. Ropes are useful for efficiently handling large strings and concatenating them.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Operations](#operations)
- [Expected Outputs](#expected-outputs)
- [License](#license)

## Installation

To run this program, you'll need a C compiler. You can use GCC or any other compatible compiler.

1. Clone this repository:
    ```bash
    git clone <repository-url>
    cd <repository-directory>
    ```

2. Compile the program using the following command:
    ```bash
    gcc -o rope rope.c
    ```
   Replace `rope.c` with the name of your C source file if different.

3. Run the compiled program:
    ```bash
    ./rope
    ```

## Usage

Upon running the program, a menu will appear prompting you to select an operation. You can input your choice by entering the corresponding number.

### Operations

1. **Insert**: Insert a string at a specified index.
   - Input: A string.
   - Example: Insert "Hello" at index 0.

2. **Append**: Append a string to the end of the current rope.
   - Input: A string.
   - Example: Append " World" to the current rope.

3. **Concatenate Ropes**: Concatenate a new string as a rope to the existing rope.
   - Input: A string.
   - Example: Concatenate "Hello" and " World".

4. **Delete**: Delete a substring starting from a specified index for a given length.
   - Input: Starting index and length.
   - Example: Delete 5 characters starting from index 2.

5. **Print Rope**: Print the current contents of the rope.

6. **Exit**: Exit the program.

## Expected Outputs

- After performing each operation, the program will display the updated state of the rope.
- For instance, after an insertion, you will see the rope printed with the new string included.
- When deleting, the program will show the rope without the specified substring.



