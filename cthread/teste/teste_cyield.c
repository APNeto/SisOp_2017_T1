
#include <stdio.h>
#include "../include/cthread.h"

void* func3(void *arg);
void* func1(void *arg);
void* func2(void *arg);

void* func3(void *arg) {
    printf("thread 3 iniciando\n");
    printf("yield thread 3\n");
    cyield();
    printf("thread 3 finalizada\n");
    return;
}

void* func1(void *arg) {
    printf("thread 1 iniciando\n");
    ccreate(func2, NULL,1);
    printf("thread 2 foi criada pela thread 1 e vai dar yield.\n");
    cyield();
    printf("thread 1 finalizada\n");
    return;
}

void* func2(void *arg) {
    printf("thread 2 iniciando\n");
    ccreate(func3, NULL,1);
    printf("thread 3 foi criada pela thread 2 e vai dar yield.\n");
    cyield();
    printf("thread 2 finalizada\n");
    return;
}

int main(int argc, char *argv[]) {
    ccreate(func1, NULL,1);
    printf("Main criou Thread 1 e vai dar yield.\n");
    cyield();
   
    printf("Main recebeu o processador e vai dar yield.\n");
    cyield();
    

    printf("Main recebeu o processador e vai dar yield.\n");
    cyield();
    
    printf("Main recebeu o processador e vai dar yield.\n");
    cyield();

    printf("Main chegou ao fim.\n");    
    return 0;
}
