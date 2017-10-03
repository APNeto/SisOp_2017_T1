#define ERRO -1


int cidentify (char *name, int size){
  return ERRO;
}

int ccreate (void* (*start)(void*), void *arg, int prio) {
  return ERRO;
}

int cyield(void){
  return ERRO;
}
int cjoin(int tid){
  return ERRO;
}
int csem_init(csem_t *sem, int count){
  return ERRO;
}
int cwait(csem_t *sem){
  return ERRO;
}
int csignal(csem_t *sem){
  return ERRO;
}
