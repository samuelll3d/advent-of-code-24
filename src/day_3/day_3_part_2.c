#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct mul_instr_data {
    int x;
    int y;
} mul_instr_data;

typedef struct instr {
    const unsigned char* instruction;
    const void* data;
    const size_t len;
} instruction;

bool is_number_character(const unsigned char _char) {
    if (_char == '0' || _char == '1' || _char == '1' || _char == '2' || _char == '3' || _char == '4'
        || _char == '5' || _char == '6' || _char == '7' || _char == '8' || _char == '9') {
        return true;
    }
    return false;
}

unsigned int find_do_instruction(const unsigned char* read_buf, size_t start_index) {
    static const size_t do_instr_len = 4;
    static const char do_instr[] = "do()";

    for (size_t j = 0; j < do_instr_len; j++) {
        if (read_buf[start_index + j] == do_instr[j]) {
            if (j == do_instr_len - 1) {
                return do_instr_len - 3;
            }
            continue;
        }

        break;
    }

    return 0;
}

unsigned int find_dont_instruction(const unsigned char* read_buf, size_t start_index) {
    static const size_t dont_instr_len = 7;
    static const char dont_instr[] = "don't()";

    for (size_t j = 0; j < dont_instr_len; j++) {
        if (read_buf[start_index + j] == dont_instr[j]) {
            if (j == dont_instr_len - 1) {
                return dont_instr_len - 3;
            }
            continue;
        }

        break;
    }

    return 0;
}

unsigned int find_multiply_instruction(const unsigned char* read_buf, size_t start_index, mul_instr_data* data) {
    static const size_t mul_instr_len = 8;
    static const char mul_instr[] = "mul(%,%)";

    unsigned int read_digits_offset = 0;
    int instr_args[2] = { 0 };
    int instr_arg_index = 0;

    for (size_t j = 0; j < mul_instr_len; j++) {
        if (mul_instr[j] == '%') {
            unsigned char num_buf[10] = { 0 };
            unsigned int num_digits = 0;

            for (; num_digits < 10; num_digits++) {
                num_buf[num_digits] = read_buf[start_index + j + num_digits + read_digits_offset];

                if (is_number_character(num_buf[num_digits])) {
                    continue;
                }

                break;
            }

            if (num_digits) {
                num_buf[num_digits] = '\n';
                instr_args[instr_arg_index] = (int)strtol(num_buf, NULL, 10);
                read_digits_offset += num_digits - 1;
                instr_arg_index++;
                continue;
            }
        }
        else if (read_buf[start_index + j + read_digits_offset] == mul_instr[j]) {
            if (j == mul_instr_len - 1) {
                const mul_instr_data res = { .x = instr_args[0], .y = instr_args[1] };
                *data = res;
                return mul_instr_len + read_digits_offset - 1;
            }
            continue;
        }

        return  0;
    }

    return 0;
}

int main(void) {
    FILE* file = fopen("input.txt", "r");

    if (!file) {
        printf("Could not open file!");
        return -1;
    }

    unsigned int read_buf_len = INT16_MAX;
    unsigned char read_buf[read_buf_len];
    memset(read_buf, 0, sizeof(unsigned char) * INT16_MAX);

    mul_instr_data found_instructions[1000];
    unsigned int instructions_read = 0;
    bool mul_enabled = true;

    for (;;) {
        size_t read = fread(read_buf, sizeof(unsigned char), INT16_MAX, file);
        for (size_t i = 0; i < read; i++) {
            if (read_buf[i] == 'm' && mul_enabled) {
                unsigned int found = find_multiply_instruction(read_buf, i, &found_instructions[instructions_read]);
                if (found > 0) {
                    i += found;
                    instructions_read++;
                    continue;
                }
            }
            else if (read_buf[i] == 'd') {
                unsigned int found = find_do_instruction(read_buf, i);
                if (found > 0) {
                    i += found;
                    mul_enabled = true;
                    continue;
                }
                found = find_dont_instruction(read_buf, i);
                if (found > 0) {
                    i += found;
                    mul_enabled = false;
                    continue;
                }
            }
        }

        if (read_buf[read] == '\000') {
            break;
        }
    }

    unsigned long sum = 0;
    for (int i = 0; i < instructions_read; i++) {
        sum += found_instructions[i].x * found_instructions[i].y;
    }

    printf("Sum of all multiplication instructions is: %lu", sum);
}
