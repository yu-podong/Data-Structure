#include<stdio.h>
#include<stdlib.h>

typedef struct Node {		//doubly linked list의 노드를 구성하는 구조체 node 정의
	int key;				//노드의 data field에 해당
	struct Node* llink;		//노드의 왼쪽 링크에 해당
	struct Node* rlink;		//노드의 오른쪽 링크에 해당
} listNode;					//struct Node를 listNode라는 이름으로 사용

typedef struct Head {		//doubly linked list에서 head를 가리킬 구조체 Head 정의
	struct Node* first;		//doubly linked list의 head node를 가리킬 구조체 Node 포인터 변수
}headNode;					//struct Head를 headNode라는 이름으로 사용

int initialize(headNode** h);			//doubly linked list를 초기화하는 함수 원형
int freeList(headNode* h);				//doubly linked list의 노드들이 남아있을 경우 메모리 해제시키는 함수 원형
int insertNode(headNode* h, int key);	//key보다 큰 노드 앞에 새로운 노드를 삽입하는 함수 원형
int insertLast(headNode* h, int key);	//doubly linked list의 마지막 노드를 삽입하는 함수 원형
int insertFirst(headNode* h, int key);	//doubly linked list의 첫번째 노드를 삽입하는 함수 원형
int deleteNode(headNode* h, int key);	//key값을 가진 노드를 삭제하는 함수 원형
int deleteLast(headNode* h);			//doubly linked list의 마지막 노드를 삭제하는 함수 원형
int deleteFirst(headNode* h);			//doubly linked list의 첫번째 노드를 삭제하는 함수 원형
int invertList(headNode* h);			//doubly linked list를 뒤집는 함수 원형

void printList(headNode* h);			//현재 연결 리스트의 상태를 출력하는 함수 원형

