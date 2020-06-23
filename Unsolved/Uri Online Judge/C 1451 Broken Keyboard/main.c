#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node * next;
};

#ifndef NULL
    #define NULL 0
#endif

int main() {
    struct node * start = NULL;
    struct node * current = NULL;
    struct node * end = NULL;

    struct node * n;
    struct node * aux;
    struct node * next;
    int c = 0;

    while (c != EOF) {
        c = getchar();
        // printf("%c | ", c);
        if (((char) c) == '[') {
            if (start == NULL) {
                continue;
            }
            // printf("Going to the start of the array\n");
            current = NULL;
        } else if (((char) c) == ']') {
            if (start == NULL) {
                continue;
            }
            // printf("Going to the end of the array\n");
            current = end;
        } else if (((char) c) == '\n' || ((char) c) == '\r' || c == EOF) {
            // printf("List finished with%s", start != NULL ? ": " : " with nothing\n");
            aux = start;
            if (aux != NULL) {
                while (aux != NULL) {
                    putc(aux->value, stdout);
                    next = aux->next;
                    free(aux);
                    aux = next;
                }
                putc('\n', stdout);
            }
            start = NULL;
            current = NULL;
        } else if (current == NULL) {
            if (start == NULL) {
                // printf("Starting list with '%c'\n", (char) c);
                start = calloc(1, sizeof(struct node));
                start->value = c;
                start->next = NULL;
                current = start;
                end = start;
            } else {
                // printf("Writing to list start with '%c'\n", (char) c);
                current = calloc(1, sizeof(struct node));
                current->value = c;
                current->next = start;
                start = current;
            }
        } else if (current == end) {
            // printf("Appending '%c' to end of the list\n", (char) c);
            n = calloc(1, sizeof(struct node));
            n->value = c;
            n->next = NULL;
            current->next = n;
            end = n;
            current = n;
        } else {
            // printf("Adding letter '%c' before '%c'\n", (char) c, (char) current->next->value);
            n = calloc(1, sizeof(struct node));
            n->value = c;
            n->next = current->next;
            current->next = n;
            current = n;
        }
        if (c == EOF) {
            // printf("Finished\n");
            break;
        }
    };
