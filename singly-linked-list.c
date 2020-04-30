#include<stdio.h>
#include<stdlib.h>

typedef struct Node {		//연결 리스트의 노드를 구성하는 구조체 Node 정의
	int key;				//data field에 해당하는 정수형 변수
	struct Node* link;		//link field에 해당하는 구조체 포인터 변수
} listNode;					//struct Node를 listNode라는 별명을 붙임

typedef struct Head {		//연결 리스트의 첫번째 노드를 가리킬 구조체 Head 정의
	struct Node* first;		//struct Node를 가리키는 구조체 포인터 변수 first
}headNode;					//struct Head를 headNode라는 별명을 붙임


/* 함수 리스트 */
headNode* initialize(headNode* h);		//연결 리스트를 초기화하는 initialize 함수 원형 선언
int freeList(headNode* h);				//기존 리스트에 할당되었던 노드들을 초기화하는 freeList 함수 원형 선언

int insertFirst(headNode* h, int key);	//연결 리스트의 첫번째 노드 앞에 새로운 노드를 삽입하는 insertFirst 함수 원형 선언
int insertNode(headNode* h, int key);	//노드의 data field값을 비교하여 key값보다 큰 data를 가진 노드 앞에 삽입하는 insertNode 함수 원형 선언
int insertLast(headNode* h, int key);	//연결 리스트의 끝에 새로운 노드를 삽입하는 insertLast 함수 원형 선언

int deleteFirst(headNode* h);			//연결 리스트의 첫번째 노드를 제거하는 deleteFirst 함수 원형 선언
int deleteNode(headNode* h, int key);	//노드 중에서 key값과 동일한 data field를 가지는 노드를 제거하는 deleteNode 함수 원형 선언
int deleteLast(headNode* h);			//연결 리스트의 마지막 노드를 제거하는 deleteLast 함수 원형 선언
int invertList(headNode* h);			//연결 리스트를 역순으로 바꿔주는 invertList 함수 원형 선언

void printList(headNode* h);			//연결 리스트에 저장된 노드들의 data field값을 출력하는 printList 함수 원형 선언

