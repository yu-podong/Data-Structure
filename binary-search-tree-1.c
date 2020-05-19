#include <stdio.h>
#include <stdlib.h>

typedef struct node {		//Binary Search Tree의 노드를 구성할 구조체 
	int key;				//data field
	struct node *left;		//왼쪽 link field
	struct node *right;		//오른쪽 link field
} Node;						//struct node를 Node라는 별명을 생성

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;		//Tree의 head
	Node* ptr = NULL;		/* temp */

	printf("[----- [유현진] [2019038006] -----]");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n");
		printf(" Postorder Traversal  = t      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		//원하는 메뉴 입력하는 곳
		printf("Command = ");
		scanf(" %c", &command);

		//입력한 메뉴 문자를 비교하여 해당하는 case문 실행
		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');	  //Quit를 실행하는 문자를 입력하기 전까지 계속 반복

	return 1;
}

int initializeBST(Node** h) {			//초기화
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr)			//중위 순회(LVR)
{
	if (ptr) {								//ptr이 NULL이 이닐 떼
		inorderTraversal(ptr->left);		//왼쪽 순회
		printf("%d ", ptr->key);			//V 출력
		inorderTraversal(ptr->right);		//오른쪽 순회
	}
}
void preorderTraversal(Node* ptr)			//전위 순회(VLR)
{
	if (ptr) {								//ptr이 NULL이 이닐 떼
		printf("%d ", ptr->key);			//V 출력
		preorderTraversal(ptr->left);		//왼쪽 순회
		preorderTraversal(ptr->right);		//오른쪽 순회
	}
}
void postorderTraversal(Node* ptr)			//후위 순회(LRV)
{
	if (ptr) {								//ptr이 NULL이 이닐 떼
		postorderTraversal(ptr->left);		//왼쪽 순회
		postorderTraversal(ptr->right);		//오른쪽 순회
		printf("%d ", ptr->key);			//V 출력
	}
}
int insert(Node* head, int key)			//key값 삽입
{
	Node *find = NULL;					//탐색하고 있는 노드의 위치 가리킬 노드
	Node *temp = (Node *)malloc(sizeof(Node));					//삽입될 새로운 노드 

	//삽입될 노드의 field 값 설정
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	
	if (head == NULL) {					//Tree의 head가 정해져있지 않은 경우
		printf(">>> This Binary Search Tree isn't initialized <<<\n");
		return -1;
	}

	find = head->left;					//Tree의 root노드

	if (find == NULL) {					//아무 노드도 없을 경우 즉, root 노드가 없을 경우
		head->left = temp;				//새로운 root 노드 연결
		temp->key = key;
		printf("Insert %d\n", key);

		return key;
	}

	while (find) {						//head 이외의 노드가 하나 이상일 결우
		if (find->key == key) {			//이미 같은 값이 tree에 들어있는 경우
			printf(">>> Already insert %d in this Tree <<<\n", key);

			return -1;
		}
		else if (find->key < key)		//key이 현재 노드의 값보다 큰 경우
		{
			if (!find->right) {;		//새로운 노드가 삽입될 위치에 도달(현재 노드의 right == NULL)
				find->right = temp;		//현재 노드의 오른쪽에 새로운 노드 삽입
				printf("Insert %d\n", key);

				return key;
			}
			else						//아직 비교할 노드가 남아있을 경우
				find = find->right;		//현재 노드의 오른쪽으로 이동
		}	
		else {							//key가 현재 노드의 값보다 작거나 같은 경우
			if (!find->left) {			//새로운 노드가 삽입될 위치가 도달(현재 노드의 left == NULL)
				find->left = temp;		//현재 노드의 왼쪽에 새로운 노드 삽입
				printf("Insert %d\n", key);

				return key;
			}
			else						//아직 비교할 노드가 남아있을 경우
				find = find->left;		//현재 노드의 왼쪽으로 이동
		}	
	}
}
int deleteLeafNode(Node* head, int key)	//key값을 갖는 노드 삭제
{
	Node *find = NULL;					//탐색하고 있는 노드의 위치를 가리킬 노드
	Node *previous = NULL;				//이전에 탐색했던 노드의 위치를 가리킬 노드

	if (head == NULL) {					//Tree의 head가 정해져있지 않은 경우
		printf(">>> This Binary Search Tree isn't initialized <<<\n");
		return -1;
	}

	find = head->left;					//Tree의 root노드 

	if (find == NULL) {					//트리에 노드가 존재하지 않을 떄
		printf(">>> This tree doesn't have any node <<<\n");
		return -1;
	}

	while (find) {						//트리에 노드가 하나 이상이고 NULL이 아닐 경우
		if ((find->key == key) && (find->left == NULL) && (find->right == NULL)) {	//key과 동일한 필드를 갖고 Leaf Node일 경우
			printf("Delete Leaf Node %d\n", key);
			if (previous->key >= find->key)		//이전 노드보다 현재 노드가 값이 작을 때
				previous->left = NULL;			//현재 노드가 연결되었던 링크 NULL
			else								//이전 노드보다 현재 노드의 값이 클 때
				previous->right = NULL;			//현재 노드가 연결되었던 링크 NULL
			free(find);					//key와 동일한 필드를 갖는 노드 삭제

			return key;
		}
		else if (find->key == key) {	//key와 동일한 값을 갖는 노드이지만 Leaf Node가 아닐 경우
			printf(">>> This value isn't Leaf Node <<<\n");
			return -1;
		}
		else if (find->key < key) {		//key가 현재 노드의 필드보다 값이 클 경우
			previous = find;
			find = find->right;			//현재 노드의 오른쪽으로 이동	
		}
		else if (find->key > key) {		//key가 현재 노드의 필드보다 값이 작을 경우
			previous = find;
			find = find->left;			//현재 노드의 왼쪽으로 이동
		}
			
	}
	//Binary Search Tree에서 key와 같은 값이 없는 경우
	printf(">>> This value dosen't exist in this Binary Tree <<<\n");

	return -1;
}
Node* searchRecursive(Node* ptr, int key)		//동일 key값을 갖는 노드 탐색(재귀적)
{
	if (ptr == NULL)								//key와 동일한 값을 가진 노드가 없을 경우
		return NULL;			
	else if (ptr->key == key)						//key와 동일한 값을 갖는 노드 존재
		return ptr;
	else if (ptr->key > key)						//key가 현재 노드보다 값이 작을 경우
		return searchRecursive(ptr->left, key);		//현재 노드의 왼쪽 탐색 시작
	else											//key가 현재 노드보다 값이 클 경우
		return searchIterative(ptr->right, key);	//현재 노드의 오른쪽 탐색 시작

}
Node* searchIterative(Node* head, int key)		//동일 key값을 갖는 노드 탐색(반복적)
{
	Node *temp = NULL;					//Tree를 탐색할 노드

	if (head == NULL) {					//Tree의 head가 정해져있지 않은 경우
		printf(">>> This Binary Search Tree isn't initialized <<<\n");

		return NULL;
	}

	temp = head->left;					//탐색의 시작 위치

	while (temp) {						//가리키는 노드가 존재할 때
		if (temp->key == key)			//찾고 있는 값과 같은 필드를 갖는 노드를 찾았을 경우
			return temp;
		else if (temp->key > key)		//key가 탐색 중인 노드의 값보다 작을 경우
			temp = temp->left;			//탐색 노드의 왼쪽으로 이동
		else							//key가 탐색 중인 노드의 값보다 큰 경우
			temp = temp->right;			//탐색 노드의 오른쪽으로 이동
	}
	//key와 동일한 값을 갖는 노드가 없는 경우
	return NULL;
}
int freeBST(Node* head)		//노드 해제	
{
	if (head) {				//tree의 head가 NULL이 아닐 경우
		//inorder 순회 방식을 이용하여 맨 밑의 Leaf Node부터 차례로 노드들을 해제
		freeBST(head->left);		
		freeBST(head->right);
		free(head);			//해당 노드에 할당된 동적 메모리 해제
	}
	return 0;
}