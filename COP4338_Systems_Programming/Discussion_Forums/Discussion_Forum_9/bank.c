#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

pthread_mutex_t mutex;
int balance = 10000;

void* deposit(void* arg) {
    for(int i = 0; i < 100; i++)
        balance += (int)arg;
}

void* withdraw(void* arg) {
    for(int i = 0; i < 100; i++)
        balance -= (int)arg;
}

int main(int argc, char** argv) {
    int thread_no = 1; // default # of deposit/withdraw threads
    // you can update this number by passing
    // an integer as a command-line argument
    if(argc > 1) {
        char* arg_copy = malloc(strlen(argv[1]) + 1);
        strcpy(arg_copy, argv[1]);
        sscanf(arg_copy, "%d", &thread_no);
        free(arg_copy);
    }
    
    fprintf(stderr, "# of deposit threads: %d\n", thread_no);
    fprintf(stderr, "# of withdraw threads: %d\n", thread_no);
    
    pthread_mutex_init(&mutex, NULL); // initialize the mutex lock...
    
    pthread_t deposit_thread_id[thread_no]; // placeholders for deposit thread IDs
    pthread_t withdraw_thread_id[thread_no]; // placeholders for withdraw thread IDs

    for(int i = 0; i < thread_no; i++) {
        while(pthread_create(&deposit_thread_id[i], NULL, deposit, (void*)100)) // "while" tries again if failed!
            ; // create a thread to deposit $100 100 times
        while(pthread_create(&withdraw_thread_id[i], NULL, withdraw, (void*)100)) // "while" tries again if failed!
            ; // create a thread to withdraw $100 100 times
    }
    
    for(int i = 0; i < thread_no; i++) { // main thread waits for all other threads to finish their jobs!
        pthread_join(deposit_thread_id[i], NULL);
        pthread_join(withdraw_thread_id[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    printf("final balance: %d.\n", balance); // see if the balance is corrupted or not!
    
    return 0;
} 