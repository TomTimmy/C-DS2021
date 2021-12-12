#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
	int key;
} element;

typedef struct treeNode* treePointer;

typedef struct treeNode {
	treePointer leftChild;
	element data;
	int bf;
	treePointer rightChild; 
} treeNode;


//* VLR (RECURSIVE) 
void preorder(treePointer root){
	if (root){
		printf("%d ", root->data.key);
		preorder(root->leftChild);
		preorder(root->rightChild);
	}
}


// * leftRotation 함수 
void leftRotation(treePointer* parent, int* unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->leftChild;

	// * LL Rotation
	if (child->bf == 1) {
	// ~ 	(20) <- parent
	// ~  (10) <- child
	// ~ (5) <- will be inserted one
		/* LL Rotation */
		(*parent)->leftChild = child->rightChild; // ? child 의 서브트리가 있을 수 도 있으니,
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}

	// * LR Rotation
	else {
	// ~ 	(20) <- parent
	// ~  (10) <- child
	// ~ 	(15) <- will be inserted one
		/* LR Roatation */
		// * L Rot.
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild; // ? grandChild 의 서브트리가 있을 수 도 있으니,
		grandChild->leftChild = child;
		//* R Rot.
		(*parent)->leftChild = grandChild->leftChild;
		grandChild->rightChild = *parent;

		// ! 각각의 경우에 대해 상황 그림 그려야 한다. 안 그리고 이해하려 하면 겁나 헷갈림.
		switch (grandChild->bf) {
			case 1:
				(*parent)->bf = -1;
				child->bf = 0;
				break;
			case 0:
				(*parent)->bf = child->bf = 0;
				break;
			case -1:
				(*parent)->bf = 0;
				child->bf = 1;
				break;
		}
		*parent = grandChild;
	}

	(*parent)->bf = 0;
	*unbalanced = FALSE;
}


// * rightRotation 함수 
void rightRotation(treePointer* parent, int* unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->rightChild;

	if (child->bf == -1) {
		/* RR Rotation */
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}

	else {
		/* RL Rotataion */
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->rightChild;
		grandChild->leftChild = *parent;
		switch (grandChild->bf) {
			case -1:
				(*parent)->bf = -1;
				child->bf = 0;
				break;
			case 0:
				(*parent)->bf = child->bf = 0;
				break;
			case 1:
				(*parent)->bf = 0;
				child->bf = 1;
				break;
		}
		*parent = grandChild;
	}

	(*parent)->bf = 0;
	*unbalanced = FALSE;
}


// * Insertion (RECURSIVE)
// ~ "이중"포인터 parent, 삽입값 x, unbalanced의 주소를 담을 *unbalanced
// ~ 1. root 노드와 말단 노드를
void avlInsert(treePointer* parent, element x, int* unbalanced) {
	// * parent의 값이 NULL 이면 시행. 
	// * 즉, 빈 트리 or 말단 노드일때 시행되는 코드이다.
	if (!*parent) { /*insert element into null tree*/
		*unbalanced = TRUE; // ? 최초삽입시에는 Balance 할 것이다. 그럼에도 불구하고 *unbalanced = TRUE 라고 한 이유는 else if 문안에 있는 RECURSIVE CALL 때문에 그러하다.
		*parent = (treePointer)malloc(sizeof(treeNode)); 
		(*parent)->leftChild = (*parent)->rightChild = NULL;
		(*parent)->bf = 0; 
		(*parent)->data = x;
	} 
	// * x가 더 작으면 왼쪽으로~
	else if (x.key < (*parent)->data.key) { 
		// * RECURSIVE CALL! 
		// * 말단 노드를 찾을떄까지 계속 간다~(RECURSIVE CALL)
		avlInsert(&((*parent)->leftChild), x, unbalanced); // ! 지금은 avlInsert 함수 내부니까, 인자로 들어가는 "unbalanced" 는 "unbalanced의 주소"값이다.
		// * 말단 노드를 찾은뒤, 상단 if 문을 시행해서 unbalanced 값이 True 이면, 아래코드가 실행된다. 
		if (*unbalanced) {
			/*left branch has grown higher*/
			// * 부모노드의 Balance Factor (bf) 확인!
			switch ((*parent)->bf) {
				case -1:
					(*parent)->bf = 0;
					*unbalanced = FALSE; // ? 여기까진 상식적이다. balnce 하니까 unbalanced 값은 FALSE. 
					break;
				case 0:
					(*parent)->bf = 1;
					// ! 여기선 왜 unbalanced 값을 안 바꿔주는가?? ... 질문
					break;
				case 1:
					// * LL, LR 회전의 경우를 모두 포함하는 leftRotation 함수
					leftRotation(parent, unbalanced); // ! 지금은 avlInsert 함수 내부니까, 인자로 들어가는 "unbalanced" 는 "unbalanced의 주소"값이다.
					break;
			} 
		}
	}

	// * x가 더 크면 오른쪽으로~
	else if(x.key > (*parent)->data.key){
		avlInsert(&((*parent)->rightChild), x, unbalanced);
		if(*unbalanced){
			/*right barnch has grown higher*/
			switch((*parent)->bf){
				case 1:
					(*parent)->bf = 0;
					*unbalanced = FALSE;
					break;
				case 0:
					(*parent)->bf = -1;
					break;
				case -1:
					// * RR, RL 회전의 경우를 모두 포함하는 rightRotation 함수
					rightRotation(parent, unbalanced);
					break;
			}
		}
	}

	// * x가 어떤 노드의 값이랑 같음. 즉, 이미 있음~
	else {
		*unbalanced = FALSE;
		printf("The key is already in the tree\n");
	}
}

