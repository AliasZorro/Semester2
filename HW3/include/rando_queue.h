#ifndef RANDO_QUEUE_H
#define RANDO_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef void (*rq_destructor_fn)(void *);

typedef struct RandomizedQueue RandomizedQueue;

RandomizedQueue *rq_create(rq_destructor_fn destructor);
void rq_destroy(RandomizedQueue *rq);

size_t rq_size(const RandomizedQueue *rq);
bool rq_is_empty(const RandomizedQueue *rq);

bool rq_enqueue(RandomizedQueue *rq, void *item);
void *rq_dequeue(RandomizedQueue *rq);
void *rq_sample(const RandomizedQueue *rq);

#endif