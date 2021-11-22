// https://dojang.io/mod/page/view.php?id=646
// ! 노드 추가 함수 만들기

#include <stdio.h>
#include <stdlib.h>

struct NODE {
    struct NODE *next; // ? 다음 노드주소를 담을, NODE 구조체형 포인터 변수 
    int data;// ? 현재 노드에 담을 데이터가 할당될 변수
};

//* 노드 추가 함수 (기준노드 뒤에 노드를 추가한다)
void addFirst(struct NODE *target, int data) {
    // ? 새 노드
    struct NODE *newNode = malloc(sizeof(struct NODE));

    // ? 기준노드(target)가 가리키는 다음 노드주소를 새 노드에게도 할당한다.
    newNode->next = target->next;
    newNode->data = data;

    // ? 기준노드가 가리키는 다음 노드주소를 새 노드의 주소로 수정한다.
    target->next = newNode;
}


int main() {
    struct NODE *head = malloc(sizeof(struct NODE));
    head->next = NULL; // ? head 노드(처음 노드)가 가리키는 다음 노드주소를 NULL 로 초기화
    // ! head 노드는 데이터를 갖고 있지 않다.

    // ? 노드 추가 함수 addFirst 를 사용하여 노드 추가.
    addFirst(head, 10); // ! 새 노드가 가리키는 다음 주소는 NULL 이다. (head 가 가리켰던 주소가 NULL 이므로!) 
    addFirst(head, 20); // ! 새 노드가 가리키는 다음 주소는 바로 위에서 생성된 노드 주소다.
    addFirst(head, 30); // ! 새 노드가 가리키는 다음 주소는 바로 위에서 생성된 노드 주소다.
    // ! 결과적으로, LinkedList 의 첫 부분에서 노드가 계속 추가된다.
    // (head ->) 30 -> 20 -> 10

    //* display 구현하기 
    struct NODE *curr = head->next;
    while (curr != NULL) {
        printf("%d\n", curr->data);

        //! 매우 중요한 부분이다.
        // ? curr 에 현재노드가 가리키는 다음 노드주소(curr->next)를 할당한다!
        curr = curr->next;
    }

    //* 메모리주소 순차적으로 free 시키기
    curr = head->next;
    while (curr != NULL) {
        struct NODE *next = curr->next; // ? free(curr) 을 먼저하면, 다음 노드에 접근할 수 가 없다.
        free(curr);
        curr = next;
    }

    free(head); // ?  마지막으로 head 의 메모리주소를 free 해준다.

    return 0;
}