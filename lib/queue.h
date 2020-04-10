#ifndef HEADER
#include "../header.h"
#endif
typedef struct queue {
    NODE** queue;
    int queue_front;
    int queue_rear;
} QUEUE;

extern void enqueue(QUEUE* ,NODE* );
extern NODE* dequeue(QUEUE* );