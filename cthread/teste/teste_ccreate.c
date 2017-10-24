#include "../include/cthread.h"
#include <stdio.h>

void *teste(void *arg)
{
  printf("Thread 2 --  %d\n", *((int *)arg));
  return 0;
}

int main(int argc, char *argv[])
{
  ccreate(teste,NULL, 5);
  ccreate(teste,NULL, 5);
  ccreate(teste,NULL, 5);
  ccreate(teste,NULL, 5);
  return 0;
}
