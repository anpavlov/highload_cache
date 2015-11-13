#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAD 1
#define ADDED 100
#define ITERS 100

#define repeat(X) X; X;

#define KB 1024
#define MB 1024 * KB
#define SIZE 0x1000000
#define SPACE 101
#define STEPS 1000
//#define MAX_ITERS SIZE / SPACE

typedef struct elem {
    struct elem *next;
    int pad[2];
} elem;

//void add_to(elem *first, int num);
elem *shuffle_loop(elem *first);
elem *generate_list(int amt);
void free_list(elem *first);

volatile char arr[SIZE];
int access[0xFFFFFF];

int main() {


    srand(time(NULL));

//    ==== OLD ====
//    elem *list = (elem*)malloc(sizeof(elem));
//    list->next = NULL;
//    =============


//    ==== OLD ====

    int max = 8 * 1024 * 1024 / sizeof(elem);

    clock_t measured;
    int i, count = 100;
    for (count = 10; count < max;) {

        if ((int)(count * sizeof(elem)) > 1024 * 1024) {
            count += count/10;
        } else if ((int)(count * sizeof(elem)) < 100 * 1024) {
            count += 10;
        } else {
            count += 1000;
        }

        elem *first_elem = generate_list(count);
//        add_to(list, ADDED);

        elem *tail = shuffle_loop(first_elem);
        volatile elem *t = first_elem;
        volatile elem t1;
//       (t = t->next))))))))))))))))))));

        int j, k;
        measured = clock();
        for (k = 0; k < 50; ++k) {
//            for (j = 0; j < count / 100; ++j) {
                repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(t1 = *t;
                               t = t->next))))))))));
//            }
        }
//        repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(t = t->next))))))))));
        measured = clock() - measured;
        printf("%d %d\n", (int) measured, (int)(count * 8));
        tail->next = NULL;
        free_list(first_elem);

    }

//    ================


//    add_to(list, 9);
//    shuffle_loop(list);

//    int i = 0;
//    repeat(repeat(i++));

    return 0;
}

elem *shuffle_loop(elem *first) {

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

    for (i = 0; i < length / 2; i++) {
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

//void add_to(elem *first, int num) {
////    find tail
//    while (first->next) {
//        first = first->next;
//    }
//
//    int i;
//    for (i = 0; i < num; ++i) {
//        elem *new_elem = (elem*)malloc(sizeof(elem));
//        new_elem->next = NULL;
//        first->next = new_elem;
//        first = new_elem;
//    }
//}

elem *generate_list(int amt) {
    elem *list = (elem*)malloc(sizeof(elem));
    elem *first_elem = list;
    int i;
    for (i = 0; i < amt - 1; ++i) {
        elem *new_elem = (elem*)malloc(sizeof(elem));
        new_elem->pad[0] = rand();
        new_elem->pad[1] = rand();
        list->next = new_elem;
        list = new_elem;
    }
    list->next = NULL;
    return first_elem;
}

void free_list(elem *first) {

    elem *temp = first;
    elem *temp1;
    while (temp->next) {
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    free(temp);
}