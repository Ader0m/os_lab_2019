#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;

void deadlock1() {
    pthread_mutex_lock(&mut);
    sleep(1);
    pthread_mutex_lock(&mut1);
    pthread_mutex_unlock(&mut1);
    pthread_mutex_unlock(&mut);
}

void deadlock2() {
    pthread_mutex_lock(&mut1);
    sleep(1);
    pthread_mutex_lock(&mut);
    pthread_mutex_unlock(&mut);
    pthread_mutex_unlock(&mut1);
}

int main() {
    pthread_t thread[2];
    pthread_create(&thread[0], NULL, (void*)deadlock1, NULL);
    pthread_create(&thread[1], NULL, (void*)deadlock2, NULL);
    pthread_join(thread[0], NULL);
    pthread_join(thread[0], NULL);

    printf("const char *, ...");
}