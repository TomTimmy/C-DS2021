#include <stdio.h>
#define MAX_ELEMENT 200

// * element
typedef struct {
	int key;
} element;

// * HeapType
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// * 초기화 
void init(HeapType *h)
{
	h->heap_size = 0;
}

/* 현재 요소의 개수가 heap_size인 힙 h에 item을 삽입한다. */
// *  최대 힙(max heap) 삽입 함수: 1. 힙의주소와, 2. 추가할 노드를 input 으로 받는다.
// ~ 1. 맨 마지막 노드에 추가한다.
// ~ 2. 그리고, reheap
void insert_max_heap(HeapType *h, element item) { 
	int i;
	i = ++(h->heap_size); // ?  "힙 크기에 +1" 한 값을 i에 할당. 

/* 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정, reheap */ 
// ?  i가 루트 노트(index: 1)이 아니고, 삽입할 item의 값이 i의 부모 노드(index: i/2)보다 크면
	// ? i/2 = i로 나눈 몫 => 즉, 부모노드.
	// ! 자식노드 값이 부모노드 값보다 크다면, 서로 교환해준다.
	while ((i != 1) && (item.key > h->heap[i/2].key)) {
		// ?  i번째 노드와 부모 노드를 교환환다.
		h->heap[i] = h->heap[i/2];

		// ? 한 레벨 위로 올라간다.
		i /= 2; // ?  => i = i/2
	}
	h->heap[i] = item; // ?  새로운 노드를 삽입
}


// *  최대 힙(max heap) 삭제 함수: heap의 주소만을 input으로 받는다. 오직 root 노드만 삭제한다.
// ~ 1. 가장 큰 값(즉, root 값)을 제거한다.
// ~ 2. 그리고, reheap (reheap은 아래에서 위로 진행됨을 주의하라.)
element delete_max_heap(HeapType *h) {
	int parent, child;
	element item, temp;
	
	item = h->heap[1]; // ?  루트 노드 값을 반환하기 위해 item에 할당
	temp = h->heap[(h->heap_size)--]; // !  1. "마지막 노드"를 temp에 할당하고, 2. 힙 크기를 하나 감소(왜냐면, delete 하고나면, heap_size 하나 감소하니까!)
	parent = 1;
	child = 2;
	
	// * reheap 과정이다.
	while (child <= h->heap_size) {
		// ?  현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다. (루트 노드의 왼쪽 자식 노드(index: 2)부터 비교 시작)
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) { //? 왼쪽자식노드 = heap[child], 오른쪽자식노드 = heap[child + 1]
			child++;
		}

		// ?  마지막 노드(temp.key)가 더 큰 자식 노드보다 크면, while문 중지
		if (temp.key >= h->heap[child].key) {
			break; // ? 즉, reheap 중지!
		}

		// ?  더 큰 자식 노드보다 마지막 노드가 작으면, 부모 노드와 더 큰 자식 노드를 교환
		h->heap[parent] = h->heap[child];

		// ?  한 단계 아래로 이동
		parent = child;
		child *= 2;
	}

	// ?  마지막 노드를 재구성한 위치에 삽입
	h->heap[parent] = temp;
	// ?  최댓값(루트 노드 값)을 반환
	return item;
}

void main()
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }; // ? 각각 key 값으로 10, 5, 30 을 갖고 있는 노드를 선언해준다.
	element e4, e5, e6; // ? delete 하면 return 될 값들을 할당할 변수들 선언.
	HeapType heap; // ? 힙 선언.

	init(&heap); // ? 힙 주소 전달하여 init
	insert_max_heap(&heap, e1); 
	insert_max_heap(&heap, e2) ;
	insert_max_heap(&heap, e3);

	e4 = delete_max_heap(&heap);
	e5 = delete_max_heap(&heap);
	e6 = delete_max_heap(&heap);

	printf("<%d> <%d> <%d>\n", e4.key, e5.key, e6.key);
}