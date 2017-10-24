
#include "../include/support.h"
#include "../include/cdata.h"
#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "./insert.c"
#define ERRO -1
#define SUCESSO 0

FILA2 aptos;
FILA2 bloqueados;
FILA2 esperando; // espera recurso
FILA2 terminado;
TCB_t *thread_executando;

int numT = 1;
int filascriadas = 0;
ucontext_t escalonador;
TCB_t thread_main;
clock_t inicialT;

void dispatcher(){
  TCB_t *prox = (TCB_t *) GetAtIteratorFila2(&aptos);
  prox->state = PROCST_EXEC;

  DeleteAtIteratorFila2(&aptos);
  thread_executando = prox;
  //AppendFila2(&executando, prox);

  printf("Passando os recursos para a thread %d \n", thread_executando->tid);
  time(inicialT);
  setcontext(&(prox->context));
  return;
}

void escalonadorupdate()
{
  printf("escalonador iniciando os trabalhos\n");
  //TCB_t *thread_executando = (TCB_t *) GetAtIteratorFila2(&executando);
  if (thread_executando != NULL)
  {
    if(thread_executando->state == PROCST_TERMINO){ //libera recursos da thread
      free(thread_executando);
    }
    else{//coloca thread em aptos
      InsertByPrio(&aptos, thread_executando);
    }
    //DeleteAtIteratorFila2(&executando);
    thread_executando = NULL;    
    printf("escalonador liberando os recursos\n");
    //AppendFila2(terminado, thread_executando);
  }

  return dispatcher();

  // n vai acontecer, deve ao menos ter main
  if (FirstFila2(&aptos) != 0)
  {
    printf("A fila de aptos está vazia\n"); 
    return;
  }
  // if(thread_executando = NULL){
  //	thread_executando = &thread_main;
  //}
}

int cidentify(char *name, int size)
{
  printf("Alberto Pena Neto - 217444\nIago Martins - 240499\nMateus Heck - 206740");
  return SUCESSO;
}

char ss_sp_escalonador[SIGSTKSZ];

void init_escalonador()
{
  getcontext(&escalonador);
  escalonador.uc_link = &(thread_main.context);
  escalonador.uc_stack.ss_sp = ss_sp_escalonador;
  escalonador.uc_stack.ss_size = SIGSTKSZ;
  makecontext(&escalonador, (void (*)(void))escalonadorupdate, 0);
}

void CriaFilas()
{
  printf("Criando fila Aptos\n");
  CreateFila2(&aptos);
  printf("Criando fila bloqueados\n");
  CreateFila2(&bloqueados);
  printf("Criando fila esperando\n");
  CreateFila2(&esperando);
  printf("Criando fila terminado\n");
  CreateFila2(&terminado);
  filascriadas = 1;
}

void Create_Main_Thread()
{
  thread_main.tid = 0;
  thread_main.state = PROCST_EXEC;
  getcontext(&(thread_main.context));
  thread_executando = &thread_main;
}

void InicializaVariavies()
{
  printf("Criando Filas\n");
  CriaFilas();
  printf("Criando escalonador\n");
  init_escalonador();
  printf("Criando Main Thread\n");
  Create_Main_Thread();
}

TCB_t *check_tid_apto(int tid)
{
  TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
  if (!FirstFila2(&aptos))
  {
    do
    {
      tcb = GetAtIteratorFila2(&aptos);
      if (tcb->tid == tid)
        return tcb;
    } while (!(NextFila2(&aptos)));
  }
  return NULL;
}

TCB_t *check_tid_esperando(int tid)
{
  TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
  if (!FirstFila2(&esperando))
  {
    do
    {
      tcb = GetAtIteratorFila2(&esperando);
      if (tcb->tid == tid)
        return tcb;
    } while (!(NextFila2(&esperando)));
  }
  return NULL;
}

TCB_t *check_tid_bloqueados(int tid)
{
  TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
  if (!FirstFila2(&bloqueados))
  {
    do
    {
      tcb = GetAtIteratorFila2(&bloqueados);
      if (tcb->tid == tid)
        return tcb;
    } while (!(NextFila2(&bloqueados)));
  }
  return NULL;
}

void finalizador()
{
  // se ha alguma thread esperando esta que termina, libera a thread para aptos
  //acha ponteiro na fila de bloqueados
  //deleta ponteiro na fila de bloqueados
  //coloca thread em aptos
  TCB_t *exec = thread_executando;
  if(exec->bloqueando){
    FirstFila2(&bloqueados);
    do
    {
      TCB_t *tcb = GetAtIteratorFila2(&bloqueados);
      if (tcb->tid == exec->bloqueando->tid){
        DeleteAtIteratorFila2(&bloqueados);
        InsertByPrio(&aptos, tcb);
        tcb->state = PROCST_APTO;
        break;
      }
    } while (!(NextFila2(&bloqueados)));
    exec->state = PROCST_TERMINO;
    
    setcontext(&(escalonador));
  }
}

