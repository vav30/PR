#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking\n", id + 1);

    sem_wait(&room);

    sem_wait(&chopstick[id]);
    printf("Philosopher %d picked left fork\n", id + 1);

    sem_wait(&chopstick[(id + 1) % 5]);
    printf("Philosopher %d picked right fork\n", id + 1);

    printf("Philosopher %d is eating\n", id + 1);
    sleep(1);

    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % 5]);

    printf("Philosopher %d released forks\n", id + 1);

    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t p[5];
    int id[5], i;

    sem_init(&room, 0, 4);

    for(i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    for(i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for(i = 0; i < 5; i++)
        pthread_join(p[i], NULL);

    for(i = 0; i < 5; i++)
        sem_destroy(&chopstick[i]);

    sem_destroy(&room);

    return 0;
}
