#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int priority;
    char *data;
} node_t;

typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;

void push (heap_t *h, int priority, char *data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = realloc(h->nodes, h->size * sizeof (node_t));
    }
    // upheap
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}

int min (heap_t *h, int a, int b, int c) {
    int m = a;
    if (b <= h->len && h->nodes[b].priority < h->nodes[m].priority) {
        m = b;
    }
    if (c <= h->len && h->nodes[c].priority < h->nodes[m].priority) {
        m = c;
    }
    return m;
}

char *pop (heap_t *h) {
    int i, j;
    if (!h->len) {
        return NULL;
    }
    // downheap
    char *data = h->nodes[1].data;
    h->nodes[1] = h->nodes[h->len];
    h->len--;
    i = 1;
    while (1) {
        j = min(h, i, 2 * i, 2 * i + 1);
        if (j == i) {
            break;
        }
        h->nodes[i] = h->nodes[j];
        i = j;
    }
    h->nodes[i] = h->nodes[h->len + 1];
    return data;
}

int main () {
    heap_t *h = calloc(1, sizeof (heap_t));
    push(h, 3, "Clear drains");
    push(h, 4, "Feed cat");
    push(h, 5, "Make tea");
    push(h, 1, "Solve RC tasks");
    push(h, 2, "Tax return");
    int i;
    for (i = 0; i < 5; i++) {
        printf("%s\n", pop(h));
    }
    return 0;
}

