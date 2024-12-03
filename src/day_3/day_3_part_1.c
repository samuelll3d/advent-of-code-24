#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct mul_instr {
    int x;
    int y;
} mul_instr;

bool is_number_character(const unsigned char _char) {
    if (_char == '0' || _char == '1' || _char == '1' || _char == '2' || _char == '3' || _char == '4'
        || _char == '5' || _char == '6' || _char == '7' || _char == '8' || _char == '9') {
        return true;
    }
    return false;
}

int main(void) {
    unsigned char mul_instruction[] = "mul(%,%)";
    size_t mul_instr_len = strlen((const char*)mul_instruction);

    FILE* file = fopen("input.txt", "r");

    if (!file) {
        printf("Could not open file!");
        return -1;
    }

    unsigned int read_buf_len = INT16_MAX;
    unsigned char read_buf[read_buf_len];
    memset(read_buf, 0, sizeof(unsigned char) * INT16_MAX);

    mul_instr instructions[1000];
    unsigned int instructions_read = 0;

    for (;;) {
        size_t read = fread(read_buf, sizeof(unsigned char), INT16_MAX, file);
        for (size_t i = 0; i < read; i++) {
            int instr_args[2] = { 0 };
            int instr_arg_index = 0;
            unsigned int read_digits_offset = 0;
            bool full_instruction = false;

            for (size_t j = 0; j < mul_instr_len; j++) {
                if (mul_instruction[j] == '%') {
                    unsigned char num_buf[10] = { 0 };
                    unsigned int num_digits = 0;
                    unsigned int total_digits_read = 0;

                    for (; num_digits < 10; num_digits++) {
                        num_buf[num_digits] = read_buf[i + j + num_digits + read_digits_offset];

                        if (is_number_character(num_buf[num_digits])) {
                            continue;
                        }

                        break;
                    }

                    if (num_digits) {
                        num_buf[num_digits] = '\n';
                        instr_args[instr_arg_index] = (int)strtol(num_buf, NULL, 10);
                        read_digits_offset += num_digits - 1;
                        total_digits_read += num_digits;
                        instr_arg_index++;
                        continue;
                    }
                }
                else if (read_buf[i + j + read_digits_offset] == mul_instruction[j]) {
                    if (j == mul_instr_len - 1) {
                        full_instruction = true;
                    }
                    continue;
                }
                break;
            }

            if (full_instruction) {
                const mul_instr new_instr = { .x = instr_args[0], .y = instr_args[1] };
                i += mul_instr_len + read_digits_offset - 1;
                instructions[instructions_read] = new_instr;
                instructions_read++;
            }
        }

        if (read_buf[read] == '\000') {
            break;
        }
    }

    unsigned long sum = 0;
    for (int i = 0; i < instructions_read; i++) {
        sum += instructions[i].x * instructions[i].y;
    }

    printf("Sum of all multiplication instructions is: %lu", sum);
}