int make_join(TCB_t *thread, TCB_t *tidThread)
{
  if (tidThread->bloqueando) //check se thread_de_tid ja eh esperada por outra thread
    return ERRO;

  clock_t termino;
  thread->prio += difftime(termino, inicialT);
  tidThread->bloqueando = thread;
  thread->state = PROCST_BLOQ;
  thread_executando = NULL;
  //DeleteAtIteratorFila2(&executando);
  AppendFila2(&bloqueados, thread);
  swapcontext(&thread->context, &escalonador);
  return SUCESSO;
}

///*************************************** Funcoes ******************************
int ccreate(void *(*start)(void *), void *arg, int prio)
{
  printf("Iniciando teste ccreate...\n");
  // Crias as listas e a thread de start
  if (!filascriadas)
  {
    InicializaVariavies();
  }
  //******************** Cria uma nova thread
  TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
  tcb->tid = numT++;
  tcb->state = PROCST_APTO;
  getcontext(&(tcb->context));
  tcb->context.uc_link = &escalonador;
  ///char stack_tcb[SIGSTKSZ];
  ///tcb->context.uc_stack.ss_sp = stack_tcb;
  tcb->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
  tcb->context.uc_stack.ss_size = SIGSTKSZ;
  tcb->prio = 0;
  tcb->bloqueando = NULL;
  makecontext(&(tcb->context), (void (*)(void))start, 1, arg);

  // insere na fila de aptos de acordo com tempo prio transcorrido durante ultima exec
  // thread criada agora: prio = 0
  InsertByPrio(&aptos, tcb);
  ///AppendFila2(aptos, tcb);
  printf("Thread criada, tid %d \n", tcb->tid);
  return tcb->tid;
}

int cyield(void)
{
  printf("Iniciando yield \n");
  clock_t termino;
  time(&termino);
  TCB_t *thread = thread_executando;
  thread->prio += difftime(termino, inicialT);
  thread->state = PROCST_APTO;
  thread_executando = NULL;
  printf("Thread %d liberou a cpu\n", thread->tid);
  //escalonador();
  swapcontext(&thread->context, &escalonador);
  return SUCESSO;
}

int cjoin(int tid)
{
  if (tid > numT) return ERRO; // numero tid com certeza esta errado pois n houve thread com este tid
  TCB_t *thread = thread_executando; //(TCB_t *)GetAtIteratorFila2(&executando);

  TCB_t *tidThread = check_tid_apto(tid);
  //check se tid em aptos
  if (tidThread)
  {
    return make_join(thread, tidThread);
  }

  //check se tid em esperando
  tidThread = check_tid_esperando(tid);
  if (tidThread)
  {
    return make_join(thread, tidThread);
  }

  //se em bloqueados
  tidThread = check_tid_bloqueados(tid);
  if (tidThread)
  {
    //check se thread_de_tid está com join em thread (deadlock) -> transformar em função recursiva
    if (thread->bloqueando)
      if (tid == thread->bloqueando->tid)
        return ERRO;
    
    return make_join(thread, tidThread);
  }
  //caso nao encontre tid, a thread ja finalizou
  return ERRO;
}

//csem_t semaforos;
int csem_init(csem_t *sem, int count)
{
  sem = (csem_t *)malloc(sizeof(csem_t));
  sem->count = 1;
  CreateFila2(sem->fila);
  if (sem->fila)
    return SUCESSO;
  return ERRO; //caso fila nao tenha sido alocada corretamente
}

int cwait(csem_t *sem)
{
  if (sem->fila == NULL)
    return ERRO; // sem n foi inicializado
  if (sem->count > 0)
  {
    sem->count--;
  }
  else
  { // semaforo ocupado
    clock_t termino;
    time(&termino);
    TCB_t *thread = thread_executando; //GetAtIteratorFila2(&executando);
    thread->prio += difftime(termino, inicialT);
    AppendFila2(sem->fila, thread);
    thread->state = PROCST_BLOQ;
    thread_executando = NULL;
    //DeleteAtIteratorFila2(&executando);
    AppendFila2(&esperando, thread);
    escalonadorupdate();
  }
  return SUCESSO;
}

int csignal(csem_t *sem)
{
  if (sem->fila == NULL)
    return ERRO;
  if (FirstFila2(sem->fila) == 0)
  { // fila nao vazia
    TCB_t *thread = GetAtIteratorFila2(sem->fila)
    DeleteAtIteratorFila2(sem->fila);
    InsertByPrio(&aptos, thread);
    thread->state = PROCST_APTO;
  }
  else
  { //fila vazia, apenas incrementa o contador de volta para 1
    sem->count++;
  }
  return SUCESSO;
}
