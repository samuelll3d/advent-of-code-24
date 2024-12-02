#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
    FILE* file = fopen("input.txt", "r");

    if (!file) {
        printf("Could not open file!");
        return -1;
    }

    long int fileBegin = ftell(file);
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

    unsigned int report_is_safe[lineCount];

    // Read lineCount lines
    for (int line = 0; line < lineCount; line++) {
        int lineIndex = 0;
        unsigned char line_buf[100] = { 0 };
        unsigned char in;

        // Read characters into line_buf until a newline is hit
        do {
            in = fgetc(file);
            line_buf[lineIndex] = in;
            lineIndex++;
        } while (in != '\n');

        const unsigned int lineLen = lineIndex;

        int levelCount = 0;

        for (int j = 0; j <= lineLen; j++) {
            if (line_buf[j] == ' ' || line_buf[j] == '\n') {
                levelCount++;
            }
        }

        long levels[levelCount + 1];
        memset(levels, 0, (levelCount + 1) * sizeof(long));

        const int parseBufLen = 6;
        unsigned char parseBuf[parseBufLen + 1];
        memset(parseBuf, 0, (parseBufLen + 1) * sizeof(unsigned char));

        int parseIndex = 0;
        int levelIndex = 0;

        for (int j = 0; j <= lineLen; j++) {
            if (line_buf[j] != ' ' && line_buf[j] != '\n') {
                if (parseIndex >= parseBufLen) {
                    free(levels);
                    free(parseBuf);
                    return -1;
                }

                parseBuf[parseIndex] = line_buf[j];
                parseIndex++;
            }
            else {
                if (levelIndex >= levelCount) {
                    free(levels);
                    free(parseBuf);
                    return -1;
                }

                parseBuf[parseIndex] = '\n';

                levels[levelIndex] = strtol((char*)parseBuf, NULL, 10);

                levelIndex++;
                parseIndex = 0;
            }
        }

        long lastDiff = 0;
        for (int j = 1; j <= levelCount; j++) {
            if (j == levelCount) {
                report_is_safe[line] = 1;
                break;
            }

            const long diff = levels[j - 1] - levels[j];

            if (llabs(diff) > 3 || diff == 0) {
                report_is_safe[line] = 0;
                break;
            }

            if (diff > 0 && lastDiff >= 0) {
                lastDiff = diff;
                continue;
            }

            if (diff < 0 && lastDiff <= 0) {
                lastDiff = diff;
                continue;
            }

            report_is_safe[line] = 0;
            break;
        }

        lineIndex = 0;
    }

    unsigned int safe_reports = 0;
    for (int i = 0; i < lineCount; i++) {
        if (report_is_safe[i]) {
            safe_reports++;
        }
    }

    printf("Found %d safe reports.\n", safe_reports);
}
