#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void enq(Queue* q, int x, int y) {
	Node* new_node = malloc(sizeof(Node));
	new_node->coord[0] = x;
	new_node->coord[1] = y;
	
	new_node->next = NULL;
	if(q->back != NULL) 
		q->back->next = new_node;
	else 
		q->front = new_node;
	q->back = new_node;
}

void deq(Queue* q) {
	if(q->front == NULL)
		return;
	Node* front = q->front;
	q->front = front->next;
	
	if(front->next == NULL) // case with 1 element in the queue, we want the back to be also null to reset the queue
		q->back = NULL;
	free(front);
}

void printq(Queue q) {
	Node* start = q.front;
	while(start != NULL) {
		printf("(%d, %d) ", start->coord[0], start->coord[1]);
		start = start->next;
	}	
}

