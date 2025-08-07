#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char s[10001], t[10001];
    scanf("%s", s);
    scanf("%s", t);

    int len = strlen(s);
    char res[10001];

    for (int i = 0; i < len; i++) {
        // Changed XOR logic to use bitwise XOR
        res[i] = ((s[i] - '0') ^ (t[i] - '0')) + '0';
    }
    res[len] = '\0';

    printf("%s\n", res);


    return 0;
}
