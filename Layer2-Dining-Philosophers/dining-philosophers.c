#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t chopsticks[NUM_PHILOSOPHERS];
sem_t waiter;
time_t start_time;

void *philosopher(void*num);
void think(int id);
void pick_up_chopsticks(int id);
void eat(int id);
void put_down_chopsticks(int id);

int main(){
    int i;
    start_time = time(NULL);
    int ids[NUM_PHILOSOPHERS];
    
    	//Initialize arbitrator
    sem_init(&waiter, 0, NUM_PHILOSOPHERS - 1);

    	//Initialize semaphores
    for(i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&chopsticks[i], 0, 1);
   
    	//Create philosopher threads
    for(i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for(i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    return 0;
}

void *philosopher(void*num){
     int id = *(int*)num;
	while(1){
	think(id);
	pick_up_chopsticks(id);
	eat(id);
	put_down_chopsticks(id);
	}
   return NULL;
}


void think(int id){
    printf("[Time %ld]Philosopher %d is thinking.\n", time(NULL) - start_time, id + 1);
    sleep(1);
}

void pick_up_chopsticks(int id){
    sem_wait(&waiter);  
    sem_wait(&chopsticks[id]);    //Pick left chopstick
    sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);  //Pick right chopstick
    printf("[Time %ld]Philosopher %d picked up chopsticks.\n", time(NULL) - start_time, id + 1);
}

void eat(int id){
    printf("[Time %ld]Philosopher %d is eating.\n", time(NULL) - start_time, id + 1);
    sleep(1);
}

void put_down_chopsticks(int id){
    sem_post(&chopsticks[id]);     //Put down left chopstick
    sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);  //Put down right chopstick
    sem_post(&waiter);
    printf("[Time %ld]Philosopher %d put down chopsticks.\n", time(NULL) - start_time, id + 1);
}

