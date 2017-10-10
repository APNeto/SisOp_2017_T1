#define ERRO -1
#define SUCESSO 1

PFILA2 aptos;
PFILA2 bloqueados;
PFILA2 executando;
int numT = 0;

int cidentify (char *name, int size){
  return ERRO;T
}


int iniciaThreads(){
  CreateFila2(aptos);
  CreateFila2(bloqueados);
  CreateFila2(executando);
  
  TCB_t* tcbmain = (TCB_t*) malloc(sizeof(TCB_t));
  tcbmain->tid = numT++;
  tcbmaind->state = PROCST_EXEC;
  tcbmain->context.uc_link = NULL;
  tcbmain->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
  tcbmain->context.uc_stack.size = SIGSTKSZ;

  AppendFila2(executando, tcbmain);
  getcontext(&(tcbmain->context));
  
  return SUCESSO;
}

int ccreate (void* (*start)(void*), void *arg, int prio) {
  if(!FirstFila2(executando)) { //caso ainda nao tenha sido criada fila de executando, criar filas e iniciar thread main
    iniciaThreads();
  }

  // Cadastra nova thread de start
  TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
  tcb->tid = numT++;
  tcb->state = PROCST_EXEC;
  tcb->context.uc_link = NULL;
  tcb->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
  tcb->context.uc_stack.size = SIGSTKSZ;
  getcontext(&(tcb->context));

  AppendFila2(aptos, tcb);

  return tcb->tid;

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
