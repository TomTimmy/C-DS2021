#include <stdio.h>
#include <stdlib.h>

// ! treePointer 는 포인트형 변수이다.
typedef struct node* treePointer; // ? typedef struct node*  => treePointer 로 대신 사용. alias 같은 느낌.

// * node 정의. 
// ~ 1. 노드주소에 대응되는 데이터를 담을 data 변수
// ~ 2. 왼쪽, 오른쪽 자식주소를 담을 treePointer 포인터형 leftChild, rightChild 변수.
typedef struct node{
	int data;
	treePointer leftChild, rightChild;
} node;


// * VLR
void preorder(treePointer root){
	if (root){
		printf("%d ", root->data);
		preorder(root->leftChild);
		preorder(root->rightChild);
	}
}

// * recursive search 함수 : 트리포인터(root)와 키를 인자로 받는다. | 찾았다면, 그 녀석의 노드주소를 반환한다.
// ~ 키값에 대응되는 노드의 주소를 반환한다.
treePointer search(treePointer root, int key){
	if (!root)
		return NULL;
	else if (key == root->data) // ? 찾았다.
		return root;
	else if (key < root->data) // ? 키가 root데이터보다 작다? -> 왼쪽으로 이동.
		return search(root->leftChild, key);
	else // ? 키가 root데이터보다 크다? -> 오른쪽으로 이동.
		return search(root->rightChild, key);
}

// * search 함수 : 트리포인터(root)와 키를 인자로 받는다.  | 찾았다면, 그 녀석의 노드주소를 반환한다.
// ~ 키값에 대응되는 노드의 주소를 반환한다.
treePointer iterSearch(treePointer root, int key){
	while (root){ // ? root가 null이 아닐때, 반복시행.
		if (key == root->data) // ? 찾았다.
			return root;
		else if (key < root->data) // ? 키가 root데이터보다 작다? -> 왼쪽으로 이동. (root변수에 root->leftChild 할당)
			root = root->leftChild;
		else // ? 키가 root데이터보다 크다? -> 오른쪽으로 이동. (root변수에 root->rightChild 할당)
			root = root->rightChild;
	}

	return NULL;
}

// * insert에서 사용되는, modifiedSearch 함수: 트리포인터(root)와, 삽입가능한지 판독할 키를 인자로 받는다. | 삽입가능하다면, 키의 부모노드를 리턴한다.
// ~ 탐색후, 키(int)가 삽입될 "위치"를 찾기 위해 사용된다.
// ~ 기존 search 함수를 사용하면, 키 중복조건 확인시, 키가 중복되지 않으면 즉, 삽입가능하면 NULL 을 반환한다.
// ~ 그러나, 우리는 NULL 이 아니라 그 노드의 위치(주소)가 필요하다.
treePointer modifiedSearch(treePointer root, int key){
	treePointer temp = root;
	while (root){
		temp = root; // ? root 주소 NULL 되기전에 백업. (NULL 노드의 부모노드 주소이다.)
		if (key < root->data) // ? 키가 root데이터보다 작다? -> 왼쪽으로 이동. (root변수에 root->leftChild 할당)
			root = root->leftChild;
		else if (key > root->data) // ? 키가 root데이터보다 크다? -> 오른쪽으로 이동. (root변수에 root->rightChild 할당)
			root = root->rightChild;
		else // ? 키가 root데이터와 같다? -> 중복된 키이다. 따라서, 삽입 불가하므로 NULL 반환.
			return NULL;
	}

	// ? 탐색후 삽입가능하다면, 
	// ! NULL 대신, 그 노드의 "부모" 주소를 반환한다!
	return temp;
}

