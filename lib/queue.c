#ifndef HEADER
#include "../header.h"
#include "queue.h"
#include <stdlib.h>
#endif

void enqueue(QUEUE* queue,NODE* item){
  if (queue->queue == NULL){
    queue->queue = (NODE**)malloc(100*sizeof(NODE*));
    queue->queue_front = 0;
  }
  queue->queue_rear++;
  queue->queue[queue->queue_rear] = item;
}

NODE* dequeue(QUEUE* q){
  if (q->queue_front != -1 && q->queue_front <= q->queue_rear){
    //not empty
    NODE* temp = q->queue[q->queue_front];
    q->queue_front++;
    if (q->queue_front > q->queue_rear){
      free(q->queue);
      q->queue = NULL;
      q->queue_front = -1;
      q->queue_rear = -1;
    }
    return temp;
  }else{
    return NULL;
  }
}