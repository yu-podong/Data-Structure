#include<stdio.h>
#include<stdlib.h>

typedef struct Node {		//circular doubly linked list의 노드를 구성하는 구조체
	int key;				//data field
	struct Node* llink;		//circular doubly linked list의 왼쪽 link field
	struct Node* rlink;		//circular doubly linked list의 오른쪽 link field
} listNode;					//struct Node를 listNode라는 이름으로 사용
	
int initialize(listNode** h);			//circular doubly linked list를 초기화하는 함수 
int freeList(listNode* h);				//circular doubly linked list의 모든 노드의 메모리를 해제하는 함수
int insertLast(listNode* h, int key);	//circular doubly linked list의 마지막 노드를 추가하는 함수
int deleteLast(listNode* h);			//circular doubly linked list의 마지막 노드를 삭제하는 함수
int insertFirst(listNode* h, int key);	//circular doubly linked list의 첫번째 노드를 추가하는 함수
int deleteFirst(listNode* h);			//circular doubly linked list의 첫번째 노드를 삭제하는 함수
int invertList(listNode* h);			//circular doubly linked list를 반전시키는 함수 

int insertNode(listNode* h, int key);	//circular doubly linked list 중에서 key를 삽입할 조건에 맞게 새로운 node를 추가하는 함수
int deleteNode(listNode* h, int key);	//circular doubly linked list 중에서 key과 동일한 data field를 갖는 node를 삭세하는 함수

void printList(listNode* h);			//circular doubly linked list의 상태를 출력하는 함수

