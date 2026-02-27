#include "rando_queue.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 8
#define MIN_CAPACITY 8

struct RandomizedQueue {
    void **data;
    size_t size;
    size_t capacity;
    rq_destructor_fn destructor;
};

static bool resize(RandomizedQueue *rq, size_t new_capacity) {
    void **new_data = malloc(new_capacity * sizeof(void *));
    if (!new_data)
        return false;

    for (size_t i = 0; i < rq->size; i++)
        new_data[i] = rq->data[i];

    free(rq->data);
    rq->data = new_data;
    rq->capacity = new_capacity;

    return true;
}

RandomizedQueue *rq_create(rq_destructor_fn destructor) {
    RandomizedQueue *rq = malloc(sizeof(RandomizedQueue));
    if (!rq)
        return NULL;

    rq->data = malloc(INITIAL_CAPACITY * sizeof(void *));
    if (!rq->data) {
        free(rq);
        return NULL;
    }

    rq->size = 0;
    rq->capacity = INITIAL_CAPACITY;
    rq->destructor = destructor;

    return rq;
}

void rq_destroy(RandomizedQueue *rq) {
    if (!rq)
        return;

    if (rq->destructor) {
        for (size_t i = 0; i < rq->size; i++) {
            rq->destructor(rq->data[i]);
        }
    }

    free(rq->data);
    free(rq);
}

size_t rq_size(const RandomizedQueue *rq) {
    return rq ? rq->size : 0;
}

bool rq_is_empty(const RandomizedQueue *rq) {
    return rq ? rq->size == 0 : true;
}

bool rq_enqueue(RandomizedQueue *rq, void *item) {
    if (!rq)
        return false;

    if (rq->size == rq->capacity) {
        if (!resize(rq, rq->capacity * 2))
            return false;
    }

    rq->data[rq->size++] = item;
    return true;
}

void *rq_dequeue(RandomizedQueue *rq) {
    if (!rq || rq->size == 0)
        return NULL;

    size_t index = rand() % rq->size;
    void *item = rq->data[index];

    rq->data[index] = rq->data[rq->size - 1];
    rq->data[rq->size - 1] = NULL;
    rq->size--;

    if (rq->capacity > MIN_CAPACITY && rq->size <= rq->capacity / 4)
        resize(rq, rq->capacity / 2);

    return item;
}

void *rq_sample(const RandomizedQueue *rq) {
    if (!rq || rq->size == 0)
        return NULL;

    size_t index = rand() % rq->size;
    return rq->data[index];
}