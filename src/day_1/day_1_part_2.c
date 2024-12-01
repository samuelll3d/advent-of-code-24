#include <day_1_common.h>

int main(void) {
    FILE* file = fopen("input.txt", "r");

    if (!file) {
        printf("Could not open file!");
        return -1;
    }

    int64_t list_1[1001] = { 0 };
    int64_t list_2[1001] = { 0 };

    getNumbers(list_1, list_2, file);

    fclose(file);

    int64_t appearances = 0;
    int64_t similarity = 0;

    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++) {
            if (list_1[i] == list_2[j]) {
                appearances++;
            }
        }
        similarity += list_1[i] * appearances;
        appearances = 0;
    }

    printf("%lld", similarity);
}