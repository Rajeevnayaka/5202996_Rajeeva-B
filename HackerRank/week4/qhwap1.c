#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int heap[MAX];
int size = 0;

// Swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up (after insert)
void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] > heap[index]) {
            swap(&heap[parent], &heap[index]);
            index = parent;
        } else break;
    }
}

// Heapify down (after delete)
void heapifyDown(int index) {
    while (2 * index + 1 < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;
        if (smallest != index) {
            swap(&heap[index], &heap[smallest]);
            index = smallest;
        } else break;
    }
}

// Insert element into heap
void insert(int value) {
    heap[size++] = value;
    heapifyUp(size - 1);
}

// Delete a specific element from heap
void delete(int value) {
    int i;
    for (i = 0; i < size; i++) {
        if (heap[i] == value) break;
    }
    if (i == size) return; // not found (though input guarantees it exists)
    heap[i] = heap[size - 1];
    size--;
    heapifyDown(i);
    heapifyUp(i);
}

// Get minimum element
int getMin() {
    return heap[0];
}

int main() {
    int Q;
    scanf("%d", &Q);

    for (int i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int x;
            scanf("%d", &x);
            insert(x);
        } else if (type == 2) {
            int x;
            scanf("%d", &x);
            delete(x);
        } else if (type == 3) {
            printf("%d\n", getMin());
        }
    }

    return 0;
}
