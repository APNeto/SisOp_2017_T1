
#include "../include/support.h"
#include "../include/cdata.h"
#include <stdlib.h>
#define ERRO -1
#define SUCESSO 1



PFILA2 aptos;
PFILA2 bloqueados;
PFILA2 executando;
PFILA2 esperando;
int numT = 1;
int filascriadas = 0;
ucontext_t escalonador;
TCB_t thread_main;


int cidentify (char *name, int size){
  return ERRO;
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

void CriaFilas(){
  CreateFila2(aptos);
  CreateFila2(bloqueados);
  CreateFila2(executando);
  CreateFila2(esperando);
  filascriadas = 1;
}

void Create_Main_Thread()
{
    thread_main.tid = 0;
    thread_main.state = PROCST_EXEC;
    getcontext(&thread_main.context);
}

void InicializaVariavies()
{
    Create_Main_Thread();
    CriaFilas();
}

TCB_t* check_tid_apto(int tid){
    TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
    if(!FisrtFila2(aptos)) ;
    
    do{
      tcb = GetAtIteratorFila2(aptos);
      if(tcb->tid == tid) return tcb;
    while( !(NextFila2(aptos)) );

    return NULL;
}

TCB_t* check_tid_esperando(int tid){
    TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
    if(!FisrtFila2(esperando)) ;
    
    do{
      tcb = GetAtIteratorFila2(esperando);
      if(tcb->tid == tid) return tcb;
    while( !(NextFila2(esperando)) );

    return NULL;
}

TCB_t* check_tid_bloqueados(int tid){
    TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
    if(!FisrtFila2(bloqueados)) ;
    
    do{
      tcb = GetAtIteratorFila2(bloqueados);
      if(tcb->tid == tid) return tcb;
    while( !(NextFila2(bloqueados)) );

    return NULL;
}

//int iniciaThreads(){
//  CreateFila2(aptos);
//  CreateFila2(bloqueados);
//  CreateFila2(executando);
//  CreateFila2(esperando);

//  TCB_t* tcbmain = (TCB_t*) malloc(sizeof(TCB_t));
//  tcbmain->tid = numT++;
//  tcbmaind->state = PROCST_EXEC;
//  tcbmain->context.uc_link = NULL;
//  tcbmain->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
//  tcbmain->context.uc_stack.size = SIGSTKSZ;

//  AppendFila2(executando, tcbmain);
//  getcontext(&(tcbmain->context));
//  TCB_t
//  return SUCESSO;
//}

int ccreate (void* (*start)(void*), void *arg, int prio) {

  // Crias as listas e a thread de start
  if(!filascriadas){
	InicializaVariavies();
	}

  // Cria uma nova thread
  TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
  tcb->tid = numT++;
  tcb->state = PROCST_APTO;
  tcb->context.uc_link = &escalonador;
  tcb->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
  tcb->context.uc_stack.ss_size = SIGSTKSZ;
  tcb->prio = 0;
  getcontext(&(tcb->context));
  makecontext(&(tcb->context), (void(*)(void)) start, 1, arg);
  AppendFila2(aptos, tcb);
  return tcb->tid;
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
  
  //check se thread_de_tid ja eh esperada por outra thread
  if(check_tid_bloqueados(executando->tid)) return ERRO;


  TCB_t *tidThread = check_tid_apto(tid);
  //check se tid em aptos
  if(tidThread){
    executando->bloqueando = tidThread;
    executando->state = PROCST_BLOQ;
    //
  }
  
  //check se tid em esperando
  tidThread = = check_tid_esperando(tid);
  if(tidThread){}

  //se em bloqueados, check se thread_de_tid está com join em thread
  TCB_t *tidThread = check_tid_bloqueados(tid);
  if(tidThread){
    if(tidThread->bloqueando->tid == executando->tid) return ERRO;
  }
  return ERRO;
}

//int csem_init(csem_t *sem, int count){
//  return ERRO;
//}
//int cwait(csem_t *sem){
//  return ERRO;
//}
//int csignal(csem_t *sem){
//  return ERRO;
//}
