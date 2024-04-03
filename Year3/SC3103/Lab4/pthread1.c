# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

void *print_message(void *ptr){
    char *text;
    text = (char*) ptr;
    printf("%s\n", text);
    return NULL;
}

main()
{
    pthread_t thread1, thread2;
    char *str1 = "Thread 1";
    char *str2 = "Thread 2";
    int iret1, iret2;

    // create two threads
    iret1 = pthread_create(&thread1, NULL, print_message, (void *) str1);
    iret2 = pthread_create(&thread2, NULL, print_message, (void *) str2);

    // wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("T1 & T2 return: %d, %d\n", iret1, iret2);
    return 0;
}