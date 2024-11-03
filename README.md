# Rope Data Structure in C

This project implements a Rope Data Structure in C, allowing operations such as insertion, concatenation, splitting, deletion, and printing of strings. Ropes are useful for efficiently handling large strings and concatenating them.

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
   - Input: A string and an index.
   - Example: Insert "Hello" at index 0.

2. **Concatenate**: Concatenate a new string to the end of the current rope.
   - Input: A string.
   - Example: Concatenate " World" to the current rope.

3. **Join Multiple Ropes**: Join multiple strings into one rope.
   - Input: Number of ropes followed by each string.
   - Example: Join "Hello" and " World".

4. **Split**: Split the rope into two parts at a specified index.
   - Input: An index.
   - Example: Split the rope at index 5.

5. **Delete**: Delete a substring starting from a specified index for a given length.
   - Input: Starting index and length.
   - Example: Delete 5 characters starting from index 2.

6. **Print Rope**: Print the current contents of the rope.

7. **Exit**: Exit the program.

## Expected Outputs

- After performing each operation, the program will display the updated state of the rope.
- For instance, after an insertion, you will see the rope printed with the new string included.
- When splitting, both parts of the rope will be printed separately.

### Example Workflow

1. Select **1** to insert:
Output:

2. Select **2** to concatenate:
Output:

3.Selct **3** to join multiple ropes
output:

4.select **4** to split the ropes at specified index
output:

5.selet **5** to delete the rope at specified index and length
output:

6.select **6** to print the current rope
output:
