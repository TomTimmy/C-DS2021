#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 2018040155 최수민
typedef char element;

typedef struct ListNode{
	element data;
	struct ListNode *link;
} ListNode;

ListNode *create_node(element data){
	ListNode *newNode;
	newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->data = data;
	newNode->link = NULL;

	return newNode;
}

void insert(ListNode **phead, ListNode *p, ListNode *newNode){
	if(*phead == NULL){
		newNode->link = NULL;
		*phead = newNode;
	}
	else {
		newNode->link = *phead;
		*phead = newNode;
	}
}

void display(ListNode *head){
	ListNode *p = head;

	while(p != NULL){
		printf("%c", p->data);
		p = p->link;
	}
	printf("\n");
}

ListNode *search(ListNode *head, char searchTarget){
	ListNode *p;
	p = head;

	while(p != NULL){
		if(p->data == searchTarget)
			return p;
		p = p->link;
	}
	return p;
}

ListNode* reverse(ListNode *head){
	ListNode *p, *q, *r;

	p = head;
	q = NULL;

	while(p != NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

//* 메인함수
int main() {
	ListNode *head = NULL; //! 포인터 변수는 항상 NULL 초기화!
	char word[5];
	printf("5자초과 입력 ㄴㄴ : ");
	scanf("%s", word);

	int wordLength = strlen(word);
	for(int index=1; index < wordLength; index++) {
        if (index==1) 
            insert(&head, head, create_node(word[0]));

		insert(&head, search(head, word[index-1]), create_node(word[index]));
    }

	display(head);
	display(reverse(head));

    return 0;
}

