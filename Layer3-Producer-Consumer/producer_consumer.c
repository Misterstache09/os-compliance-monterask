#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 4

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} buffer_t;

buffer_t shared;
int item_counter = 1;   // Items start at 1
time_t start_time;

void print_buffer(){
    printf("--- Buffer:[ ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", shared.buffer[i]);
    }
  printf("] ---\n");
}

void *producer(void*arg){
    int id = *(int*)arg;

    while(1){
       
        sem_wait(&shared.empty);
        sem_wait(&shared.mutex);

	int item = item_counter;
	item_counter++;

        printf("[Time %ld]Producer %d produced %d at index %d\n",
               time(NULL) - start_time, id, item, shared.in);

        shared.buffer[shared.in] = item;
        shared.in = (shared.in + 1) % BUFFER_SIZE;

        print_buffer();

        sem_post(&shared.mutex);
        sem_post(&shared.full);

      sleep(10); 
    }
}

void *consumer(void*arg){
    int id = *(int*)arg;

    while (1) {
        sem_wait(&shared.full);
        sem_wait(&shared.mutex);

        int item = shared.buffer[shared.out];
        shared.buffer[shared.out] = 0;

        printf("[Time %ld]Consumer %d consumed %d from index %d\n",
               time(NULL) - start_time, id, item, shared.out);

        shared.out = (shared.out + 1) % BUFFER_SIZE;

        print_buffer();

        sem_post(&shared.mutex);
        sem_post(&shared.empty);

      sleep(10); 
    }
}


int main(){
    pthread_t prod[NUM_PRODUCERS];
    pthread_t cons[NUM_CONSUMERS];

    start_time = time(NULL);

    printf("Producers: %d\n", NUM_PRODUCERS);
    printf("Consumers: %d\n", NUM_CONSUMERS);

    shared.in = 0;
    shared.out = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
        shared.buffer[i] = 0;

    sem_init(&shared.empty, 0, BUFFER_SIZE);
    sem_init(&shared.full, 0, 0);
    sem_init(&shared.mutex, 0, 1);

    int p_id[NUM_PRODUCERS] = {1, 2, 3};
    int c_id[NUM_CONSUMERS] = {1, 2, 3, 4};

    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_create(&prod[i], NULL, producer, &p_id[i]);

    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_create(&cons[i], NULL, consumer, &c_id[i]);

    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_join(prod[i], NULL);

    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_join(cons[i], NULL);

  return 0;
}
