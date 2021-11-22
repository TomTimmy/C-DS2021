#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct StackNode{
	element item;
	struct StackNode* link;
	
} StackNode; // ? item 과 link 선언

typedef struct{
	StackNode* top;
} LinkedStackType;

 // * 초기화 함수
void init(LinkedStackType* s){
	s->top = NULL;
}

// * 공백 상태 검출 함수
int is_empty(LinkedStackType* s){
	return (s->top == NULL);
}

int is_full(LinkedStackType* s){
 	// ? LinkedStack 에서 is_full 은 의미가 없다.
	return 0;
}

void push(LinkedStackType* s, element item){
	// ? StackNode 크기만큼 방을 만들어서 주소값을 temp 에다가 넣는다.
	StackNode* temp = (StackNode* )malloc(sizeof(StackNode));

	if (temp == NULL){
		fprintf(stderr, "Memory allocation error\n");
		return;
	}
	else{
		// ? temp 를 활용하여, item과 link 필드를 다룬다.
		temp->item = item;
		temp->link = s->top;
		// ? 이후, s top 의 주소를 바꿔준다.
		s->top = temp;
	}
}


element pop(LinkedStackType* s){
	// ! s 는 포인터다. 포인터이므로 그냥 s 를 넣는다. &s 아님!
	if (is_empty(s)){ 
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else{
		StackNode* temp = s->top;
		element popitem = temp->item;
		s->top = temp->link;

		free(temp); // ? 할당한 메모리공간 해제
		return popitem;
	}
}

element peek(LinkedStackType* s){
	if (is_empty(s)){
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else{
		// ? s->top 은 주소를 갖고있다.
		// ? 그 주소가 가리키고 있는 item을 선택!
		return s->top->item;
	}
}


// *
void PrintStacks(LinkedStackType s) {
	StackNode* temp = s.top;

	printf("Print: ");
}

// * 
int main()
{
	LinkedStackType s;
	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("is Empty? : %d\n", is_empty(&s));

	return 0;
}