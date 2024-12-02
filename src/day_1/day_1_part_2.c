#include <day_1_common.c>

int main(void) {
    FILE* file = fopen("input.txt", "r");

    if (!file) {
        printf("Could not open file!");
        return -1;
    }

    long long list_1[1001] = { 0 };
    long long list_2[1001] = { 0 };

    getNumbers(list_1, list_2, file);

    fclose(file);

    long long appearances = 0;
    long long similarity = 0;

    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++) {
            if (list_1[i] == list_2[j]) {
                appearances++;
            }
        }
        similarity += list_1[i] * appearances;
        appearances = 0;
    }

    printf("%ld", similarity);
}