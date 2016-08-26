#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cstring>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#define NPAD_SEQ 0
#define NPAD_RND 31

// NPAD configuration
#define NPAD NPAD_RND
#define NON_RANDOM 0
#define RANDOM 1

// macros
#define JMP1 cursor = cursor->next;
#define JMP2 JMP1 JMP1
#define JMP4 JMP2 JMP2
#define JMP8 JMP4 JMP4
#define JMP16 JMP8 JMP8
#define JMP32 JMP16 JMP16
#define JMP64 JMP32 JMP32
#define JMP128 JMP64 JMP64
#define JMP256 JMP128 JMP128
#define JMP512 JMP256 JMP256
#define JMP1024 JMP512 JMP512
#define JMP2048 JMP1024 JMP1024
#define JMP4096 JMP2048 JMP2048
#define JMP8192 JMP4096 JMP4096
#define JMP16384 JMP8192 JMP8192
#define JMP32768 JMP16384 JMP16384
#define JMP32768 JMP16384 JMP16384
#define JMP65536 JMP32768 JMP32768
#define JMP131072 JMP65536 JMP65536
#define JMP262144 JMP131072 JMP131072
#define JMP524288 JMP262144 JMP262144
#define JMP1048576 JMP524288 JMP524288
#define JMP2097152 JMP1048576 JMP1048576

struct node {
    long int pad[NPAD];
    struct node *next;
};

struct arr {
    int flag;
    struct node *ptr;
};

const int START_SIZE = 64;
const int END_SIZE  = 650000;
const int steps = 10000;

uint64_t measure( int size, int random);
void mix_nodes(struct node* first, int size);
uint64_t rdtsc(void);

int main () {
    srand(time(NULL));

    if ( NPAD == NPAD_SEQ ) { //
        printf("Sequential Read Access\n");
        for (int i = START_SIZE; i< END_SIZE; i *= 1.5)
            measure(i, NON_RANDOM);
    } else
    if ( NPAD == NPAD_RND ) {
        printf("Random Read Access\n");
        for (int i = START_SIZE; i< END_SIZE; i *= 1.5)
            measure(i, RANDOM);
    }
}

uint64_t measure( int size, int random) {
    int i;
    struct node *first, *cursor = 0;

    for (i = 0; i<size; i++) {
        struct node *new_node = (node*) malloc( sizeof(struct node) );
        if (cursor) {
            cursor->next = new_node;
        } else {
            first = new_node;
        }
        cursor = new_node;
    }
    cursor->next = first;

    if (random) mix_nodes(first, size);

    uint64_t started, finished, result;
    result = 0;

    for ( int step = 0; step < steps; step++) {
        cursor = first;
        started = rdtsc();   // start clock

        JMP131072

        finished = rdtsc();  // finish clock
        result = finished - started;
    }

    result /= 131072;
    // result /= steps;

    printf("%lu:", size * sizeof(struct node) / 1024 );
    printf("%" PRIu64 "\n", result);
    return result;
}

// mix nodes
void mix_nodes(struct node* first, int size)
{
    struct node *cursor = first;
    struct arr arr[size];
    int i, r;

    for ( int i = 0; i< size; i++) {
        arr[i].flag = 1;
        arr[i].ptr = cursor;
        cursor = cursor->next;
    }

    cursor = first;
    for (i = 1; i< size; i++) {
        find_addr:
        r = rand() % size;
        if ( r != 0 && arr[r].flag == 1) {
            cursor->next = arr[r].ptr;
            arr[r].flag = 0;
            cursor = cursor->next;
        } else {
            goto find_addr;
        }
    }
    cursor->next = first;
}

uint64_t rdtsc()
{
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ( ((uint64_t)hi) << (uint32_t)32 )
           | ( ((uint64_t)lo) );
}