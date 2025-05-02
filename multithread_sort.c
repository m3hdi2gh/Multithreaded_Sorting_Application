#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM 10
#define HALF (NUM / 2)

// global arrays
int unsorted[NUM];
int final_sorted[NUM];

// structs passed to threads
typedef struct {
    int   *start;
    size_t len;
} SortArgs;

typedef struct {
    int   *left;  size_t n_left;
    int   *right; size_t n_right;
    int   *dest;
} MergeArgs;

// insertion sort
static void insertion_sort(int *a, size_t n)
{
    for (size_t i = 1; i < n; ++i) {
        int key = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > key) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = key;
    }
}

// thread functions
static void *sorter(void *arg)
{
    SortArgs *s = (SortArgs *)arg;
    insertion_sort(s->start, s->len);
    return NULL;
}

static void *merger(void *arg)
{
    MergeArgs *m = (MergeArgs *)arg;

    size_t i = 0, j = 0, k = 0;
    while (i < m->n_left && j < m->n_right) {
        if (m->left[i] <= m->right[j])
            m->dest[k++] = m->left[i++];
        else
            m->dest[k++] = m->right[j++];
    }
    while (i < m->n_left)  m->dest[k++] = m->left[i++];
    while (j < m->n_right) m->dest[k++] = m->right[j++];
    return NULL;
}

int main(void)
{
    puts("Enter 10 integers:");
    for (size_t i = 0; i < NUM; ++i)
        scanf("%d", &unsorted[i]);

    // prepare arguments for sorter threads
    SortArgs left_half  = { .start = &unsorted[0],    .len = HALF };
    SortArgs right_half = { .start = &unsorted[HALF], .len = HALF };

    pthread_t tid_left, tid_right;
    pthread_create(&tid_left,  NULL, sorter, &left_half);
    pthread_create(&tid_right, NULL, sorter, &right_half);

    pthread_join(tid_left, NULL);
    pthread_join(tid_right, NULL);

    // merge the two in place sorted halves
    MergeArgs m = {
        .left   = &unsorted[0],    .n_left  = HALF,
        .right  = &unsorted[HALF], .n_right = HALF,
        .dest   = final_sorted
    };

    pthread_t tid_merge;
    pthread_create(&tid_merge, NULL, merger, &m);
    pthread_join(tid_merge, NULL);

    puts("\nSorted result:");
    for (size_t i = 0; i < NUM; ++i)
        printf("%d ", final_sorted[i]);
    putchar('\n');
    return 0;
}
