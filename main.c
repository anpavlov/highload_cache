#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define repeat(X) X; X;

#define KB 1024
#define MB 1024 * KB

typedef struct elem {
    struct elem *next;
    int a;
} elem;

//void add_to(elem *first, int num);
elem *shuffle_loop(elem *first);
elem *normal_loop(elem *first);
elem *generate_list(int amt);
void free_list(elem *first);

int main() {
    
    srand(time(NULL));
    
    int max = 256 * MB / sizeof(elem);
    
    clock_t measured;
    int count = 0;
    for (count = 1; count < max;) {
        
        elem *first_elem = generate_list(count);
//        elem *tail = shuffle_loop(first_elem);
        elem *tail = normal_loop(first_elem);
        
        volatile elem *t = first_elem;
        
        int k;
        measured = clock();
        for (k = 0; k < 5000; ++k) {
            repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(repeat(t = t->next))))))))));
        }
        
        measured = clock() - measured;
        
        printf("%d;%d\n", (int)(((float)measured) * 1000000000 / CLOCKS_PER_SEC)/(5000 * 1024), (int)(count * sizeof(elem)));
        
        tail->next = NULL;
        free_list(first_elem);
        
        if (count * sizeof(elem) > 32000 && count * sizeof(elem) < 256000){
            count += 1280;
        } else {
            count *= 2;
        }
        
    }
    
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

elem *normal_loop(elem *first){
    elem* temp;
    temp = first;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = first;
    return temp;
}

elem *generate_list(int amt) {
    elem *list = (elem*)malloc(sizeof(elem));
    elem *first_elem = list;
    int i;
    for (i = 0; i < amt - 1; ++i) {
        elem *new_elem = (elem*)malloc(sizeof(elem));
        new_elem->a = rand();
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