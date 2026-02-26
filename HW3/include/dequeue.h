#ifndef DEQUEUE_H
#define DEQUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Dequeue Dequeue;
typedef void (*dq_destructor_fn)(void *);

Dequeue *dequeue_create(dq_destructor_fn destructor);
void dequeue_destroy(Dequeue *dq);

size_t dequeue_size(const Dequeue *dq);
bool dequeue_is_empty(const Dequeue *dq);

bool dequeue_push_front(Dequeue *dq, void *item);
bool dequeue_push_back(Dequeue *dq, void *item);

void *dequeue_pop_front(Dequeue *dq);
void *dequeue_pop_back(Dequeue *dq);

void *dequeue_peek_front(const Dequeue *dq);
void *dequeue_peek_back(const Dequeue *dq);

#endif