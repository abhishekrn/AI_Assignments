#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct node {
	int val;
	struct node *next;
} node;

typedef struct queue {
	node *head;
	node *tail;
} queue;

void InitQueue(queue *q) {
	q->head = NULL;
	q->tail = NULL;
}

int IsEmptyQueue(queue *q) {
	return (q->head == NULL);
}

void Enqueue(queue *q, int val) {
	node *n = (node *)malloc(sizeof(node));
	n->val = val;
	n->next = NULL;
	if(IsEmptyQueue(q)) {
		q->head = q->tail = n;
		return;
	}
	q->tail->next = n;
	q->tail = n;
}

int Dequeue(queue *q) {
	node *temp;
	int val = INT_MAX;
	if(!IsEmptyQueue(q)) {
		val = q->head->val;	
		if(q->head == q->tail) {
			free(q->head);
			q->head = q->tail = NULL;
		}
		else {
			temp = q->head;
			q->head = q->head->next;
			free(temp);	
		}
	}
	return val;
}

void PrintQueue(queue *q) {
	node *n = q->head;
	if(n) {
		printf("%d->", n->val);
		n = n->next;
	}
	while(n && n != q->tail) {
		printf("%d->", n->val);
		n = n->next;
	}
	printf("\n");
}

void BreadthFirstSearch(int n, int root, int graph[][n]) {
	int visited[n];
	int i;
	for(i = 0; i < n; i++) {
		visited[i] = 0;
	}
	queue q;
	InitQueue(&q);
	Enqueue(&q, root);
	int num;
	while(!IsEmptyQueue(&q)) {
		num = Dequeue(&q);
		printf("Num%d\n", num);
		visited[num] = 1;
		for(i = 0; i < n; i++) {
			if(graph[num][i] == 1) {
				if(!visited[i]) {
					Enqueue(&q, i);
					visited[i] = 1;
				}
			}
		}
	}
}


int main() {
	int graph[][5] = {
			{ 0, 1, 0, 0, 1 },
			{ 1, 0, 1, 1, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 1, 1, 0, 1 },
			{ 1, 1, 0, 1, 0 }
			};
	BreadthFirstSearch(5, 2, graph);
	return 0;
}