int main()
{
	char command;					//사용자가 입력한 메뉴 문자 저장하는 변수
	int key;						//사용자가 입력하는 data 값
	headNode* headnode = NULL;		//doubly linked list의 head를 가리키는 구조체 포인터

	printf("[----- [유현진] [2019038006] -----]\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
		case 'z': case 'Z':					//Initialize 메뉴 실행
			initialize(&headnode);			//doubly linked list 초기화하는 함수 호출
			break;
		case 'p': case 'P':					//Print 메뉴 실행
			printList(headnode);			//현재 이중 연결 리스트의 상태 출력하는 함수 호출
			break;
		case 'i': case 'I':					//Insert Node 메뉴 실행
			printf("Your Key = ");
			scanf("%d", &key);				//삽입하고자 하는 data 값 입력
			insertNode(headnode, key);		//조건에 맞게 새로운 노드 삽입하는 함수 호출
			break;
		case 'd': case 'D':					//Delete Node 메뉴 실행
			printf("Your Key = ");
			scanf("%d", &key);				//삭제하고픈 data 입력
			deleteNode(headnode, key);		//해당 key을 가진 노드 삭제하는 함수 호출
			break;
		case 'n': case 'N':					//Insert Last 메뉴 실행
			printf("Your Key = ");
			scanf("%d", &key);				//삽압하고자 하는 data값 입력
			insertLast(headnode, key);		//doubly linked list의 마지막에 key을 가진 노드를 삽입하는 함수 호출
			break;
		case 'e': case 'E':					//Delete Last 메뉴 실행
			deleteLast(headnode);			//doubly linked list의 마지막 노드를 삭제하는 함수 호출
			break;
		case 'f': case 'F':					//Insert First 메뉴 실행
			printf("Your Key = ");
			scanf("%d", &key);				//삽입하고자 하는 date 값 입력
			insertFirst(headnode, key);		//doubly linked list의 첫번째 노드를 삽입하는 함수 호출
			break;
		case 't': case 'T':					//Delete First 메뉴 실행
			deleteFirst(headnode);			//doubly linked list의 첫번째 노드를 삭제하는 함수 호출
			break;
		case 'r': case 'R':					//Invert 메뉴 실행
			invertList(headnode);			//doubly linked list를 뒤집는 함수 호출
			break;
		case 'q': case 'Q':					//Quit 메뉴 실행
			freeList(headnode);				//doubly linked list의 모든 노드와 head의 메모리를 해제하는 함수 호출
			break;
		default:							//이외의 다른 문자 입력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		//ERROR message 출력
			break;
		}

	} while (command != 'q' && command != 'Q');		//Quit 메뉴 실행 전까지 loop

	return 1;
}
int initialize(headNode** h) {									//이중 포인터를 사용하여 headnode 수정
	if (*h != NULL)												//doubly linked list의 head를 가리키는 주소가 있다면
		freeList(*h);											//doubly linked list의 모든 노드 및 head의 메모리를 해제시키는 함수 호출
	headNode *temp = (headNode *)malloc(sizeof(headNode));		//headNode에 대한 동적 할당
	temp->first = NULL;
	*h = temp;													//새로 만든 head의 주소를 저장

	return 0;
}
int freeList(headNode* h) {					//doubly linked list와 관련된 메모리 모두 해제
	listNode *now = h->first;				//doubly linked list의 headnode 접근
	for (; now != NULL; now = now->llink)
		free(now);							//doubly linked list의 모든 노드 해제
	free(h);								//doubly linked list의 head 해제

	return 0;
}
void printList(headNode* h) {
	int i = 0;
	listNode* p;							//doubly linked list의 노드에 접근할 구조체 포인터

	printf("\n---PRINT\n");

	if (h == NULL) {						//doubly linked list가 선언되지 않은 경우
		printf("Nothing to print....\n");	//ERROR message 출력
		return;
	}

	p = h->first;							//doubly linked list의 첫번째 노드 접근

	while (p != NULL) {						//doubly linked list의 마지막 노드에 다다를때까지
		printf("[ [%d]=%d ] ", i, p->key);	//해당 노드의 date 출력
		p = p->rlink;						//다음 노드
		i++;								//리스트 노드의 개수 count
	}

	printf("  items = %d\n", i);			//현재 리스트에 연결된 노드의 개수 출력
}
int insertLast(headNode* h, int key) {											//headnode의 값 변경 x
	listNode *temp = (listNode *)malloc(sizeof(listNode));						//임의의 노드 생성
	listNode *now = NULL;														//doubly linked list에 접근할 노드 생성
	if (h == NULL) {															//doubly linked list의 head 즉, 초기화된 리스트가 없다면
		printf(">>> This doubly linked list is not initialization! <<<\n");		//ERROR message 출력
		return -1;		//비정상 종료 표현
	}

	temp->key = key;															//임의의 노드에 key 저장
	now = h->first;																//doubly linked list의 첫번째 노드에 접근
	if (now == NULL) {															//현재 리스트의 노드가 존재X
		insertFirst(h, key);													//리스트에 첫번째 노드를 삽입하는 함수 호출
		return 0;		//정상 종료 표현
	}
	for (; now->rlink != NULL; now = now->rlink);								//마지막 노드에 도달
	temp->rlink = NULL;															//임의의 노드가 마지막 노드이기에 NULL
	temp->llink = now;															//삽입 전 마지막 노드와 임의의 노드의 왼쪽 노드 연결
	now->rlink = temp;															//삽입 전 마지막 노드의 오른쪽 노드와 임의의 노드 연결

	printf("Input Last Node %d \n", key);

	return key;		//정상 종료 표현
}
int deleteLast(headNode* h) {													//headnode의 값 변경 X
	listNode *now = NULL;														//doubly linked list에 접근할 노드 생성
	if (h == NULL) {															//doubly linked list의 head 즉, 초기화된 리스트 존재X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	if (h->first == NULL) {														//초기화된 리스트에 노드X
		printf(">>> This doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}
	now = h->first;																//doubly linked list의 첫번째 노드에 접근ㄴ
	for (; now->rlink != NULL; now = now->rlink);								//마지막 노드에 도달
	if (now == h->first)														//리스트에 노드가 단 한 개
		h->first = NULL;														//삭제 후 연결할 노드 x -> NULL
	else																		//리스트에 노드가 두 개 이상
		now->llink->rlink = NULL;												//마지막 노드의 이전 노드의 왼쪽 링크에 연결될 노드 x -> NULL
	free(now);																	//삭제 노드의 메모리 해제

	printf("Delete Last Node\n");

	return 0;		//정상 종료 표현
}
int insertFirst(headNode* h, int key) {											//headnode의 값 변경 X
	listNode *temp = (listNode *)malloc(sizeof(listNode));						//임의의 노드 생성

	if (h == NULL) {															//초기화된 리스트 존재 X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	temp->key = key;															//임의의 노드에 key값 저장
	if (h->first == NULL) {														//리스트의 노드가 단 한 개
		h->first = temp;														//doubly linked list의 headnode를 temp로 가리킴
		temp->llink = temp->rlink = NULL;										//temp의 왼쪽 노드와 오른쪽 노드 모두 가리킬 노드X -> NULL
	}
	else {																		//리스트이 노드가 두 개 이상
		temp->llink = NULL;														//삽입 노드의 왼쪽은 가리킬 노드X -> NULL
		h->first->llink = temp;													//삽입 전 첫번째 노드의 왼쪽 노드를 temp와 연결
		temp->rlink = h->first;													//삽입할 노드의 오른쪽을 삽입 전 첫번째 노드와 연결
		h->first = temp;														//doubly linked list의 첫번째 노드를 삽입 노드로 변경
	}
	printf("Insert First Node %d\n", key);

	return key;		//정상 종료 표현
}
int deleteFirst(headNode* h) {													//headnode의 값 변경 x
	listNode *now = NULL;

	if (h == NULL) {															//초기화된 리스트 존재 X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	if (h->first == NULL) {														//리스트의 노드 존재 X
		printf(">>> This doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}
	now = h->first;																//doubly linked list의 노드에 접근할 구조체 포인터
	h->first = now->rlink;														//doubly linked list의 첫번째 노드를 삭제할 노드의 오른쪽 노드와 연결
	free(now);																	//삭제 노드의 메모리 해제

	printf("Delete First Node\n");
	return 0;		//정상 종료 표현
}
int invertList(headNode* h) {													//headnode의 값 변경 X
	listNode *tail, *mid = NULL, *now = NULL;

	if (h == NULL) {															//초기화된 리스트 존재 X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	if (h->first == NULL) {														//리스트의 노드 존재 X
		printf(">>> This doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}
	now = h->first;						//doubly linked list의 첫번째 노드에 접근
	for (; now != NULL;) {				//모든 노드를 거쳐 리스트를 벗어날 떄 까지
		tail = mid;						//연결될 노드의 위치 저장
		mid = now;						//연결해야하는 노드의 위치 저장
		now = now->rlink;				//링크 변경 전 다음 노드의 위치 저장
		mid->rlink = tail;				//기존의 오른쪽 링크를 왼쪽 링크가 가리키는 쪽으로 연결
		mid->llink = now;				//기존의 왼쪽 링크를 오른쪽 링크가 가리키는 쪽으로 연결
	}
	h->first = mid;						//doubly linked list의 첫번째 노드를 뒤집기 전의 마지막 노드로 변경

	printf("Invert this doubly linked list!\n");
	return 0;		//정상 종료 표현
}
int insertNode(headNode* h, int key) {											//headnod의 값 변경X
	listNode *temp = (listNode *)malloc(sizeof(listNode));						//임의의 노드 생성
	listNode *previous = NULL, *now = NULL;										//접근 중인 노드의 이전 노드 접근할 포인터, doubly linked list의 노드에 접근할 포인터 선언
	temp->key = key;															//임의의 노드에 key값 저장
	if (h == NULL) {															//초기화된 리스트 존재 X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	else if (h->first == NULL)													//리스트의 노드가 존재X
		insertFirst(h, key);													//첫번째 노드를 삽입하는 함수 호출
	else {																		//리스트의 노드가 두 개 이상
		now = h->first;															//doubly linked list의 첫번째 노드에 접근
		for (; now != NULL; previous = now, now = now->rlink) {					//마지막 노드까지 접근
			if (now->key >= temp->key && now == h->first) {						//접근 노드의 값보다 작고 현재 노드가 첫번째 노드
				temp->llink = NULL;												//삽입할 노드가 가리킬 노드 존재 X -> NULL
				temp->rlink = h->first;											//삽입 노드의 오른쪽을 삽입 전 첫번째 노드와 연결
				h->first = temp;												//doubly linked list의 첫번째 노드를 삽입 노드로 변경
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
		temp->llink = previous;					//삽입 전 마지막 노드와 삽입 노드의 왼쪽을 연결
		temp->rlink = NULL;						//삽입 노드의 오른쪽은 가리킬 노드 X -> NULL
		previous->rlink = temp;					//삽입 전 마지막 노드의 오른쪽과 삽입 노드를 연결
		printf("Insert %d\n", key);

		return key;		//정상 종료 표현
	}
}
int deleteNode(headNode* h, int key) {											//headnode의 값 변경X
	listNode *now = NULL;														//doubly linked list의 노드에 접근할 구조체 포인터

	if (h == NULL) {															//초기화된 리스트 존재 X
		printf(">>> This doubly linked list is not initialization! <<<\n");
		return -1;		//비정상 종료 표현
	}
	if (h->first == NULL) {														//리스트의 노드 존재 X
		printf(">>> This doubly linked list don't have any node! <<<\n");
		return -1;		//비정상 종료 표현
	}
	now = h->first;											//doubly linked list의 첫번재 노드에 접근

	for (; now != NULL; now = now->rlink) {					//마지막 노드까지 접근
		if (now->key == key && now == h->first) {			//리스트의 첫번째 노드와 삭제할 값이 same
			h->first = now->rlink;							//doubly linked list의 첫번째 노드를 삭제 노드의 다음 노드로 변경
			if (now->rlink != NULL)							//리스트의 노드가 두 개 이상
				now->rlink->llink = now->llink;				//삭제 노드의 다음 노드의 왼쪽을 삭제 노드의 왼쪽과 연결
			free(now);										//삭제 노드의 메모리 해제
			printf("Delete %d\n", key);

			return key;		//정상 종료 표현
		}
		else if (now->key == key) {							//첫번째 이후 노드와 삭제할 값이 same
			now->llink->rlink = now->rlink;					//삭제 노드의 이전의 오른쪽을 삭제 노드의 오른쪽과 연결
			if (now->rlink != NULL)							//삭제 노드가 doubly linked list의 마지막 노드가 아님
				now->rlink->llink = now->llink;				//삭제 노드의 다음의 왼쪽을 삭제 노드의 왼쪽과 연결
			free(now);										//삭제 노드의 메모리 해제
			printf("Delete %d\n", key);

			return key;		//정상 종료 표현
		}
	}
	printf(">>> Not found %d in doubly linked list<<<\n", key);

	return -1;	//비정상 종료 표현
}
