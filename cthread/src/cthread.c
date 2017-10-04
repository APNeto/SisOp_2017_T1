#define ERRO -1

PFILA2 aptos;
PFILA2 bloqueados;
PFILA2 executando;

int cidentify (char *name, int size){
  return ERRO;
}


int iniciaThreads(){
  CreateFila2(aptos);
  CreateFila2(bloqueados);
  CreateFila2(executando);
  
  TCB_t* tcbmain = (TCB_t*) malloc(sizeof(TCB_t));
  tcbmain.tid = 0;
  tcbmaind.state = PROCST_EXEC;
  //tcbmain.context
  
  return ERRO;
}

int ccreate (void* (*start)(void*), void *arg, int prio) {
  if(!FirstFila2(executando)) { //caso ainda nao tenha sido criada fila de executando, criar filas e iniciar thread main
    iniciaThreads();
  } 
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
