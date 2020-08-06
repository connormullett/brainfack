
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"

#define MEM_SIZE 30000
#define STACK_SIZE 100


bool is_valid_instruction(char c) {
    return strchr("+-><.,[]", c) != NULL;
}


int main(int argc, char** argv) {

    if (argc < 2) {
        perror("Usage: brainfuck <filename>");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error reading file");
        exit(1);
    }

    
    // memory and program tape
    int memory[MEM_SIZE];
    int program[MEM_SIZE];

    // dry run for checking loop balance and removing nonvalid operations
    char c;
    int i = 0;
    int left_balance = 0, right_balance = 0;
    while ((c = fgetc(fp)) != EOF && i < MEM_SIZE) {
        if (is_valid_instruction(c)) {
            program[i++] = c;
            if (c == '[') left_balance++;
            else if (c == ']') right_balance++;

            if (right_balance > left_balance) {
                perror("loops imbalanced");
                exit(1);
            }
        }
    }

    fclose(fp);

    if (left_balance != right_balance) {
        perror("loops imbalanced");
        exit(1);
    }

    int memory_pointer = 0;
    int instruction_pointer = 0;
    stack* loop_stack = create_stack(STACK_SIZE);
    
    while (instruction_pointer < MEM_SIZE && program[instruction_pointer] != 0) {
        
        char op = program[instruction_pointer];

        if (op == '+') memory[memory_pointer]++;
        else if (op == '-') memory[memory_pointer]--;
        else if (op == '<') {
            // check if at cell 0
            if (memory_pointer > 0) memory_pointer--;
            else memory_pointer = MEM_SIZE - 1;  // last cell
        }
        else if (op == '>') {
            if (memory_pointer < MEM_SIZE - 1) memory_pointer++;
            else memory_pointer = 0;
        }
        else if (op == '[') {
            if (memory[memory_pointer] == 0) 
                while (program[instruction_pointer] != ']') instruction_pointer++;
            else {
                push(loop_stack, instruction_pointer);
            }
        }
        else if (op == ']') {
            if (memory[memory_pointer] != 0)
                instruction_pointer = peek(loop_stack);
            else {
                pop(loop_stack);
            }
        }
        else if (op == '.') putchar(memory[memory_pointer]);
        else if (op == ',') memory[memory_pointer] = getchar();

        instruction_pointer++;
    }
}
