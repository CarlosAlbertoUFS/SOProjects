/*
Anotaçoes e adaptações disciplina SO  2016/1
compilar: gcc -pthread Trabalho02.c
executar: ./Trabalho02.c 12
12 é o parametro
*/


/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Solaris users must enter
 * gcc thrd.c -lpthreads
 *
 *
 *
 * Figure 4.6
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Seventh Edition
 * Copyright John Wiley & Sons - 2005.
 */
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

  struct remedio {
    char* nome;
    int doses;
  };
  /*mutex*/
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  /* Semaforo  */
  sem_t semaforo;
 int main()
 {
   //guarda o menor multiplo comum
   int mmc = 0;

   int nth_value = 40;

   struct params{
     int value;
   };


   void* mmc_function(void* params_thread){
      struct params* data = (struct params*)params_thread;
      int a = pthread_self();

     printf("Multiplos de %d \n",data->value);
     int i;
     for(i = 1; i < nth_value; i++){
       if(!(i%data->value)){

         /*Aqui queremos evitar que outras threads acessem o mmc durante esta execução*/
         pthread_mutex_lock (&mutex);
         if(mmc == 0){
            mmc = i;
         }else{
           /*testa se o valor que está no mmc é um mútiplo seu*/
           if(!(mmc%data->value)){
                //if(sem_trywait(&semaforo) == EAGAIN){
             sem_wait(&semaforo);
                 // printf("Erro %d\n",sem_trywait(&semaforo));
                //};
           }
         }
         pthread_mutex_unlock (&mutex);
         /*libera a variavel mmc*/

          printf(" %d,",i);
       }
     }
      printf("\n");
      //printf("Thread %d \n Multiple: %d \n",a,data->value);
   }

   struct params parametro1;
   parametro1.value = 3;

   struct params parametro2;
   parametro2.value = 5;

   struct params parametro3;
   parametro3.value = 7;

   pthread_t thread_id1;
   pthread_t thread_id2;

   /*inicializando o semaforo*/
   sem_init(&semaforo,0,0);

   pthread_create (&thread_id2, NULL, &mmc_function, &parametro2);
   pthread_create (&thread_id1, NULL, &mmc_function, &parametro2);


   pthread_join (thread_id1, NULL);
   pthread_join (thread_id2, NULL);

   printf("MMC: %d \n",mmc);
   sem_destroy(&semaforo);
  return 0;
 }