int main()
{
	char command;					//사용자가 입력한 메뉴 문자 저장
	int key;						//사용자가 입력한 key값 입력
	listNode* headnode = NULL;		//headnode를 선언하고 NULL로 초기화

	printf("[----- [유현진] [2019038006] -----]");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);	

		switch (command) {				
		case 'z': case 'Z':				
			initialize(&headnode);		
			break;			
		case 'p': case 'P':				
			printList(headnode);		
			break;
		case 'i': case 'I':				
			printf("Your Key = ");		
			scanf("%d", &key);
			insertNode(headnode, key);	
			break;
		case 'd': case 'D':	
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {					//headnode의 값을 변경할 수 있는 함수

	if (*h != NULL)								//headnode가 이전에 초기화를 했을 경우
		freeList(*h);							//리스트의 모든 노드의 메모리를 해제
		
	*h = (listNode*)malloc(sizeof(listNode));	//haadnode의 값을 새로운 동적 메모리의 주소로 change
	//circular를 구현하기 위해 양쪽 link field를 자기자신을 가리키도록 함
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;		//headnode의 data field는 큰 의미가 없으므로 의미없는 값 저장
	return 1;	//정상 종료 표현
}
int freeList(listNode* h) {
	listNode *now = h;						//circular doubly linked list의 headnode 접근
	if (h->rlink == h)						//리스트의 headnode밖에 없을 경우
		free(now);
	else {									//리스트에 headnode 제외 하나 이상의 노드 존재
		for (; now != NULL; now = now->rlink)	//마지막 노드까지 접근
			free(now);							//circular doubly linked list의 모든 노드 해제
	}
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {		//headnode가 초기화되지 않았을 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;			//리스트의 의미있는 data field를 가진 node에 접근

	while (p != NULL && p != h) {				//p가 circular의 특성에 의해 headnode에 접근하기 전까지 
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;							//현재 노드의 다음 노드에 접근
		i++;
	}
	printf("  items = %d\n", i);	//data field를 갖는 노드의 개수(headnode 제외)

	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);	//해당 노드의 link field가 가리키는 node의 주소 출력

	i = 0;
	p = h->rlink;					//리스트의 의미있는 data field를 가진 node에 접근
	while (p != NULL && p != h) {				//p가 circular의 특성에 의해 headnode에 접근하기 전까지 
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);		//해당 node의 모든 정보 출력
		p = p->rlink;   //현재 노드의 다음 노드 접근
		i++;
	}
}
int insertLast(listNode* h, int key) {
	listNode *now = NULL;	//접근 노드를 선언 및 초기화
	listNode *temp = (listNode *)malloc(sizeof(listNode));		//삽입 노드를 동적 할당
	temp->key = key;

	if (h == NULL) {				//circular doubly linked list의 headnode 즉, 초기화된 리스트가 없다면
		printf(">>> This doubly linked list is not initialization! <<<\n");	
		return -1;		//비정상 종료 표현
	}
	now = h;			//headnode에 접근
	for (; now->rlink != h; now = now->rlink);	//리스트의 마지막 노드에 접근하기 위한 for문
	temp->llink = now;
	temp->rlink = now->rlink;					//circular를 구현하기 위해 삽입 노드와 headnode를 연결
	h->llink = temp;							//circular를 구현하기 위해 headnode의 왼쪽과 삽입 노드를 연결
	now->rlink = temp;

	return 1;
}
int deleteLast(listNode* h) {
	listNode *now = h;		//접근 노드를 선언 및 초기화

	if (h == NULL) {				//circular doubly linked list의 headnode 즉, 초기화된 리스트가 없다면
		printf(">>> This circular doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	else if (h->rlink == h) {		//리스트에 headnode만 존재할 때
		printf(">>> This circular doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}
	//리스트에 headnode 제외 하나 이상의 노드가 존재할 때
	for (; now->rlink != h; now = now->rlink);	//now가 마지막 노드를 가리키도록 하는 for문
	now->llink->rlink = h;						//삭제 후의 마지막 노드의 오른쪽을 원형 리스트를 구현하기 위해 headnode와 연결
	h->llink = now->llink;						//삭제 후의 마지막 노드의 왼쪽을 headnode의 왼쪽과 연결
	free(now);	

	printf("Delete Last Node!!\n");

	return 1;
}
int insertFirst(listNode* h, int key) {
	listNode *temp = (listNode *)malloc(sizeof(listNode));	//새로운 key를 갖는 node를 가질 temp를 동적 할당
	temp->key = key;

	if (h == NULL) {				//circular doubly linked list의 headnode 즉, 초기화된 리스트가 없다면
		printf(">>> This circular doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	else if (h->rlink == h) {		//리스트에 headnode만 존재할 때
		h->rlink = temp;
		temp->llink = h;
		temp->rlink = h;			//temp가 마지막 노드이므로 삽입 노드의 오른쪽을 headnode와 연결 
		h->llink = temp;			//headnode의 왼쪽을 삽입노드와 연결
	}
	else {							//리스트에 headnode 제외 하나 이상의 노드가 존재할 때
		temp->llink = h;
		temp->rlink = h->rlink;	
		h->rlink->llink = temp;
		h->rlink = temp;
	}

	return 1;
}
int deleteFirst(listNode* h) {
	listNode *now = NULL;
	if (h == NULL) {				//circular doubly linked list의 headnode 즉, 초기화된 리스트가 없다면
		printf(">>> This circular doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	else if (h->rlink == h) {		//headnode의 오른쪽이 자기자신을 가리킬 때
		printf(">>> This circular doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}	
	else {							//headnode 제외 하나 이상의 노드 존재할 때
		now = h->rlink;									//now를 실제 의미있는 value를 갖는 노드의 주소 저장
		h->rlink = now->rlink;							//circular doubly linked list의 첫번째 노드를 삭제 노드의 다음 노드로 변경
		if (now->rlink != h)							//리스트의 노드가 두 개 이상
			now->rlink->llink = now->llink;				//삭제 노드의 다음 노드의 왼쪽을 삭제 노드의 왼쪽과 연결
		else											//리스트의 노드가 한 개일 때
			h->llink = h;								//headnode의 왼쪽을 자기자신을 가리키도록 함
		free(now);										//삭제 노드의 메모리 해제
		printf("Delete First Node\n");

		return 1;		//정상 종료 표현
	}
}
int invertList(listNode* h) {
	listNode *previous = h , *now = NULL;		//이전 노드와 현재 노드를 가리킬 노드 선언 및 초기화

	if (h == NULL) {							//circular doubly linked list의 headnode 즉, 초기화된 리스트가 없다면
		printf(">>> This circular doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	else if (h->rlink == h) {					//리스트에 headnode를 제외한 노드가 없다면
		printf(">>> This circular doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}

	for (; previous->rlink != h; previous = previous->rlink);	//이전 노드가 마지막 노드를 가리킬 때까지 for문 실행
	for (now = h; previous->llink != h; now = now->llink) {		//invert를 하기 위해 now를 headnode부터 접근
		now->llink = now->rlink;								//현재 노드의 왼쪽을 현재 노드의 오른쪽을 가리키도록 함
		now->rlink = previous;									//현재 노드의 오른쪽을 이전 노드를 가리키도록함
		previous = now;											//이전 노드를 현재 노드로 change
	}

	return 0;		//정상 종료 표현
}
int insertNode(listNode* h, int key) {
	listNode *temp = (listNode *)malloc(sizeof(listNode));						//임의의 노드 생성
	listNode *now = NULL;														//circular doubly linked list의 노드에 접근할 포인터 선언
	temp->key = key;															//임의의 노드에 key값 저장
	if (h == NULL) {															//초기화된 리스트 존재 X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	else if (h->rlink == h)														//리스트에 headnode만 존재
		insertFirst(h, key);													//첫번째 노드를 삽입하는 함수 호출
	else {																		//리스트의 노드가 두 개 이상
		now = h->rlink;															//circular doubly linked list의 headnode의 오른쪽 노드에 접근
		for (; now != h; now = now->rlink) {									//마지막 노드까지 접근
			if (now->key >= temp->key && now == h->rlink) {						//접근 노드의 값보다 작고 현재 노드가 첫번째 노드
				temp->llink = h;												//삽입할 노드의 왼쪽을 headnode와 연결
				temp->rlink = now;												//삽입 노드의 오른쪽을 삽입 전 첫번째 노드와 연결
				h->rlink = temp;												//circular doubly linked list의 headnode의 오른쪽을 삽입 노드와 연결
				now->llink = temp;												//현재 노드의 왼쪽을 삽입 노드와 연결
				printf("Insert %d \n", key);

				return key;		//정상 종료 표현
			}
			else if (now->key >= temp->key) {									//현재 노드가 첫번째 노드가 아니면서 현재 노드의 값보다 작은 경우
				temp->llink = now->llink;										//삽입 노드의 왼쪽을 삽입 전의 접근 노드의 왼쪽과 연결
				temp->rlink = now;												//삽입 노드의 오른쪽을 현재 노드와 연결
				now->llink->rlink = temp;										//삽입 전 접근 노드의 왼쪽과 삽입 노드와 연결
				now->llink = temp;												//현재 노드의 왼쪽과 삽입 노드를 연결
				printf("Insert %d\n", key);

				return key;		//정상 종료 표현
			}
		}
		//모든 노드보다 값이 클 경우
		temp->llink = h->llink;					//삽입 전 마지막 노드와 삽입 노드의 왼쪽을 연결
		temp->rlink = h;						//삽입 노드의 오른쪽을 headnode와 연결
		h->llink->rlink = temp;					//삽입 전 마지막 노드의 오른쪽과 삽입 노드를 연결
		h->llink = temp;						//headnode의 왼쪽을 삽입 노드와 연결
		printf("Insert %d\n", key);

		return key;		//정상 종료 표현
	}
}
int deleteNode(listNode* h, int key) {
	listNode *now = NULL;							//circular doubly linked list의 노드에 접근할 구조체 포인터

	if (h == NULL) {								//초기화된 리스트 존재 X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	if (h->rlink == h) {							//리스트에 headnode만 존재
		printf(">>> This doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}
	now = h->rlink;											//circular doubly linked list의 headnode의 오른쪽의 노드 주소를 삽입

	for (; now != h; now = now->rlink) {					//마지막 노드까지 접근
		if (now->key == key && now == h->rlink) {			//리스트의 첫번째 노드와 삭제할 값이 same
			h->rlink = now->rlink;							//circular doubly linked list의 첫번째 노드를 삭제 노드의 다음 노드로 변경
			if (now->rlink != h)							//리스트의 노드가 두 개 이상
				now->rlink->llink = now->llink;				//삭제 노드의 다음 노드의 왼쪽을 삭제 노드의 왼쪽과 연결
			else											//리스트의 노드가 하나일 때
				h->llink = h;								//headnode의 왼쪽 노드가 자기 자신을 가리키도록 함
			free(now);										//삭제 노드의 메모리 해제
			printf("Delete %d\n", key);

			return key;		//정상 종료 표현
		}
		else if (now->key == key) {							//첫번째 이후 노드와 삭제할 값이 same
			now->llink->rlink = now->rlink;					//삭제 노드의 이전의 오른쪽을 삭제 노드의 오른쪽과 연결
			if (now->rlink != h)							//삭제 노드가 circular doubly linked list의 마지막 노드가 아님
				now->rlink->llink = now->llink;				//삭제 노드의 다음의 왼쪽을 삭제 노드의 왼쪽과 연결
			else											//삭제 노드가 circular doubly linked list의 마지막 노드일 때
				h->llink = now->llink;						//headnode의 왼쪽 노드들 삭제 노드의 왼쪽 노드와 연결
			free(now);										//삭제 노드의 메모리 해제
			printf("Delete %d\n", key);

			return key;		//정상 종료 표현
		}
	}
	printf(">>> Not found %d in doubly linked list<<<\n", key);

	return -1;	//비정상 종료 표현
}

