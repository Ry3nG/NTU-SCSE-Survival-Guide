#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* print_message(void *ptr)
{
    pthread_mutex_lock(&mutex);
    char* text;
    text = (char*) ptr; 


    printf("%s\n", text);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    int T1ret, T2ret;

    char* str1 = "I am thread 1";
    char* str2 = "I am thread 2";

    T1ret = pthread_create(&thread1, NULL, print_message, (void*) str1);
    T2ret = pthread_create(&thread2, NULL, print_message, (void*) str2);


    printf("I am main thread");
     return 0;
}