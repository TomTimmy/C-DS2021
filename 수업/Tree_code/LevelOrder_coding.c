#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100
// * LevelOrder 는 Circular Queue 를 이용한다.
// * First In First Out

// * TreeNode
typedef struct TreeNode{
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;


// * QueueType
typedef struct{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 26, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

void error(char* message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(QueueType* q){
	q->front = q->rear = 0;
}

int is_empty(QueueType* q){
	return (q->front == q->rear);
}

// * is_full
int is_full(QueueType* q){

	// ! 큐에서는 "한칸 비어있는" 상태를 full 로 정의한다.
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}


// ! 큐는 rear로 데이터가 들어간다. enqueue: queue INSERT
void enqueue(QueueType* q, element item){
	if (is_full(q))
		error("Queue is full");

		q->rear = (q->rear+1)%MAX_QUEUE_SIZE; // ? Circular Queue 조건 충족시키게끔 rear 증가
		q->queue[q->rear] = item;
	;
}


// ! 큐는 front에서 데이터가 나온다. dequeue: queue DELETE
element dequeue(QueueType* q){
	if (is_empty(q))
		error("Queue is empty");

	q->front = (q->front+1)%MAX_QUEUE_SIZE; // ? Circular Queue 조건 충족시키게끔 front 증가
	return q->queue[q->front];
}

void level_order(TreeNode* ptr){
	QueueType q;
	init(&q);
	if (ptr == NULL)
		return;

	enqueue(&q, ptr);

	while (!is_empty(&q)){
		ptr = dequeue(&q);
		printf("%d\n", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
	printf("\n");
}

void main() {
	level_order(root);
}