#include <stdio.h>
#include <stdlib.h>

//tree를 구성하는 노드
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

//오른쪽 서브트리에서 가장 작은 값을 찾는 함수
Node* search_left(Node* node, Node* previous, int min, int num);
//왼쪽 서브트리에서 가장 큰 값을 찾는 함수
Node* search_right(Node* node, Node* previous, int max, int num);

//스택과 큐의 삽입과 삭제할 때의 조건 함수
int stack_isFull();
int stack_isEmpty();
int queue_isFull();
int queue_isEmpty();

int main()
{
	char command;
	int key;
	//
	Node* head = NULL;

	printf("-------------유현진 2019038006-------------\n");
	do {
		printf("\n----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		//메뉴 선택 시 해당되는 case문을 실행
		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}
void recursiveInorder(Node* ptr)
{
	//inorder 순회방식을 이용
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}
void iterativeInorder(Node* node)
{
	//tree에 들어있는 노드가 없는 경우
	if (node == NULL) {
		printf(">>> This tree doesn't have any node!! <<<\n");
		return;
	}
	//tree에 들어있는 노드가 둘 이상인 경우
	while (1) {
		//root부터 왼쪽 서브트리의 parent 노드 push
		for (; node != NULL; node = node->left)
			push(node);
		//스택의 top에 위치한 값 pop
		node = pop();
		//pop의 반환값이 NULL 즉, 모두 pop하여 스택이 비어있는 경우
		if (!node) {
			//printf(">>> This stack doesn't have any node to pop!! <<<\n");
			break;
		}

		printf(" [%d] ", node->key);
		//왼쪽과 v를 탐색 완료 -> 오른쪽 탐색 시작
		node = node->right;
	}
}
void levelOrder(Node* ptr)
{
	//원헝 큐에서는 front가 가리키는 index의 값은 공백이여야 함
	front = 0; rear = 0;

	//tree에 root노드가 없는 경우 즉, 노드가 존재하지 않음
	if (ptr == NULL) {
		printf(">>> This tree haven't any node!! <<<\n");
		return;
	}
	//root 노드가 존재하는 경우, root노드를 큐에 삽입
	enQueue(ptr);
	//같은 level에 있는 노드를 왼쪽부터 출력
	while (1) {
		//front에 위치한 값 삭제
		ptr = deQueue();
		//삭제할 값이 존재한다먼
		if (ptr) {
			printf(" [%d] ", ptr->key);
			//삭제 노드의 왼쪽과 오른쪽 자식노드를 큐에 삽입
			if (ptr->left != NULL)
				enQueue(ptr->left);
			if (ptr->right != NULL)
				enQueue(ptr->right);
		}
		//삭제할 값이 없음 즉, 모든 노드의 값을 삽입 및 출력을 완료
		else break;
	}
}

int insert(Node* head, int key)
{
	//새로운 key를 삽입할 노드 동적 할당
	Node* newNode = (Node*)malloc(sizeof(Node));			
	newNode->key = key;
	//새로 삽입될 노드는 Leaf Node이기 때문에 양쪽 Link field -> NULL
	newNode->left = NULL;
	newNode->right = NULL;

	if (head == NULL) {
		printf(">>> This tree isn't initialized!! <<<<\n");
		return 0;
	}
	//삽입할 노드가 tree의 첫 노드 즉, root 노드일 때
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}
	//root 노드의 주소 저장
	Node* ptr = head->left;				
	Node* parentNode = NULL;

	while (ptr != NULL) {

		//이미 해당 tree에 key값이 있을 경우(중복 처리)
		if (ptr->key == key) {
			printf(">>> This key already insert!! <<<\n");
			return 1;
		}
		//삽입될 노드의 부모 노드 위치 저장
		parentNode = ptr;				
		
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	//새로운 노드가 삽입될 위치의 부모 노드와 값 비교
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;

	return 1;
}
int deleteNode(Node* head, int key)
{
	Node *find = NULL;
	Node *previous = NULL;
	//바꿀 노드의 위치를 저장
	Node *temp = NULL;
	int search = 0;
	//Tree의 head가 정해져있지 않은 경우
	if (head == NULL) {					
		printf(">>> This Binary Search Tree isn't initialized <<<\n");
		return -1;
	}
	//Tree의 root노드 
	find = head->left;		

	//트리에 노드가 존재하지 않을 떄
	if (find == NULL) {					
		printf(">>> This tree doesn't have any node <<<\n");
		return -1;
	}
	//트리에 노드가 하나 이상이고 NULL이 아닐 경우
	while (find) {		
		//key과 동일한 필드를 갖고 Leaf Node일 경우
		if ((find->key == key) && (find->left == NULL) && (find->right == NULL)) {	
			printf("Delete Leaf Node %d\n", key);
			//이전 노드보다 현재 노드가 값이 작을 때
			if (previous->key >= find->key)		
				//현재 노드가 연결되었던 링크 NULL
				previous->left = NULL;
			//이전 노드보다 현재 노드의 값이 클 때
			else								
				//현재 노드가 연결되었던 링크 NULL
				previous->right = NULL;	
			//key와 동일한 필드를 갖는 노드 삭제
			free(find);					

			return key;
		}
		//key와 동일한 값을 갖는 노드이지만 Leaf Node가 아닐 경우
		else if (find->key == key) {	
			//왼쪽 자식노드가 존재할 때
			if (find->left != NULL) {
				//바꿀 노드의 위치를 왼쪽 서브트리의 가장 큰 노드를 찾음
				temp = search_right(find->left, find, find->left->key, 0);
				//삭제할 위치에 바꿀 값을 삽입
				find->key = temp->key;

				free(temp);
			}
			//key와 동일한 노드와 바꿀 노드의 위치를 오른쪽 서브트리에서 찾음	
			else if (find->right != NULL) {
				//바꿀 노드의 위치를 오른쪽 서브트리의 가장 작은 값을 찾음
				temp = search_left(find->right, find, find->right->key, 0);
				//삭제할 위치에 바꿀 값을 삽입
				find->key = temp->key;
				free(temp);
			}
			return key;
		}
		//key가 현재 노드의 필드보다 값이 클 경우
		else if (find->key < key) {		
			previous = find;
			//현재 노드의 오른쪽으로 이동	
			find = find->right;			
		}
		//key가 현재 노드의 필드보다 값이 작을 경우
		else if (find->key > key) {		
			previous = find;
			//현재 노드의 왼쪽으로 이동
			find = find->left;			
		}

	}
	//Binary Search Tree에서 key와 같은 값이 없는 경우
	printf(">>> This value dosen't exist in this Binary Tree <<<\n");

	return -1;
}
Node* search_left(Node* node, Node* previous, int min, int num) {
	//왼쪽 서브트리에서 편향트리의 중간 노드나 왼쪽의 오른쪽 서브트리에서 왼쪽 노드일 경우
	if (node->left == NULL && node->right != NULL) {
		//편향 트리일 경우
		if (num == 0) {
			previous->right = node->right;
		}
		//왼쪽의 오른쪽 서브트리에서 왼쪽 노드일 경우
		else {
			previous->left = node->right;
		}
		return node;

	}
	//ndoe가 leaf node인 경우
	if (node->left == NULL) {
		if (previous->left != NULL)
			previous->left = NULL;
		return node;
	}
	//현재 노드의 값이 min보다 작을 경우
	else if (min >= node->key) {
		//min값을 update
		min = node->key;
		//node의 왼쪽노드를 탐색
		return search_left(node->left, node, min, num+1);
	}
}
Node* search_right(Node* node, Node* previous, int max, int num) {
	//오른쪽 서브트리에서 편향트리의 중간 노드나 오른쪽의 왼쪽 서브트리에서 오른쪽 노드일 경우
	if (node->right == NULL && node->left != NULL) {
		//편향 트리일 경우
		if (num == 0) {
			previous->left = node->left;
		}
		//오른쪽의 왼쪽 서브트리에서 오른쪽 노드일 경우
		else {
			previous->right = node->left;
		}
		return node;
	}
	//ndoe가 leaf node인 경우
	else if (node->right == NULL) {
		//node의 부모노드의 왼쪽을 NULL
		if (previous->left == node)
			previous->left = NULL;
		//node의 부모노드의 오른쪽을 NULL
		else if (previous->right == node)
			previous->right = NULL;
		
		return node;
	}
	//현재 노드의 값이 max값보다 큰 경우
	else if (max <= node->key) {
		//max값을 update
		max = node->key;
		//node의 오른쪽노드를 탐색
		return search_right(node->right, node, max, num+1);
	}
}
void freeNode(Node* ptr)
{	
	//postorder 방식을 이용하여 tree의 모든 노드의 동적 메모리 해제
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}
int freeBST(Node* head)
{
	//tree에 노드가 존재하지 않을 때
	if (head->left == head) {
		free(head);
		return 1;
	}
	//tree의 root노드 위치 저장
	Node* p = head->left;	
	//tree의 모든 노드의 메모리 해제하는 함수 호출
	freeNode(p);
	//tree의 head노드의 메모리 해제
	free(head);		

	return 1;
}

Node* pop()
{
	Node* element = NULL;
	//스택이 비어있을 경우
	if (stack_isEmpty() == 0) {
		return NULL;
	}
	//top위치의 값을 저장
	element = stack[top];
	//top에 저장된 노드의 주소 삭제
	stack[top--] = NULL;

	return element;
}
void push(Node* aNode)
{
	//스택의 남은 공간이 없을 경우
	if (stack_isFull() == 0) {
		return;
	}
	//top을 이동 후 해당 위치에 aNode 저장
	stack[++top] = aNode;
}

Node* deQueue()
{
	Node* element = NULL;

	//큐가 비어있을 경우
	if (queue_isEmpty() == 0) {
		return NULL;
	}
	//front를 다음 위치로 이동
	front = (front + 1) % MAX_QUEUE_SIZE;
	element = queue[front];
	//front 위치의 값을 NULL로 삭제
	queue[front] = NULL;

	return element;
}
void enQueue(Node* aNode)
{
	//큐가 남은 공간 없이 꽈 차있을 경우
	if (queue_isFull() == 0) {
		//printf("Can't ENQUEUE");
		return NULL;
	}
	//rear의 위치를 다음 위치로 이동
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	//이동한 rear의 위치에 aNode를 삽입
	queue[rear] = aNode;
}

int stack_isFull() {
	//top이 MAX_STACK_SIZE를 넘어갈 경우
	if (top >= (MAX_STACK_SIZE - 1)) {
		//printf(">>> This stack is FULL!! <<<\n");
		return 0;
	}
	//top이 MAX_STACK_SIZE를 넘어가지 않을 경우
	return 1;
}
int stack_isEmpty() {
	//top이 초기설정 값일 경우
	if (top < 0) {
		return 0;
	}
	//top이 초기설정 값이 아닐 경우 즉, 원소 삽입됨
	return 1;
}
int queue_isFull() {
	//rear이 이동할 다음 위치와 현재 front의 위치가 같다면
	if (front == ((rear + 1) % MAX_QUEUE_SIZE)) {
		return 0;
	}
	//rear이 이동할 다음 위치와 현재 front의 위치가 같지 않다면
	return 1;
}
int queue_isEmpty() {
	//rear와 front이 같을 경우 즉, 초기설정과 같다면
	if (front == rear) {
		//printf(">>> This queue is EMPTY!! <<<\n");
		return 0;
	}
	//rear와 front의 위치 이동이 있는 경우
	return 1;
}