// * delete 함수: 트리포인터(root)와, 삭제할 키를 인자로 받는다. | 리턴값은 int
// ! 경우의수가 많아서 헷갈린다! 집중할 것!!!
// - 삭제대상의 경우의수
// ~ 1. leaf 노드인 경우. (=> 얏호!)
// ~ 2. 자식노드가 한 개 있는 경우.
// ~ 3. 자식노드가 두 개 있는 경우. (=> ㅠㅠ)
// - 기본 알고리즘
// ~ 0. 삭제할 노드를 탐색한다.
// ~ 1. 삭제할 노드랑 swap할 노드를 정한다.
// ~ 2. 삭제 후 생긴 빈자리를 swap타겟노드 채운다.
int delete(treePointer root, int key){
	int temp; // ? temp 는 우리가 삭제할 데이터의 값이다. 즉, 삭제후 그 데이터값을 반환할 것이다. (printf 용으로)

	// ! current: swap할 노드의 주소이다.
	// ! target: 삭제하고자 하는 노드의 주소이다. (즉, 삭제할 키값을 갖고있는 노드)
	// ! previous: crurrent 노드의 "부모"노드 주소이다. (crurrent 노드의 이전 노드이다.)
	treePointer current, target, previous;


	current = root;
	target = NULL;
	
	if (!current) // ? root 가 NULL 이라면 즉, 빈 트리이다. 지울게 없으니 0 리턴.
		return 0; 

	while (1){
		// * 키가 더 크다면, 오른쪽 자식으로 이동한다
		if (key > current->data){ // ? 최초 current 는 root 이다.
			if (current->rightChild == NULL) // ? 이동할 오른쪽 자식노드가 없으면 걍 break
				break;
			previous = current;
			current = current->rightChild;
		}

		// * swap 할 노드를 같이 찾기위해서, "같다면"과 "작다면"를 같이 처리한다
		else{
			// * 키가 같다면, 그녀석이 곧 삭제대상(target)이다.
			if (key == current->data)
				target = current;
			// * 같지 않다면, 즉 작다면, 왼쪽   자식으로 이동한다
			if (current->leftChild == NULL) // ? 왼쪽자식이 없으면 걍 break
				break;
			previous = current; // ? current 자식으로 내려가기 전에 부모노드(previous)에 값 할당.
			current = current->leftChild;
		}
	}

	// ! 아래 알고리즘은 W11#2 강의와 과제#13 을 꼭 참고하여 읽을 것.
	if (target == NULL) // ? 삭제할 노드가 없는경우, 걍 종료.
		return 0;
	else{
		if (previous == NULL){ // ? previous 가 NULL 이란 것은, current 가 root 임을 의미한다.
			temp = current->data;
			free(current);
			root = NULL; // ? root 밖에 없는 트리에서 root 노드를 제거하였으니, NULL 초기화.
			return temp;
		}
		else{
			temp = target->data;
			target->data = current->data;

			if (previous->leftChild == current){
				if (current == target)
					previous->leftChild = current->rightChild;
				else
					previous->leftChild = current->leftChild;
			}
			else{
				if (current == target)
					previous->rightChild = current->rightChild;
				else
					previous->rightChild = current->leftChild;
			}

			free(current);
			return temp;
		}
	}
}

// * insert 함수: 트리포인터(root)와, 삽입할 키를 인자로 받는다. | 리턴값은 없다.
// ! treePointer* => 포인터의 포인터... 즉, 이중포인터이다. "포인터의 주소"를 담을 수 있는 것은 이중포인터이기에 이렇게 선언해줬다.
void insert(treePointer* root, int key){
	treePointer ptr;
	treePointer temp = modifiedSearch(*root, key); // ? temp는 삽입할 키의 부모노드주소이다.

	// ? temp 가 존재하거나,  (=> 즉, 삽입가능한 키라면,)
	// ? "root가 가리키는 값"이 존재하지 않는다면 (=> 즉, root노드가 없다면! => 즉, BST가 아예 쌩 비어있는 트리이면,)
	if (temp || !(*root)){ // ? *root : "포인터변수 root의 주소"를 통해 dereference(주소를 통해 값에 접근) 한다.
		// ? 트리 생성
		ptr = (treePointer) malloc(sizeof(*ptr));
		ptr->data = key; // ? 트리데이터에 키 할당
		ptr->leftChild = ptr->rightChild = NULL; // ? 트리 자식들 초기화

		// * root가 존재한다면, 즉, 빈 트리가 아니라면.
		if (*root){
			//* BST 정의에 따라, temp 자식노드 둘 중 하나에 키값을 담은 노드(prt)의 주소를 할당한다.
			if (key < temp->data)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		// * 빈 트리라면,
		else
			*root = ptr; // * ptr 이 곧 root가 된다.
	}
}


// * 메인문
int main(){
	int item;
	treePointer root = NULL;
	// ?과제#13 1번용 코드, preorder출력: 27 20 5 23 38 30 34 55
	insert(&root, 27);
	insert(&root, 20);
	insert(&root, 38);
	insert(&root, 5);
	insert(&root, 23);
	insert(&root, 30);
	insert(&root, 55);
	insert(&root, 34);

	// insert(&root, 30);
	// insert(&root, 20);
	// insert(&root, 40);
	// insert(&root, 10);
	// insert(&root, 25);
	// insert(&root, 35);
	// insert(&root, 50);

	printf("Preorder traversal: ");
	preorder(root);
	// item = delete(root, 20);
	// printf("\ndeleted item: %d\n", item);

	// printf("Preorder traversal: ");
	// preorder(root);
	// item = delete(root, 35);
	// printf("\ndeleted item: %d\n", item);

	// printf("Preorder traversal: ");
	// preorder(root);
	// item = delete(root, 40);
	// printf("\ndeleted item: %d\n", item);

	// printf("Preorder traversal: ");
	// preorder(root);
	// printf("\n");
}