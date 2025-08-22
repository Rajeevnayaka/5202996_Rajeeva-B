#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct Stack {
    int data[MAX];
    int top;
} Stack;

void push(Stack* s, int val) {
    s->data[++(s->top)] = val;
}

int pop(Stack* s) {
    if (s->top == -1) return -1;
    return s->data[(s->top)--];
}

int peek(Stack* s) {
    if (s->top == -1) return -1;
    return s->data[s->top];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int main() {
    int q;
    scanf("%d", &q);

    Stack stack1 = {.top = -1};
    Stack stack2 = {.top = -1};

    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int x;
            scanf("%d", &x);
            push(&stack1, x);
        } else if (type == 2) {
            if (isEmpty(&stack2)) {
                while (!isEmpty(&stack1)) {
                    push(&stack2, pop(&stack1));
                }
            }
            pop(&stack2);
        } else if (type == 3) {
            if (isEmpty(&stack2)) {
                while (!isEmpty(&stack1)) {
                    push(&stack2, pop(&stack1));
                }
            }
            printf("%d\n", peek(&stack2));
        }
    }

    return 0;
}
