#include <stdio.h>
#include <stdlib.h>

void findZigZagSequence(int arr[], int n) {
    // Step 1: sort array
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // FIX #1
    int mid = (n + 1)/2 - 1;   // instead of n/2

    // FIX #2
    int temp = arr[mid];
    arr[mid] = arr[n - 1];     // swap with last element
    arr[n - 1] = temp;

    // FIX #3
    int st = mid + 1;
    int ed = n - 2;            // not n-1
    while (st <= ed) {
        temp = arr[st];
        arr[st] = arr[ed];
        arr[ed] = temp;
        st++;
        ed--;
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        findZigZagSequence(arr, n);
    }
    return 0;
}
