#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <rando_queue.h>

void int_destructor(void *ptr) {
    free(ptr);
}



    int main(){
    srand((unsigned)time(NULL));

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
        free(value);
    }
    printf("\n");

    rq_destroy(rq);

    return 0;
}

