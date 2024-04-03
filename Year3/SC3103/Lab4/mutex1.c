#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int g_var1 = 0;
pthread_mutex_t mutexA; // declare a mutex globally

void *inc_gv()
{
    int i, j;
    for (i = 0; i < 10; i++)
    {  
        pthread_mutex_lock(&mutexA); // lock the mutex
        g_var1++;
        for (j = 0; j < 10; j++)
            ;
        printf(" %d", g_var1);
        fflush(stdout);
        pthread_mutex_unlock(&mutexA); // unlock the mutex
    }
}

// add main function
int main()
{
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutexA, NULL); // initialize the mutex
    

    pthread_create(&thread1, NULL, inc_gv, NULL);

    pthread_create(&thread2, NULL, inc_gv, NULL);
    pthread_join(thread1, NULL);

    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutexA); // destroy the mutex
    return 0;
}