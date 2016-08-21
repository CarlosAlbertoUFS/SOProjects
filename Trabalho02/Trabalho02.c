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
  /*Semaforo*/
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
          printf("Validou\n");
         if(mmc == 0){
            mmc = i;
            printf("esperando por ser o primeiro\n");
            pthread_mutex_unlock (&mutex);
            sem_wait(&semaforo);
         }else{
           printf("mmc já possui dados\n");
           /*testa se o valor que está no mmc é um mútiplo seu*/
           if(mmc == i){
                printf("Finalizar\n");
                pthread_mutex_unlock (&mutex);
             return NULL;
            }else if(mmc < i){
                       printf("esperando\n");
                       mmc = i;
                       pthread_mutex_unlock (&mutex);
                       sem_wait(&semaforo);
                    }else{
                        printf("continue\n");

                    }
            printf("saiu dos ifs \n");
         }
         printf(" mmc : %d \n",mmc);
         pthread_mutex_unlock (&mutex);
         /*libera a variavel mmc*/
         int id = pthread_self();
         printf(" Thread id %d \n",id);
         printf(" m : %d \n",i);

         //printf(" passou do semaforo ");
       }
     }
      printf("\n");
      /*printf("Thread %d \n Multiple: %d \n",a,data->value);*/
   }

   struct params parametro1;
   parametro1.value = 3;

   struct params parametro2;
   parametro2.value = 5;

   struct params parametro3;
   parametro3.value = 7;

   /*Iniciando o Semaforo*/
   sem_init(&semaforo,0,0);

   pthread_t thread_id1;
   pthread_t thread_id2;

   pthread_create (&thread_id2, NULL, &mmc_function, &parametro1);
   pthread_create (&thread_id1, NULL, &mmc_function, &parametro2);

   pthread_join (thread_id1, NULL);
   pthread_join (thread_id2, NULL);

   printf("MMC: %d \n",mmc);
  return 0;
 }