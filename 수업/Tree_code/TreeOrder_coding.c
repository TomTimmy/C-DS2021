#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 26, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6; //! <- 이걸 보자!ㅎㅎ

// * LVR
void inorder(TreeNode* root){
	if (root){ 
		inorder(root->left); 
		printf("%d\n", root->data);
		inorder(root->right);
	}
}

// * VLR
void preorder(TreeNode* root){
	if (root) {
		printf("%d\n", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

// * LRV
void postorder(TreeNode* root){
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d\n", root->data);
	}
}

void main() {
	printf("inorder: \n");
	inorder(root);
	printf("\n");
	
	printf("preorder: \n");
	preorder(root);
	printf("\n");
	
	printf("postorder: \n");
	postorder(root);
	printf("\n");
}