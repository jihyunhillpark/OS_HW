#define _GNU_SOURCE
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<execinfo.h>
#include<unistd.h>

#define MUTEX_NUM 100
#define THREAD_NUM 10
#define TRUE 1
#define FALSE 0

static pthread_t input_thread[THREAD_NUM] = {0x0,};
static int n_lock = 0;

int pthread_mutex_lock(pthread_mutex_t *mutex){
        int (*pthread_mutex_lock_p)(pthread_mutex_t *mutex);
        static __thread int n_nodes = 0;
        char * error ;
        int i;
        int j;

        pthread_t p_id;
        p_id = pthread_self();

        pthread_mutex_lock_p = dlsym(RTLD_NEXT, "pthread_mutex_lock") ;
        if ((error = dlerror()) != 0x0)
                exit(1);


        for( i=0; i < THREAD_NUM; i++)
        {
                if(!input_thread[i]){
                 input_thread[i]=p_id;
                 break;
                }
                else if( input_thread[i] == p_id) break;

        }
        mutex_nodes[i][n_nodes] = mutex;
        n_nodes += 1;

        fprintf(stderr, "\n========================\n");
        for( i=0; i < THREAD_NUM; i++){
         for( j=0; j< MUTEX_NUM/20 ; j++){
              fprintf(stderr, "[ %p] ",mutex_nodes[i][j]);
         }
         fprintf(stderr, "\n ");
        }
        //fprintf(stderr, "mutex : %p, %d\n",&mutex,n_nodes); 
        return pthread_mutex_lock_p(mutex);

}

int pthread_mutex_unlock(pthread_mutex_t *mutex){
        int(* pthread_mutex_unlock_p)(pthread_mutex_t *mutex);
        char * error ;

        if (mutex == 0x0)
                return 0;

        pthread_mutex_unlock_p = dlsym(RTLD_NEXT, " pthread_mutex_unlock") ;
        if ((error = dlerror()) != 0x0)
                exit(1) ;

        return pthread_mutex_unlock_p(mutex);

}



