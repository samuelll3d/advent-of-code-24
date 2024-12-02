#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    long long number_a = * ( ( long long* ) a);
    long long number_b = * ( ( long long* ) b);

    if (number_a > number_b) {
        return 1;
    }
    if (number_a < number_b) {
        return -1;
    }
    return 0;
}

int isNumChar(const unsigned char in) {
    if (in == '0' || in == '1' || in == '2' || in == '3' || in == '4' || in == '5' || in == '6' || in == '7' || in == '8' || in == '9') {
        return 1;
    }

    return 0;
}

void getNumbers(long long* list_1, long long* list_2, FILE* file) {
    unsigned char line[100] = { 0 };
    unsigned char read_buf[10] = { 0 };

    for (int i = 0; i < 1000; i++) {
        int line_end = 0;
        for (int j = 0; j < 100; j++) {
            line[j] = fgetc(file);
            if (line[j] == '\n') {
                line_end = j;
                break;
            }
        }

        list_1[i] = strtoll(line, NULL, 10);

        int index = 5;
        for (int j = line_end; j > 0; j--) {
            if (line[j] != ' ') {
                read_buf[index] = line[j];
                index--;
            }
            else {
                list_2[i] = strtoll(read_buf, NULL, 10);
                break;
            }
        }
    }
}