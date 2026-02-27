#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dequeue.h>
#include <rando_queue.h>

void int_destructor(void *ptr) {
    free(ptr);
}

int main(void) {
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
        free(value);   
    }
    printf("\n");

    dequeue_destroy(dq);
}

