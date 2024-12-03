#include <day_2_common.h>
#include <common.h>
#include <stdio.h>

int main(void) {
    FILE* file = fopen("input.txt", "r");

    if (!file) {
        printf("Could not open file!");
        return -1;
    }

    unsigned int lineCount = getLineCount(file);

    unsigned int report_is_safe[lineCount];

    // Read lineCount lines
    for (int line = 0; line < lineCount; line++) {
        unsigned char line_buf[100] = { 0 };

        const unsigned int lineLen = getLine(file, line_buf, 100);

        int levelCount;
        long* levels = getLevels(line_buf, lineLen, &levelCount);

        report_is_safe[line] = getSafety(levels, levelCount);
    }

    unsigned int safe_reports = 0;
    for (int i = 0; i < lineCount; i++) {
        if (report_is_safe[i]) {
            safe_reports++;
        }
    }

    printf("Found %d safe reports.\n", safe_reports);
}
