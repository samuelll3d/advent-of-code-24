#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getSafety(const long* levels, const long levelCount) {
    long lastDiff = 0;

    for (int j = 1; j <= levelCount; j++) {
        if (j == levelCount) {
            return 1;
        }

        const long diff = levels[j - 1] - levels[j];

        if (llabs(diff) > 3 || diff == 0) {
            return 0;
        }

        if (diff > 0 && lastDiff >= 0) {
            lastDiff = diff;
            continue;
        }

        if (diff < 0 && lastDiff <= 0) {
            lastDiff = diff;
            continue;
        }

        return 0;
    }

    return 0;
}

int getLine(FILE* file, unsigned char* line, int buf_len) {
    for (int i = 0; i < buf_len; i++) {
        unsigned char in = fgetc(file);
        line[i] = in;
        if (in == '\n') {
            return i;
        }
    }
}

long* getLevels(const unsigned char* line_buf, const unsigned int lineLen, int* levelCount) {
    *levelCount = 0;

    for (int j = 0; j <= lineLen; j++) {
        if (line_buf[j] == ' ' || line_buf[j] == '\n') {
            *levelCount = *levelCount + 1;
        }
    }

    long* levels = malloc((*levelCount + 1) * sizeof(long));
    memset(levels, 0, (*levelCount + 1) * sizeof(long));

    const int parseBufLen = 6;
    unsigned char parseBuf[parseBufLen + 1];
    memset(parseBuf, 0, (parseBufLen + 1) * sizeof(unsigned char));

    int parseIndex = 0;
    int levelIndex = 0;

    for (int j = 0; j <= lineLen; j++) {
        if (line_buf[j] != ' ' && line_buf[j] != '\n') {
            assert(parseIndex < parseBufLen);

            parseBuf[parseIndex] = line_buf[j];
            parseIndex++;
        }
        else {
            assert(levelIndex < *levelCount);

            parseBuf[parseIndex] = '\n';

            levels[levelIndex] = strtol(parseBuf, NULL, 10);

            levelIndex++;
            parseIndex = 0;
        }
    }

    return levels;
}