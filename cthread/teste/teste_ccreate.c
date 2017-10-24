#include "../include/cthread.h"
#include <stdio.h>

void *teste(void *arg)
{
  printf("Thread 2 --  %d\n", *((int *)arg));
  return 0;
}

int main(int argc, char *argv[])
{
  argc = 10;
  int testando = ccreate(teste, (void *)&argc, 5);
  int testando2 = ccreate(teste, (void *)&argc, 5);
  printf("%d", testando);
  return 0;
}
