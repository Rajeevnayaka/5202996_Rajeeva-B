#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/*
 * Function: isValid
 * -----------------
 * Checks if the string can be considered "valid".
 * A string is valid if:
 *  1. All characters appear the same number of times, OR
 *  2. It can become valid by removing exactly one character.
 *
 * Returns "YES" or "NO".
 */
char* isValid(char* s) {
    static char yes[] = "YES";
    static char no[]  = "NO";

    int freq[26] = {0};

    // Count frequency of each character
    for (int i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
    }

    // Collect non-zero frequencies
    int countArr[26], n = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            countArr[n++] = freq[i];
        }
    }

    // Find min and max frequencies
    int minFreq = INT_MAX, maxFreq = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (countArr[i] < minFreq) minFreq = countArr[i];
        if (countArr[i] > maxFreq) maxFreq = countArr[i];
    }

    if (minFreq == maxFreq) {
        return yes;  // All equal
    }

    int minCount = 0, maxCount = 0;
    for (int i = 0; i < n; i++) {
        if (countArr[i] == minFreq) minCount++;
        if (countArr[i] == maxFreq) maxCount++;
    }

    // Case 1: One character can be reduced to match minFreq
    if (maxFreq - minFreq == 1 && maxCount == 1) {
        return yes;
    }

    // Case 2: One character with freq=1 can be removed
    if (minFreq == 1 && minCount == 1 && maxFreq * maxCount == maxFreq * (n - 1)) {
        return yes;
    }

    return no;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();
    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) break;

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;

        alloc_length <<= 1;
        data = realloc(data, alloc_length);

        if (!data) return NULL;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);
        data[data_length] = '\0';
    }

    return data;
}
