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

        int res = getSafety(levels, levelCount);
        if (!res) {
            int found_safe = 0;
            long levels_one_removed[levelCount - 1];

            for (int i = 0; i < levelCount; i++) {
                int index = 0;
                for (int j = 0; j <= levelCount - 1; j++) {
                    if (i == j) { continue; }
                    levels_one_removed[index] = levels[j];
                    index++;
                }
                if (getSafety(levels_one_removed, levelCount - 1)) {
                    found_safe = 1;
                    break;
                }
            }

            report_is_safe[line] = found_safe;
        }
        else {
            report_is_safe[line] = 1;
        }
    }

    unsigned int safe_reports = 0;
    for (int i = 0; i < lineCount; i++) {
        if (report_is_safe[i]) {
            safe_reports++;
        }
    }

    printf("Found %d safe reports.\n", safe_reports);
}
