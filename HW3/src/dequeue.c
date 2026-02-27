#include "dequeue.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 8
#define MIN_CAPACITY 8

struct Dequeue {
    void **data;
    size_t size;
    size_t capacity;
    size_t front;
    size_t back;
    dq_destructor_fn destructor;
};

static bool resize(Dequeue *dq, size_t new_capacity) {
    void **new_data = malloc(new_capacity * sizeof(void *));
    if (!new_data)
        return false;

    for (size_t i = 0; i < dq->size; i++)
        new_data[i] = dq->data[(dq->front + i) % dq->capacity]; // circular behaviour

    free(dq->data);
    dq->data = new_data;
    dq->capacity = new_capacity;
    dq->front = 0;
    dq->back = dq->size;
    return true;
}

Dequeue *dequeue_create(dq_destructor_fn destructor) {
    Dequeue *dq = malloc(sizeof(Dequeue));
    if (!dq)
        return NULL;

    dq->data = malloc(INITIAL_CAPACITY * sizeof(void *));
    if (!dq->data) {
        free(dq);
        return NULL;
    }

    dq->size = 0;
    dq->capacity = INITIAL_CAPACITY;
    dq->front = 0;
    dq->back = 0;
    dq->destructor = destructor;

    return dq;
}

void dequeue_destroy(Dequeue *dq) {
    if (!dq)
        return;

    if (dq->destructor) {
        for (size_t i = 0; i < dq->size; i++) {
            void *item = dq->data[(dq->front + i) % dq->capacity];
            dq->destructor(item);
        }
    }

    free(dq->data);
    free(dq);
}

size_t dequeue_size(const Dequeue *dq) {
    return dq ? dq->size : 0;
}

bool dequeue_is_empty(const Dequeue *dq) {
    return dq ? dq->size == 0 : true;
}

bool dequeue_push_front(Dequeue *dq, void *item) {
    if (!dq)
        return false;

    if (dq->size == dq->capacity) {
        if (!resize(dq, dq->capacity * 2))
            return false;
    }

    dq->front = (dq->front == 0) ? dq->capacity - 1 : dq->front - 1;
    dq->data[dq->front] = item;
    dq->size++;
    return true;
}

bool dequeue_push_back(Dequeue *dq, void *item) {
    if (!dq)
        return false;

    if (dq->size == dq->capacity) {
        if (!resize(dq, dq->capacity * 2))
            return false;
    }

    dq->data[dq->back] = item;
    dq->back = (dq->back + 1) % dq->capacity;
    dq->size++;
    return true;
}

void *dequeue_pop_front(Dequeue *dq) {
    if (!dq || dq->size == 0)
        return NULL;

    void *item = dq->data[dq->front];
    dq->front = (dq->front + 1) % dq->capacity;
    dq->size--;

    if (dq->capacity > MIN_CAPACITY && dq->size <= dq->capacity / 4)
        resize(dq, dq->capacity / 2);

    return item;
}

void *dequeue_pop_back(Dequeue *dq) {
    if (!dq || dq->size == 0)
        return NULL;

    dq->back = (dq->back == 0) ? dq->capacity - 1 : dq->back - 1;
    void *item = dq->data[dq->back];
    dq->size--;

    if (dq->capacity > MIN_CAPACITY && dq->size <= dq->capacity / 4)
        resize(dq, dq->capacity / 2);

    return item;
}

void *dequeue_peek_front(const Dequeue *dq) {
    if (!dq || dq->size == 0)
        return NULL;

    return dq->data[dq->front];
}

void *dequeue_peek_back(const Dequeue *dq) {
    if (!dq || dq->size == 0)
        return NULL;

    size_t index = (dq->back == 0) ? dq->capacity - 1 : dq->back - 1;
    return dq->data[index];
}