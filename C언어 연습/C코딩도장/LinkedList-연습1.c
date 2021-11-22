// https://dojang.io/mod/page/view.php?id=645
// ! Single LinkedList 이다.

#include <stdio.h>
#include <stdlib.h>

struct NODE {
    struct NODE *next; // ? 다음 노드주소를 담을, NODE 구조체형 포인터 변수 
    int data;// ? 현재 노드에 담을 데이터가 할당될 변수
};

int main() {
    struct NODE *head = malloc(sizeof(struct NODE));

    struct NODE *node1 = malloc(sizeof(struct NODE));
    head->next = node1; // ? head 노드(처음 노드)는 data를 갖고 있지 않다.
    node1->data = 10;

    struct NODE *node2 = malloc(sizeof(struct NODE));
    node1->next = node2;
    node2->data = 20;

    node2->next = NULL; // ? Single LinkedList 에서 마지막 노드는 다음 노드주소로 NULL 을 갖고있다.

    //* display 구현하기 
    struct NODE *curr = head->next;
    while (curr != NULL) {
        printf("%d\n", curr->data);

        //! 매우 중요한 부분이다.
        // ? curr 에 현재노드가 가리키는 다음 노드주소(curr->next)를 할당한다!
        curr = curr->next;
    }

    free(node2);
    free(node1);
    free(head);

    return 0;
}