int main()
{
	char command;						//사용자가 입력한 메뉴 문자를 저장할 문자형 변수 선언
	int key;							//노드의 data field에 들어갈 값 또는 비교할 값을 저장하는 정수형 변수 선언
	headNode* headnode = NULL;			//연결 리스트의 첫번째 노드를 가리킬 구조페 포인터 변수 선언 및 NULL로 초기화

	printf("[----- [유현진] [2019038006] -----]\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);					//실행하길 원하는 메뉴 입력 및 command에 저장

		switch (command) {						//command의 값을 case별로 비교하여 해당하는 case문 즉, 해당 메뉴를 실행
		case 'z': case 'Z':						//command가 Initialize 메뉴를 실행시키는 z or Z일 경우
			headnode = initialize(headnode);	//intialize 함수를 호출하여 리스트를 초기화시키는 동적 메모리의 주소를 headnode에 저장
			break;								//switch문 탈출
		case 'p': case 'P':						//command가 Print 메뉴를 실행시키는 p or P일 경우
			printList(headnode);				//연결 리스트의 전체 노드의 data field값을 출력하는 printList 함수 호출
			break;								//switch문 탈출
		case 'i': case 'I':						//command가 Insert Node 메뉴를 실행시키는 i or I일 경우
			printf("Your Key = ");
			scanf("%d", &key);					//삽입할 노드의 data field값 입력 및 key에 저장
			insertNode(headnode, key);			//insertNode 함수를 호출하여 오름차순으로 새로운 노드 삽입
			break;								//switch문 탈출
		case 'd': case 'D':						//command가 Delete Node 메뉴를 실행시키는 d or D일 경우
			printf("Your Key = ");
			scanf("%d", &key);					//삭제하고픈 노드의 data field값 입력 및 key에 저장
			deleteNode(headnode, key);			//deleteNode 함수를 호출하여 key값 같은 data field를 가진 노드를 삭제
			break;								//switch문 탈출
		case 'n': case 'N':						//command가 Insert Last 메뉴를 실행시키는 n or N일 경우
			printf("Your Key = ");	
			scanf("%d", &key);					//연결 리스트의 마지막에 삽입할 노드의 data field값을 입력 및 key에 저장
			insertLast(headnode, key);			//insertLast 함수를 호출하여 연결 리스트의 마지막에 key값을 가진 새로운 노드 삽입
			break;								//switch문 탈출
		case 'e': case 'E':						//command가 Delete Last 메뉴를 실행시키는 e or E일 경우
			deleteLast(headnode);				//deleteLast 함수를 호출하여 연결 리스트의 마지막 노드를 삭제
			break;								//switch문 탈출
		case 'f': case 'F':						//command가 Insert First 메뉴를 실행시키는 f or F일 경우
			printf("Your Key = ");
			scanf("%d", &key);					//연결 리스트의 첫번째 노드로 삽입할 data field의 값을 입력 및 key에 저장
			insertFirst(headnode, key);			//insertFirst 함수를 호출하여 연결 리스트의 첫번째 노드 앞에 key값을 가진 새로운 노드 삽입
			break;								//switch문 탈출
		case 't': case 'T':						//command가 Delete First 메뉴를 실행시키는 t or T일 경우
			deleteFirst(headnode);				//deleteFirst 함수를 호출하여 연결 리스트의 첫번째 노드를 삭제
			break;								//switch문 탈출
		case 'r': case 'R':						//command가 Invert List 메뉴를 실행시키는 r or R일 경우
			invertList(headnode);				//invertList 함수를 호출하여 연결 리스트를 역순으로 만듦
			break;								//switch문 탈출
		case 'q': case 'Q':						//command가 Quit 메뉴를 실행시키는 q or Q일 경우
			freeList(headnode);					//freeList 함수를 호출하여 연결 리스트를 해제
			break;								//switch문 탈출
		default:								//command가 위의 경우 이외의 문자를 입력했을 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");	//ERROR message 출력
			break;								//switch문 탈출
		}

	} while (command != 'q' && command != 'Q');	//사용자가 q or Q를 입력하기 전까지 do-while문 계속 실행

	return 1;
}
headNode* initialize(headNode* h) {								//연결 리스트의 head를 가리키는 구조체 포인터 변수를 이용하여 연결 리스트를 초기화하는 함수 정의
	if (h != NULL)												//만약 h가 연결 리스트의 head를 가리키고 있다면
		freeList(h);											// freeList 함수 호출하여 초기화 진행

	headNode* temp = (headNode*)malloc(sizeof(headNode));		//연결 리스트의 head의 주소를 가리킬 수 있는 동적 메모리의 주소를 temp에 저장
	temp->first = NULL;											//temp가 NULL을 대입하여 아직 아무것도 pointing하고 있지 않음

	return temp;												//temp에 저장된 주소를 반환
}
int freeList(headNode* h) {										//연결 리스트의 head를 가리키는 구조체 포인터 변수를 이용하여 각각의 노드의 메모리 해제
	listNode* p = h->first;										//연결 리스트의 head의 노드 주소를 p에 저장

	listNode* prev = NULL;										//메모리 해제할 노드의 주소를 저장하는 구조체 변수를 선언 및 NULL로 초기화
	while (p != NULL) {											//연결 리스트의 마지막 노드에 도달하기 전까지
		prev = p;												//prev에 p의 주소를 저장하여 현재 리스트의 head 노드를 point
		p = p->link;											//삭제할 노드의 다음 노드의 주소를 p에 저장
		free(prev);												//prev의 주소에 해당하는 노드의 동적 메모리 해제
	}
	free(h);													//연결 리스트의 head를 가리키고 있던 구조체 포인터 해제

	return 0;
}
int insertFirst(headNode* h, int key) {							//연결 리스트의 head와 삽입할 key값을 이용해 새로운 노드를 첫번째 노드로 삽입하는 함수 정의
	listNode* node = (listNode*)malloc(sizeof(listNode));		//listNode 크기만큼의 동적 메모리의 주소를 받아서 새로운 노드로 사용

	if (h == NULL) {											//연결 리스트의 초기화가 일어나지 않아 head의 주소가 NULL이라면
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message 출력
		return -1;
	}
	node->key = key;											//새로운 노드의 data field에 key값 저장
	node->link = h->first;										//새로운 노드가 연결 리스트의 head 노드와 연결 if. head 노드가 없다면 NULL 저장
	h->first = node;											//연결 리스트의 첫번째 노드가 바뀌었으므로 head 노드를 새로운 노드로 변경

	return 0;
}
int insertNode(headNode* h, int key) {								//연결 리스트의 head와 삽입할 key값을 이용하여 key값보다 큰 data를 가진 노드 앞에 삽입하는 함수 정의
	listNode *search = (listNode *)malloc(sizeof(listNode));		//listNode 크기만큼의 동적 메모리를 할당받아 새로운 노드로 사용
	listNode *previous = NULL;										//현재 노드의 이전 노드로 사용할 포인터의 값을 NULL로 초기화
	listNode *now = NULL;											//head 노드부터 현재 가리키고 있는 노드를 표현하기 위한 포인터 선언 및 초기화
	search->key = key;												//삽입할 노드의 data field에 key값을 저장

	if (h == NULL) {												//연결 리스트의 초기화가 일어나지 않아 head의 주소가 NULL이라면
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message 출력
		return -1;
	}
	else if (h->first == NULL) {									//만약 head 노드의 주소가 NULL 즉, 연결 리스트에 노드가 존재하지 않다면
		search->link = NULL;										//처음이자 마지막 노드이므로 삽입한 노드를 다음으로 가리킬 노드가 없으므로 NULL 저장
		h->first = search;											//search가 첫번째 노드가 되었으므로 head 노드를 search로 변경

		return key;													//key값 반환
	}
	else {															//연결 리스트에 노드가 하나 이상이 있을 경우
		now = h->first;												//head 노드부터 현재 가리키고 있는 노드를 표현하기 위해 haed 노드의 주소 저장
		for (; now != NULL; previous = now, now = now->link) {		//현재 가리키고 있는 위치가 마지막 노드를 벗어나기 전까지 계속 다음 노드를 가리키기 위한 for문
			if (now == h->first && key <= now->key) {				//현재 위치가 head 노드와 같고 삽입하고자 하는 key값이 head 노드의 data보다 작다면
				search->link = now;									//삽입할 노드에 현재 노드의 주소를 저장하여 head 노드를 가리키도록 함
				h->first = search;									//head 노드에 삽입할 노드의 주소를 저장하여 그 노드를 가리키도록 하여 연결 리스트에 삽입

				return key;											//key값 반환
			}
			else if (key <= now->key) {								//현재 노드의 data보다 삽입하고자 하는 key가 더 작을 경우
				search->link = now;									//삽입할 노드가 현재 노드의 앞에 위치해야 하므로 삽입할 노드가 현재 노드의 주소를 저장하여 pointing
				previous->link = search;							//현재 노드의 이전 노드는 삽입할 노드를 가리켜야 하므로 search의 주소 저장

				return key;											//key값 반환
			}
		}
		if (previous->key <= key) {									//함수가 return되지 않고 for문을 탈출했다는 것은 key값이 모든 노드의 data보다 클 경우에 해당하는 조건문
			search->link = now;										//삽입할 노드가 연결 리스트의 마지막에 삽입되야 하므로 현재 NULL값인 now의 주소를 저장
			previous->link = search;								//현재 노드의 이전 노드는 삽입할 노드를 가리켜야 하므로 search의 주소 저장

			return key;												//key값 반환
		}
	}
}int insertLast(headNode* h, int key) {								//연결 리스트의 head와 삽입할 key값을 이용해 새로운 노드를 마지막 노드 뒤에 삽입할 함수 정의
	listNode *input = (listNode *)malloc(sizeof(listNode));			//listNode 크기만큼의 동적 메모리의 주소를 받아서 새로운 노드로 사용
	listNode *now = NULL;											//head 노드부터 현재 가리키고 있는 노드를 표현하기 위한 포인터 선언 및 초기화
				
	input->key = key;												//삽입할 노드의 data field에 삽입할 key 저장

	if (h == NULL) {												//연결 리스트의 초기화가 일어나지 않아 head의 주소가 NULL이라면
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message 출력
		return -1;
	}
	else if (h->first == NULL) {									//만약 head 노드의 주소가 NULL 즉, 연결 리스트에 노드가 존재하지 않다면
		input->link = NULL;											//처음이자 마지막 노드이므로 삽입한 노드를 다음으로 가리킬 노드가 없으므로 NULL 저장
		h->first = input;											//search가 첫번째 노드가 되었으므로 head 노드를 search로 변경

		return key;													//key값 반환
	}
	now = h->first;													//연결 리스트의 head 노드의 주소를 저장하여 첫번째 노드부터 접근하도록 함
	for (; now->link != NULL; now = now->link);						//현재 위치가 마지막 노드가 되기 전까지 다음 노드의 위치로 이동하며 마지막 노드에 도달하기 위한 for문
	input->link = now->link;										//삽입할 노드가 다음 노드의 주소를 저장하여 pointing
	now->link = input;												//현재 위치의 노드가 삽입할 노드를 가리켜 연결 리스트에 삽입할 수 있도록 새로운 노드의 주소 저장

	return key;														//key값 반환
}
int deleteFirst(headNode* h) {										//연결 리스트의 head를 이용하여 첫번째 노드를 삭제하는 함수 정의
	listNode *temp = (listNode *)malloc(sizeof(listNode));			//삭제할 노드의 주소를 저장할 임의의 노드를 listNode 크기만큼의 동적 메모리 할당

	if (h == NULL) {												//연결 리스트의 초기화가 일어나지 않아 head의 주소가 NULL이라면
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message 출력
		return -1;
	}
	else if (h->first == NULL) {									//만약 head 노드의 주소가 NULL 즉, 연결 리스트에 노드가 존재하지 않다면
		printf(">>> This Linked List have not node!! <<<\n");		//head의 주소는 있지만 아직 node를 가지고 있지 않아서 ERROR message 출력

		return -1;
	}
	temp = h->first;												//연결 리스트의 첫번째 노드인 head 노드의 주소를 임의의 노드에 저장
	h->first = temp->link;											//head 노드가 가리키는 노드가 새로운 head 노드가 되기 떄문에 해당 노드의 주소를 head 노드를 가리키는 포인터에 저장
	free(temp);														//연결 리스트의 첫번째 노드인 이전의 head 노드의 메모리를 해제시켜 삭제
	printf("Delete First node\n");

	return 0;
}
int deleteNode(headNode* h, int key) {							//연결 리스트의 head와 삽입할 key값을 이용해 key에 같은 data field를 갖는 노드를 삭제하는 함수 정의
	listNode *temp = (listNode *)malloc(sizeof(listNode));		//listNode 크기만큼의 동적 메모리의 주소를 할당받아 임의의 노드로 사용
	listNode *previous = NULL;									//현재 노드의 이전 노드를 가리키고, 삭제된 노드 앞, 뒤의 노드를 이어주기 위해 필요한 포인터를 NULL로 초기화
	listNode *now = NULL;										//head 노드부터 현재 가리키고 있는 노드를 표현하기 위한 포인터 선언 및 초기화
		
	if (h == NULL) {											//연결 리스트의 초기화가 일어나지 않아 head의 주소가 NULL이라면
		printf(">>> This Linked List is not initialized! <<<\n");//ERROR message 출력
		return -1;
	}
	else if (h->first == NULL) {								//만약 head 노드의 주소가 NULL 즉, 연결 리스트에 노드가 존재하지 않다면
		printf(">>> This Linked List have not node!! <<<\n");	//head의 주소는 있지만 아직 node를 가지고 있지 않아서 ERROR message 출력

		return -1;
	}
	now = h->first;												//현재 위치 즉, 삭제할 노드의 주소를 저장할 포인터를 head 노드의 주소로 초기화
	for (; now != NULL; previous = now, now = now->link) {		//현재 위치가 마지막 노드를 벗어나기 전까지 이전 노드와 현재 노드를 각각 다음 노드로 이동하며 값을 비교하기 위한 for문
		if (now == h->first && key == now->key) {				//만약 현재 위치가 head 노드이고 그 노드가 삭제하고자 하는 key값과 동일하다면
			temp = now;											//삭제할 노드에 위치한 노드의 주소를 저장
			h->first = now->link;								//head 노드에 현재 노드의 다음 노드의 주소를 저장하여 연결 리스트를 끊기지 않도록 함
			free(temp);											//삭제할 노드의 주소가 담긴 임의의 노드를 해제하여 key값이 들었던 노드 삭제
			printf("Delete %d\n", key);
			return 0;
		}
		else if (now->key == key) {								//현재 위치의 data값이 삭제하고자 하는 key과 같지만 head 노드가 아니라면
			temp = now;											//삭제할 노드에 위치한 현재 노드의 주소를 저장
			previous->link = now->link;							//이전 노드가 현재 노드의 다음 노드를 가리켜 노드가 삭제되더라도 연결 리스트가 끊기지 않도록 함
			free(temp);											//삭제할 노드를 가리키는 임의의 노드를 해제시켜 key값과 동일한 data field를 갖는 노드 삭제
			printf("Delete %d\n", key);
			return 0;
		}
	}
	printf(">>> Not found %d <<<\n", key);						//연결 리스트의 마지막 노드까지 탐색했지만 동일한 key값을 찾지 못했다면 ERROR message 출력
	return -1;
}
int deleteLast(headNode* h) {										//연결 리스트의 head를 이용하여 마지막 노드를 삭제하는 함수 정의
	listNode *previous = NULL;										//현재 노드의 이전 노드를 가리키고, 삭제된 노드의 앞, 뒤를 이어주기 위한 포인터 선언 및 NULL로 초기화
	listNode *now = NULL;											//head 노드부터 현재 가리키고 있는 노드를 표현하기 위한 포인터 선언 및 초기화

	if (h == NULL) {												//연결 리스트의 초기화가 일어나지 않아 head의 주소가 NULL이라면
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message 출력
		return -1;
	}
	else if (h->first == NULL) {									//만약 head 노드의 주소가 NULL 즉, 연결 리스트에 노드가 존재하지 않다면
		printf(">>> This Linked List have not node!! <<<\n");		//head의 주소는 있지만 아직 node를 가지고 있지 않아서 ERROR message 출력

		return -1;
	}
	now = h->first;													//삭제할 노드의 주소를 저장할 포인터를 head 노드의 주소로 초기화
	for (; now->link != NULL; previous = now, now = now->link);		//현재 위치가 마지막 노드에 도달하기 전까지 이전 노드와 현재 노드를 각각 다음 노드로 이동하기 위한 for문
	if (previous != NULL)											//현재 노드의 이전 노드가 NULL이 아닐 경우 즉, 첫번째 노드가 아닐 경우
		previous->link = now->link;									//마지막 노드 이전의 노드가 마지막 노드가 가리키는 NULL을 pointing 하도록 하기 위해 현재 노드가 가리키는 주소 저장
	else															//현재 노드의 이전 노드가 NULL 즉, 현재 노드가 연결 리스트의 첫번째 노드일 경우
		h->first = NULL;											//previous 노드는 가리키고 있는 노드가 없으므로 head 노드를 현재 노드가 가리키는 주소 즉, NULL을 저장
	free(now);														//마지막 노드에 위치해있는 현재 노드를 해제함으로 마지막 노드 삭제
	printf("Delete Last node\n");

	return 0;
}
int invertList(headNode* h) {										//연결 리스트의 head를 이용하여 연결 리스트를 역순으로 바꾸는 함수 정의
	listNode *end, *mid = NULL, *now = NULL;						//연결 리스트를 역순으로 연결할 때 끊어지는 것을 방지하기 위해 3개의 구조체 포인터 선언 및 초기화
	if (h == NULL) {												//연결 리스트의 초기화가 일어나지 않아 head의 주소가 NULL이라면
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message 출력
		return -1;
	}
	else if (h->first == NULL) {									//만약 head 노드의 주소가 NULL 즉, 연결 리스트에 노드가 존재하지 않다면
		printf(">>> This Linked List have not node!! <<<\n");		//head의 주소는 있지만 아직 node를 가지고 있지 않아서 ERROR message 출력

		return -1;	
	}
	else {															//연결 리스트에 하나 이상의 노드가 연결되어 있다면
		now = h->first;												//현재 리스트의 첫번째 노드부터 접근하기 위해 첫번째 노드의 주소 저장
		for (; now != NULL;) {										//현재 위치의 노드가 마지막 노드를 벗어나기 전까지 연결 리스트를 역순으로 잇기 위한 for문
			end = mid;												//역순된 리스트에서 연결해야 될 노드로 사용하기 위해 현재 노드로 위치를 변경할 노드의 주소를 저장
			mid = now;												//연결 리스트의 노드들이 자신의 이전 노드를 가리키도록 하기 위해 일단 현재 노드의 주소 저장
			now = now->link;										//역순으로 연결될 시 mid의 다음 노드의 주소를 잃어버릴 수 있으므로 현재 노드를 다음 노드의 주소를 저장하여 이동
			mid->link = end;										//mid 이전의 노드의 주소를 저장할 end의 주소를 저장하여 연결 리스트를 역순으로 연결
		}	
		h->first = mid;												//역순되기 이전의 연결 리스트의 head 노드를 역순된 리스트의 head 노드를 가리키는 노드의 주소를 저장하여 head 변경

		return 0;
	}
}
void printList(headNode* h) {					//연결 리스트의 head를 이용하여 연결 리스트의 각 노드들의 data field값을 출력하는 함수 정의
	int i = 0;									//연결 리스트의 index 번호를 표현하기 위한 정수형 변수 선언 및 0으로 초기화
	listNode* p;								//연결 리스트의 head 노드의 주소를 저장할 구조체 포인터 변수 선언

	printf("\n---PRINT\n");

	if (h == NULL) {							//연결 리스트의 head가 NULL 즉, 어떤 연결 리스트도 가리키고 있지 않다면
		printf("Nothing to print....\n");		//ERROR message 출력
		return;
	}

	p = h->first;								//연결 리스트의 head 노드의 주소를 저장하여 첫번째 노드부터 접근 가능

	while (p != NULL) {							//현재 노드의 위치가 마지막 노드의 위치를 벗어나기 전까지 각 노드의 data field값을 출력하기 위한 for문
		printf("[ [%d]=%d ] ", i, p->key);		//첫번째 노드부터 마지막 노드까지의 data field값을 index번호와 함께 출력
		p = p->link;							//현재 위치에서 다음 노드의 주소를 저장하여 다음 노드로 이동
		i++;									//이와 함께 index 번호도 증가
	}

	printf("  items = %d\n", i);				//연결 리스트에 들어있는 노드의 수 출력
}
