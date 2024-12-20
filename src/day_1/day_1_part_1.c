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

    qsort(list_1, 1001, sizeof(long long), compare);
    qsort(list_2, 1001, sizeof(long long), compare);

    int64_t distances[1001] = { 0 };
    int64_t sum_of_distances = 0;

    for (int i = 0; i < 1001; i++) {
        sum_of_distances += llabs(list_1[i] - list_2[i]);
    }

    printf("%ld", sum_of_distances);
}
