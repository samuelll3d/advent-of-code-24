#pragma once
#include <stdio.h>

unsigned int getLineCount(FILE* file) {
    unsigned int lineCount = 0;

    {
        unsigned char count_buf[65535];
        for (;;) {
            size_t read = fread(count_buf, sizeof(unsigned char), 65535, file);

            for (int i = 0; i < read; i++) {
                if (count_buf[i] == '\n') {
                    lineCount++;
                }
            }

            if (feof(file)) {
                break;
            }
        }
    }

    rewind(file);

    return lineCount;
}

