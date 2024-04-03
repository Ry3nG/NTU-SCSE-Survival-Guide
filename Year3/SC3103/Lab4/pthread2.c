#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int g_var1 = 0;

void *inc_gv()
{
    int i,j;
    for(i = 0; i<10;i++){
        g_var1++;
        for (j = 0; j<5000000; j++);
        printf(" %d", g_var1);
        fflush(stdout);
    }
}

// add main function
int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, inc_gv, NULL);
    pthread_create(&thread2, NULL, inc_gv, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}