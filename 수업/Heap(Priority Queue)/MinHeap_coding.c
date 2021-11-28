#include <stdio.h>
#define MAX_ELEMENT 200

typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType *h)
{
	h->heap_size = 0;
}

// ? * 구조는 똑같은데, 부등호만 반대다!
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i/2].key)) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}


// ? *  최소 힙(min heap) 삭제 함수
// ? ~ 1. 가장 작은 값(즉, root 값)을 제거한다.
// ? ~ 2. 그리고, reheap
element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
			child++;

		// ? 부모가 자식보다 작다.
		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];

		// ?  한 단계 아래로 이동
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}


// ? * 추가된 함수!
// ? - key 에 해당하는 값을 output 으로 바꿔준다. 
void heap_modify(HeapType *h, int key, int output)
{
	int parent, child;
	element item, temp;
	parent = h->heap_size;

	//search correct key, and modify
	while (h->heap[parent].key != key)
		parent--;
	h->heap[parent].key = output;

	//sorting
	child = parent*2;
	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
			child++;

		// ? 첫번쨰 while문
		// ? MinHeap 에서는 부모가 자식보다 크면 안된다.
		// ? ~ 조건 위배시, 이 둘의 값을 서로 교환한다.
		if (h->heap[parent].key > h->heap[child].key) // ? parent > child
		{
			temp = h->heap[parent];
			h->heap[parent] = h->heap[child];
			h->heap[child] = temp;
			parent = child;
			child *= 2;
		}
		else
			break;
		
	}

	// ? 두번쨰 while문
	while (parent <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
		{	
			// ? grandparent > parent
			if (parent == 1)break;
			
			temp = h->heap[parent / 2];
			h->heap[parent / 2] = h->heap[child];
			h->heap[parent] = temp;
			parent = child; //value need check
			child *= 2;
		}
		else
			break;
	}
}

void main()
{
	int i;
	element e1 = { 10 }, e2 = { 30 }, e3 = { 15 }, e4 = { 16 }, e5 = { 20 };
	HeapType heap;
	init(&heap);
	insert_min_heap(&heap, e1);
	insert_min_heap(&heap, e2);
	insert_min_heap(&heap, e3);
	insert_min_heap(&heap, e4);
	insert_min_heap(&heap, e5);

	for (i = 1; i <= heap.heap_size; i++)
		printf("<%d> ", heap.heap[i].key);
	printf("\n");

	heap_modify(&heap, 30, 14);

	for (i = 1; i <= heap.heap_size; i++)
		printf("<%d> ", heap.heap[i].key);
	printf("\n");
}