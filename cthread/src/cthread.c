#define ERRO -1
#define SUCESSO 1

PFILA2 aptos;
PFILA2 bloqueados;
PFILA2 executando;
PFILA2 esperando;
int numT = 0;

int cidentify (char *name, int size){
  return ERRO;T
}


/*
  TCB_t* check_tid_apto(int tid){

    TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
    if(!FisrtFila2(aptos)) ;
    
    do{
      tcb = GetAtIteratorFila2(aptos);
      if(tcb->tid == tid) return tcb;
    while( !(NextFila2(aptos)) );

    return NULL;
  }
*/

/*
  TCB_t* dispatcher(){
    
  }
*/
int iniciaThreads(){
  CreateFila2(aptos);
  CreateFila2(bloqueados);
  CreateFila2(executando);
  CreateFila2(esperando);
  
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
  tcb->context.uc_link = dispatcher;
  tcb->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
  tcb->context.uc_stack.size = SIGSTKSZ;
  tcb->prio = 0;
  getcontext(&(tcb->context));
  makecontext(&(tcb->context), (void(*)(void)) start, 1, arg);
  AppendFila2(aptos, tcb);

  return tcb->tid;

  return ERRO;
}

int cyield(void){
  TCB_t *thread = GetAtIteratorFila2(executando);
  thread->state = PROCST_APTO;

  //AppendFila2(aptos, thread);
  //dispatcher();

  return ERRO;
}
int cjoin(int tid){
  TCB_t *thread = (TCB_t*) GetAtIteratorFila2(executando);
  //check se tid em aptos ou em esperando
  //se em bloqueados, check se thread_de_tid está com join em thread

  //check se thread_de_tid ja eh esperada por outra thread
  //swapcontext(&(), &());
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