int avlFindMin(treePointer* parent){ /* Find minimum node */
	treePointer current, pre;

	if ((*parent)->leftChild){
		current = pre = (*parent)->leftChild;
		while (current != NULL){
			pre = current;
			current = current->rightChild;
		}
	}

	else{
		current = pre = (*parent)->rightChild;
		while (current != NULL){
			pre = current;
			current = current->leftChild;
		}
	}

	return pre->data.key;
}


int isLeaf(treePointer* parent){
	if ((*parent)->leftChild || (*parent)->rightChild)
		return FALSE;

	return TRUE;
}


void delLeftRotation(treePointer* parent, int* unbalanced){
	treePointer grandChild, child;
	child = (*parent)->leftChild;

	if (child->bf == 1){
		/* LL Rotation */
		(*parent)->leftChild = child->rightChild;
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
		(*parent)->bf = 0;
	}

	else{
		/* LR Roatation */
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild;
		grandChild->leftChild = child;
		(*parent)->leftChild = grandChild->rightChild;
		grandChild->rightChild = *parent;

		switch(grandChild->bf){
			case -1:
				(*parent)->bf = -1;
				child->bf = 0;
				break;
			case 1:
				(*parent)->bf = child->bf = 0;
				break;
			case 0:
				(*parent)->bf = 0;
				child->bf = 1;
				grandChild->bf = 1;
				break;
		}
		*parent = grandChild;
	}

	*unbalanced = TRUE;
}
void delRightRotation(treePointer* parent, int* unbalanced){
	treePointer grandChild, child;
	child = (*parent)->rightChild;

	if (child->bf == -1){
		/* RR Rotation */
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
		(*parent)->bf = 0;
	}

	else{
		/* RL Roatation */
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->leftChild;
		grandChild->leftChild = *parent;

		switch(grandChild->bf){
			case -1:
				(*parent)->bf = -1;
				child->bf = 0;
				break;
			case 0:
				(*parent)->bf = child->bf = 0;
				break;
			case 1:
				(*parent)->bf = 0;
				child->bf = 1;
				break;
		}
		*parent = grandChild;
	}

	*unbalanced = TRUE;
}


// * DELETION (RECURSIVE)
void avlDelete(treePointer* parent, element x, int* unbalanced){
	int parentKey;

	if (!*parent){ /*No Node in tree*/
		*unbalanced = FALSE;
		printf("The Tree is empty or NOT Found\n\n");
		return;
	}

	parentKey = (*parent)->data.key; // ? *parent 는 이중포인터 이다.

	// * 삭제대상이 말단 노드이면,
	if ((x.key == (*parent)->data.key) && isLeaf(parent)){
		free(*parent); // ? parent 는 이중포인터이다. 말단 노드면 걍 free
		*parent = NULL;
		*unbalanced = TRUE;
		return;
	}

	// * 삭제대상이 말단 노드가 아니면,
	if ((x.key == (*parent)->data.key) && !isLeaf(parent)){
		parentKey = (*parent)->data.key;
		x.key = avlFindMin(parent); 
		(*parent)->data.key = x.key;
	}

	// ~ 이렇게, 삭제후 빈 자리에 적절한 값 복붙하고 나서,
	// ~ 원래위치에 남아있는 (적절한 대상)값 찾아서 삭제

	// * 그 값이 parent 보다 왼쪽에 있는 값이었던 경우,
	if (x.key < parentKey){
		avlDelete(&(*parent)->leftChild, x, unbalanced);
		if (*unbalanced){
			switch ((*parent)->bf){
				case 1:
					(*parent)->bf = 0;
					break;
				case 0:
					(*parent)->bf = -1;
					*unbalanced = FALSE;
					break;
				case -1: // ? 삭제하면 밸런스 깨진다.. 따라서, delRightRotation 호출
					delRightRotation(parent, unbalanced);
					*unbalanced = TRUE;
					break;
			}
		}
	}

	// * 그 값이 parent 보다 오른쪽에 있는 값이었던 경우,
	else if (x.key > parentKey){
		avlDelete(&(*parent)->rightChild, x, unbalanced);
		if (*unbalanced){
			switch ((*parent)->bf){
				case -1:
					(*parent)->bf = 0;
					break;
				case 0:
					(*parent)->bf = 1;
					*unbalanced = TRUE;
					break;
				case 1:
					delLeftRotation(parent, unbalanced);
					*unbalanced = TRUE;
					break;
			}
		}
	}
}

void menu() {
	printf("Insert 'i'\n");
	printf("Delete 'd'\n");
	printf("Preorder Show 's'\n");
	printf("EXIT 'e'\n");
}
 

// * main 문
int main(void) {
	int unbalanced;
	char input;
	treePointer root = NULL; // ? root 노드(구조체)의 주소
	element x;
 
	while (1) {
		menu(); // ? 단순히 command 메뉴를 출력해주는 함수,
		scanf("%s", &input);
		system ("clear"); // ? 터미널메시지들 깔끔하게 지워주는 함수 ㅇㅇ 
		
		switch (input) {
			case 'i': // ? INSERTION
				printf("Please enter a number to i: \n");
				scanf("%d", &x.key);
				system ("clear");
				// * 구조체포인터의주소 &root, 삽입값 x, unbalanced주소 &unbalanced
				avlInsert(&root, x, &unbalanced); // ! &root 이므로, 구조체 "포인터"의 주소이다! (root 였으면 그냥 구조체의 주소임.)
				break;
			case 'd': // ? DELETION 
				printf("Please enter a number to d: \n") ;
				scanf("%d", &x.key);
				system ("clear");
				avlDelete(&root, x, &unbalanced);
				break;
			case 's': // ? SCAN
				printf("Preorder: ");
				preorder(root);
				printf("\n\n");
				break;
			case 'e': 
				return 0; 
			default:
				printf("Unknow Command\n");
		}
	}

	return 0;
}