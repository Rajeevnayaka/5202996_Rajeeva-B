#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int isLeap(int year) {
    if(year % 400 == 0) return 1;
    if(year % 100 == 0) return 0;
    if(year % 4 == 0) return 1;
    return 0;
}

int storeDate(int d, int m, int y) {
    int val = d;
    val = val * 100 + m;
    val = val * 10000 + y;
    return val;
}

int findPrimeDates(char *d1, char *d2) {
    int d, m, y;
    int dEnd, mEnd, yEnd;
    int count = 0;

    sscanf(d1, "%d-%d-%d", &d, &m, &y);
    sscanf(d2, "%d-%d-%d", &dEnd, &mEnd, &yEnd);

    while(1) {
        int num = storeDate(d, m, y);
        if(num % 4 == 0 || num % 7 == 0) {
            count++;
        }

        if(d == dEnd && m == mEnd && y == yEnd) break;

        d++;
        if(m == 2 && isLeap(y)) {
            if(d > 29) { d = 1; m++; }
        } else {
            if(d > monthDays[m-1]) { d = 1; m++; }
        }

        if(m > 12) { m = 1; y++; }
    }
    return count;
}

int main() {
    char date1[11], date2[11];
    scanf("%s %s", date1, date2);
    printf("%d", findPrimeDates(date1, date2));
    return 0;
}
