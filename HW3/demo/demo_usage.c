#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dequeue.h>
#include <rando_queue.h>

void int_destructor(void *ptr) {
    free(ptr);
}

int main(void) {
    srand((unsigned)time(NULL));   // seed ONCE in program

    printf("dequeue\n");

    Dequeue *dq = dequeue_create(int_destructor);
    if (!dq) {
        fprintf(stderr, "Failed to create dequeue\n");
        return 1;
    }

    for (int i = 1; i <= 5; i++) {
        int *value = malloc(sizeof(int));
        *value = i;
        dequeue_push_back(dq, value);
    }

    printf("Pop from front:\n");
    while (!dequeue_is_empty(dq)) {
        int *value = dequeue_pop_front(dq);
        printf("%d ", *value);
        free(value);   // since we popped it
    }
    printf("\n");

    dequeue_destroy(dq);



    printf("randomized queue\n");

    RandomizedQueue *rq = rq_create(int_destructor);
    if (!rq) {
        fprintf(stderr, "Failed to create randomized queue\n");
        return 1;
    }

    for (int i = 10; i <= 50; i += 10) {
        int *value = malloc(sizeof(int));
        *value = i;
        rq_enqueue(rq, value);
    }

    printf("Sample (no removal): ");
    int *sample = rq_sample(rq);
    if (sample)
        printf("%d\n", *sample);

    printf("Random dequeue order:\n");
    while (!rq_is_empty(rq)) {
        int *value = rq_dequeue(rq);
        printf("%d ", *value);
        free(value);   // free popped item
    }
    printf("\n");

    rq_destroy(rq);

    return 0;
}