#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// 구조체 선언
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode n1 = { 'B', NULL, NULL };
TreeNode n2 = { 'A', NULL, NULL };
TreeNode n3 = { 'C', NULL, NULL };
TreeNode n4 = { '/', &n2, &n1 };
TreeNode n5 = { 'D', NULL, NULL };
TreeNode n6 = { '*', &n4, &n3 };
TreeNode n7 = { 'E', NULL, NULL };
TreeNode n8 = { '-', &n6, &n5 };
TreeNode n9 = { '+', &n8, &n7 };
TreeNode* root = &n9;

// ! "구조체 포인터" 타입의 stack 배열을 선언한다!
TreeNode* stack[MAX_STACK_SIZE]; // ? 즉, stack 에다가는 구조체 주소를 저장할 것이다~!

// ! 구조체 포인터를 element로 사용하겠다.
typedef TreeNode* element;
int top = -1;

int is_empty(){
	return (top == -1);
}

int is_full(){
	return (top == (MAX_STACK_SIZE - 1));
}

void push(element item){
	if (is_full()){
		fprintf(stderr, "stack is full\n");
		return;
	}
	else
		// ? 1. 먼저 ++ 해주고, 2. 그 값 인덱스에 item 을 넣겠다.
		stack[++top] = item;
}

element pop(){
	if (is_empty()){
		fprintf(stderr, "stack is empty\n");
		exit(1);
	}
	else
		return stack[top--];
}

element peek(){
	if (is_empty()){
		fprintf(stderr, "stack is empty\n");
		exit(1);
	}
	else
		return stack[top];
}


// * LVR
void iterInorder(TreeNode* root){
	TreeNode* node = root;

	// * do-while 문이다...
	// ! 일단 do 먼저 시행 후,
	// ! while 문을 만족할때까지 계속 반복 시행.
	do {
		// ? node 가 NULL이 아니면, 반복 시행.
		for ( ; node; node = node->left )
			push(node);

		// element storedNode = pop();
		// for ( element storedNode = pop() ; storedNode; storedNode = pop())
		// 	printf("%c \n", storedNode->data);
		// 위 코드는 답이 아니다.

		node = pop();
		printf("%c \n", node->data);
		node = node->right; 
		
	// ! node 가 null 이라도, stack이 비어있지만 않으면 반복한다!
	} while (!is_empty() || node != NULL);
	printf("\n");
}

int main(){
	iterInorder(root);

	return 0;
}