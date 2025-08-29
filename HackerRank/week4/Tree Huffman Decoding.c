#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

// Node structure for Huffman tree
typedef struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
} Node;

// Min-heap structure
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    Node** array;
} MinHeap;

// Create a new node
Node* createNode(char data, unsigned freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Create a min-heap of given capacity
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));
    return minHeap;
}

// Swap two nodes
void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if size is 1
int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Extract minimum
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size-1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert node into min-heap
void insertMinHeap(MinHeap* minHeap, Node* node) {
    minHeap->size++;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i-1)/2]->freq) {
        minHeap->array[i] = minHeap->array[(i-1)/2];
        i = (i-1)/2;
    }
    minHeap->array[i] = node;
}

// Build min-heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n-1)/2; i >= 0; i--)
        minHeapify(minHeap, i);
}

// Create and build min-heap from character array and frequencies
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i=0; i<size; i++)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Build Huffman tree
Node* buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Print codes (used for debugging)
void printCodes(Node* root, int arr[], int top, char codes[256][MAX_TREE_HT]) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top+1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top+1, codes);
    }
    if (!root->left && !root->right) {
        for (int i=0; i<top; i++)
            codes[(unsigned char)root->data][i] = arr[i] + '0';
        codes[(unsigned char)root->data][top] = '\0';
    }
}

// Encode string using codes
void encode(char* str, char codes[256][MAX_TREE_HT], char* encoded) {
    encoded[0] = '\0';
    for (int i=0; str[i]; i++)
        strcat(encoded, codes[(unsigned char)str[i]]);
}

// Decode Huffman encoded string
void decode_huff(Node* root, char* s) {
    Node* current = root;
    for (int i=0; s[i]; i++) {
        if (s[i] == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

// Driver code
int main() {
    char str[1000];
    scanf("%s", str);

    // Count frequencies
    int freq[256] = {0};
    for (int i=0; str[i]; i++)
        freq[(unsigned char)str[i]]++;

    // Count unique characters
    char data[256];
    int f[256];
    int n = 0;
    for (int i=0; i<256; i++) {
        if (freq[i]) {
            data[n] = i;
            f[n] = freq[i];
            n++;
        }
    }

    Node* root = buildHuffmanTree(data, f, n);

    int arr[MAX_TREE_HT];
    char codes[256][MAX_TREE_HT] = {{0}};
    printCodes(root, arr, 0, codes);

    char encoded[10000];
    encode(str, codes, encoded);

    // Decode and print
    decode_huff(root, encoded);

    return 0;
}
