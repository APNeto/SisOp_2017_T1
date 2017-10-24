#include <stdio.h>
#include "../include/cthread.h"
//#define _XOPEN_SOURCE 600
//#define THREAD_COUNT 20 

void* func3(void *arg);
void* func1(void *arg);
void* func2(void *arg);

void* func3(void *arg) {
    printf("iniciando thread 3\n");
    printf("fim da thread 3\n");
    return 0;
}

void* func1(void *arg) {
    printf("iniciando thread 1\n");
    int id2 = ccreate(func2, NULL,1);
    cjoin(id2);
    printf("fim da thread 1\n");
    return 0;
}

void* func2(void *arg) {
    printf("iniciando thread 2\n");
    int id3 = ccreate(func3, NULL,1);
    cjoin(id3);
    printf("fim da thread 2\n");
    return 0;
}

int main(int argc, char *argv[]) {
    int id1 = ccreate(func1, NULL,1);
    cjoin(id1);
    printf("Main terminou.\n");    
    return 0;
}
