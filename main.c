#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define PAD 8
//#define ADDED 100
//#define ITERS 10000

//#define repeat(X) X; X;

#define KB 1024
#define MB 1024 * KB
#define SIZE 8 * MB
#define SPACE 101
#define STEPS 1000
//#define MAX_ITERS SIZE / SPACE

//typedef struct elem {
//    struct elem *next;
//    long pad[PAD];
//} elem;

//void add_to(elem *first, int num);

//elem *shuffle_loop(elem *first);

int main() {
//    clock_t time;

//    ==== OLD ====
//    elem *list = (elem*)malloc(sizeof(elem));
//    list->next = NULL;
//    =============

    srand(time(NULL));

    int i, j, k, l;
    int x, y;
    int temp;
//    int space = SPACE;
    int length;
//    int size = SIZE / sizeof(int);
//    int size = 2000000;
    int max_iters = SIZE / SPACE;
    char *arr = (char*)malloc(SIZE);
    int *access = (int*)malloc(SIZE);
//    int access[size];
    int step = max_iters / STEPS;
    char t;

//    for (i = 0; i < SIZE; ++i) {
//        arr[i] = 0; access[i] = 0;
//    }
    memset((void*)arr, 0, sizeof(arr));
    memset((void*)access, 0, sizeof(access));

    for (i = 1; i < max_iters; i += step) {
        length = i;

//        get positions to check
        for (j = 0; j < length; ++j) {
            access[j] = j * SPACE;
        }

//        shuffle them
//        for (x = 0; x < length - 1; x++) {
//            y = x + rand() / (RAND_MAX / (length - x) + 1);
//            temp = access[y];
//            access[y] = access[x];
//            access[x] = temp;
//        }
        for (j = 0; j < length / 4; j++) {
//            y = x + rand() / (RAND_MAX / (length - x) + 1);
            x = rand() % length;
            y = rand() % length;

            temp = access[x];
            access[x] = access[j];
            access[j] = temp;
        }

//        int steps = 64 * 1024 * 1024;
//        int lengthMod = (1024 * 1024) - 1;
//        int j;
        clock_t start;

        start = clock();
        for (k = 0; k < 512; ++k) {
            for (l = 0; l < SPACE; ++l) {
                for (j = 0; j < length; j++) {
                    t = arr[access[j] + l];
                }
            }
        }
        start = clock() - start;
        printf("%d %d %f\n", i, (int)start, (float)(length * SPACE * sizeof(int)) / KB);
//        free(arr);
    }

    free(arr);
    free(access);

//        int steps = 64 * 1024 * 1024;
//        int arr[1024 * 1024];
//        int lengthMod = (1024 * 1024) - 1;
//        int i;
//        double timeTaken;
//        clock_t start;
//
//        start = clock();
//        for (i = 0; i < steps; i++) {
//            arr[(i * 16) & lengthMod]++;
//        }
//        timeTaken = (double)(clock() - start)/CLOCKS_PER_SEC;
//        printf("Time for %d: %.12f \n", i, timeTaken);


//    ==== OLD ====

//    for (i = 0; i < ITERS; ++i) {
//        add_to(list, ADDED);
//        co += ADDED;
//        elem *tail = shuffle_loop(list);
//        elem *t = list;
//        elem t1;
////       (t = t->next))))))))))))))))))));
//        time = clock();
//        repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(t1 = *t; t = t->next))))))));
////        repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(t = t->next))))))))));
//        time = clock() - time;
//        printf("%d %d\n", (int)time, co);
//        tail->next = NULL;
//    }

//    ================


//    add_to(list, 9);
//    shuffle_loop(list);

//    int i = 0;
//    repeat(repeat(i++));

    return 0;
}

/*elem *shuffle_loop(elem *first) {

//    count length
    int length = 1;
    elem *temp = first;
    while (temp->next) {
        ++length;
        temp = temp->next;
    }

    elem **array = (elem**)malloc(sizeof(elem*) * length);
    int i;
    temp = first;
    for (i = 0; i < length; ++i) {
        array[i] = temp;
        temp = temp->next;
    }

    for (i = 0; i < length - 1; i++) {
        int j = i + rand() / (RAND_MAX / (length - i) + 1);
        elem *t = array[j];
        array[j] = array[i];
        array[i] = t;
    }

    temp = array[0];
    for (i = 0; i < length - 1; ++i) {
        temp->next = array[i + 1];
        temp = temp->next;
    }
    temp->next = array[0];

    free(array);

    return temp;
}

void add_to(elem *first, int num) {
//    find tail
    while (first->next) {
        first = first->next;
    }

    int i;
    for (i = 0; i < num; ++i) {
        elem *new_elem = (elem*)malloc(sizeof(elem));
        new_elem->next = NULL;
        first->next = new_elem;
        first = new_elem;
    }
}
*/