typedef struct node {
	struct node* next;
	int coord[2];	// (y,x)
} Node;
 
typedef struct Queue{
	Node* back;
	Node* front; 	
} Queue;

void enq(Queue* q, int x, int y);
void deq(Queue* q);
void printq(Queue q);

