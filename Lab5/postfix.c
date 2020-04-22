#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4				//4라는 수를 MAX_QUEUE_SIZE라는 기호 상수로 선언

typedef char element;					//char형을 element라는 새로운 이름으로 선언
typedef struct {			           	//구조체에 대한 정의
	element queue[MAX_QUEUE_SIZE];			//원형 큐로 사용할 크기가 4인 문자열 배열 queue 선언
	int front, rear;				//원소가 삭제되는 끝을 나타내는 front, 새로운 원소가 삽입되는 끝을 나타내는 rear 선언
}QueueType;						//해당 구조체를 QueueType이라는 이름으로 정의

QueueType *createQueue();							//데이터를 삽입할 원형 큐, front, rear를 생성하기 위한 createQueue 함수 원형 선언
int isEmpty(QueueType *cQ);							//해당 원형 큐가 비어있는지 검사하는 isEmpty 함수 원형 선언
int isFull(QueueType *cQ);							//해당 원형 큐가 꽉 차있는지 검사하는 isFull 함수 원형 선언
void enQueue(QueueType *cQ, element item);					//rear 위치에 새로운 문자를 삽입하기 위한 enQueue 함수 원형 선언
void deQueue(QueueType *cQ, element* item);					//front 위치에 있는 문자를 삭제하기 위한 deQueue 함수 원형 선언
void printQ(QueueType *cQ);							//현재 원형 큐에 들어있는 원소를 출력하는 printQ 함수 원형 선언
void debugQ(QueueType *cQ);							//현재 원형 큐의 상태를 출력하는 debugQ 함수 원형 선언
int freeQueue(Queue *cQ);							//원형 큐로 사용하는 cQ의 동적 메모리를 해재시키는 함수 원형 선언
element getElement();								//사용자가 삽입하길 원하는 문자를 입력할 수 있는 getElement 함수 원형 선언

int main(void)
{
	QueueType *cQ = createQueue();								//createQueue 함수를 호출하여 데이터 3개와 1개의 front를 저장 가능한 원형 큐를 동적 할당
	element data;										//사용자가 입력한 문자를 저장하는 element(=char)형 변수 선언

	char command;										//사용자가 입력한 메뉴를 저장하는 char형 변수 선언
	printf("[------[ 유현진 ] [2019038006]------]");

	do {											//do-while문의 실행 문장을 한번 실행 후 조건문에 대해 false가 될 때까지 계속 반복
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);								//실행하고픈 메뉴에 해당하는 문자 입력 및 command에 저장

		switch (command) {								//command 값을 case 별로 비교하여 해당하는 case 안의 문장 실행
		case 'i': case 'I':								//사용자가 i or I를 입력했다면
			data = getElement();							//getElement 함수를 호출하여 삽입하고픈 문자를 입력한 후 함수의 반환값 즉, 입력한 문자를 data에 저장
			enQueue(cQ, data);							//enQueue 함수를 호출하여 data를 원형 큐에 삽입
			break;									//switch를 빠져나감
		case 'd': case 'D':								//사용자가 d or D를 입력했다면
			deQueue(cQ, &data);							//deQueue 함수를 호출하여 현재 원형 큐의 첫번째 데이터 값을 삭제
			break;									//switch를 빠져나감
		case 'p': case 'P':								//사용자가 p or P를 입력했다면
			printQ(cQ);								//printQ 함수를 호출하여 현재 원형 큐에 들어있는 데이터를 출력
			break;									//switch를 빠져나감
		case 'b': case 'B':								//사용자가 b or B를 입력했다면
			debugQ(cQ);								//debugQ 함수를 호출하여 현재 원형 큐의 상태에 대한 정보 출력
			break;									//switch를 빠져나감
		case 'q': case 'Q':								//사용자가 q or Q를 입력했다면
			freeQueue(cQ);								//freeQueue 함수를 호출하여 동적 할당한 cQ의 메모리를 해제
			break;									//switch를 빠져나감
		default:									//위의 경우 이외의 문자가 입력되었다면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		//error message 출력
			break;									//switch를 빠져나감
		}
	} while (command != 'q' && command != 'Q');						//command 값이 프로그램의 종료를 뜻하는 q or Q가 아니라면 다시 do-while문 실행

	return 1;
}
QueueType *createQueue()									//데이터를 삽입할 원형 큐, front, rear를 생성하기 위한 함수 정의
{
	QueueType *cQ;										//원형 큐, front, rear의 정보를 저장할 구조체 포인터 변수 cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));						//cQ에 구조체 QueueType의 크기만큼 동적 메모리를 할당
	cQ->front = 0;										//cQ의 원소가 삭제되는 끝인 front 값을 0으로 초기화
	cQ->rear = 0;										//cQ의 새로운 원소가 삽입되는 끝인 rear 값을 0으로 초기화

	return cQ;										//cQ가 할당받은 메모리의 주소 반환
}
element getElement()										//사용자가 원하는 문자를 입력할 수 있는 함수 정의
{
	element item;										//사용자가 입력한 문자를 저장하는 변수 선언
	printf("Input element = ");
	scanf(" %c", &item);									//사용자가 삽입하고픈 문자를 입력하여 item에 저장
	
	return item;										//item에 저장된 문자를 반환
}
int isEmpty(QueueType *cQ)									//원형 큐와 그에 대한 정보를 가진 구조체의 주소를 가진 cQ를 이용하여 해당 원형 큐가 비었는지 검사하는 함수 정의
{
	if (cQ->front == cQ->rear) {								//만약 front의 index 번호가 rear의 index 번호와 같다면
		printf("This Queue is Empty.\n");						//해당 원형 큐가 비었다는 메세지 출력
		return 1;									//1을 반환하고 함수 종료
	}
	return 0;										//front의 index 번호가 rear의 index 번호와 같지 않다면 즉, 원형 큐가 비어있지 않다면 0을 반환하고 함수 종료
}
int isFull(QueueType *cQ)									//원형 큐와 그에 대한 정보를 가진 구조체의 주소를 가진 cQ를 이용하여 해당 원형 큐가 다 찼는지 검사하는 함수 정의
{
	if (cQ->front == ((cQ->rear+1) % MAX_QUEUE_SIZE)) {					//현재 rear의 다음 위치와 front 위치가 같다면 즉, 삽입하고자 하는 위치가 front의 위치와 같다면
		printf("This Queue is full.\n");						//해당 원형 큐가 다 찼다는 메세지 출력
		return 1;									//1을 반환하고 함수 종료
	}
	return 0;										//현재 rear의 다음 위치와 front 위치가 같지 않다면 즉, 원형 큐에 삽입 가능 공간이 남아있다면 0을 반환하고 함수 종료
}
void enQueue(QueueType *cQ, element item)							//원형 큐와 그에 대한 정보를 가진 구조체 포인터 변수 cQ와 사용자가 입력한 문자를 가진 문자형 변수 item를 이용하여 원형 큐에 item을 삽입하는 함수 정의
{
	if (isFull(cQ) == 1) {									//isFull 함수의 반환값이 1 즉, 원형 큐가 꽉 차있다면
		printf("Can't insert %c\n", item);						//원하는 데이터를 삽입하지 못한다는 메세지 출력
	}
	else {											//isFull 함수의 반환값이 1이 아니면 즉, 원형 큐가 꽉 차있지 않다면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;					//현재 rear 위치를 다음 index로 이동(만약 rear+1이 최대 index를 벗어나면 rear의 위치를 0으로)
		printf("Insert %c\n", item);							//사용자가 입력한 데이터를 삽입한다는 메세지 출력
		cQ->queue[cQ->rear] = item;							//원형 큐에서 이동한 rear의 위치에 데이터 삽입
	}
}
void deQueue(QueueType *cQ, element *item)							//원형 큐와 그에 대한 정보를 가진 구조체 포인터 변수 cQ와 사용자가 입력한 문자를 가진 문자형 변수 item를 이용하여 현재 원형 큐에 남은 첫번째 데이터를 제거하는 함수 정의
{	
	if (isEmpty(cQ) == 1) {									//isEmpty 함수의 반환값이 1 즉, 원형 큐가 비어있다면
		printf("No more data to delete\n");						//지울 데이터가 없다는 메세지 출력
	}
	else {											//isEmpty 함수의 반환값이 1이 아니면 즉, 원형 큐가 비어있지 않다면
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;					//현재 front 위치를 다음 index로 이동(만약 front+1이 최대 index를 벗어나면 front의 위치를 0으로)
		*item = cQ->queue[cQ->front];							//front의 위치에 들어있는 데이터를 item이 가리키는 메모리의 값 즉, data에 저장
		printf("Delete %c\n", *item);							//data(=*item)를 삭제한다는 메세지 출력
		cQ->queue[cQ->front] = ' ';						 	//현재 front의 위치에 들어있는 데이터를 삭제했음으로 해당 값을 ' '로 저장(데이터가 없는 상태)
	}
}
void printQ(QueueType *cQ)									//원형 큐와 그에 대한 정보를 가진 구조체 포인터 변수 cQ를 이용하여 원형 큐에 저장된 데이터를 출력하는 함수 정의
{
	int i, first, last;									//원형 큐의 시작과 끝을 나타내는 변수 first, last 와 원형 큐를 출력할 때 현재 위치를 나타내줄 변수 i를 선언

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;						//front 다음에 위치한 큐의 첫번째 데이터의 위치를 first에 저장
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;							//마지막 데이터가 들어있는 다음 공간의 위치를 last에 저장
	i = first;										//첫번째 데이터의 위치를 i에 저장

	printf("Circular Queue : [");

	while (i != last) {									//i가 데이터가 삽입되지 않은 곳을 가리키기 전까지 while문 실행
		printf("%3c", cQ->queue[i]);							//i에 위치한 데이터를 출력
		i = (i + 1) % MAX_QUEUE_SIZE;							//다음 데이터의 위치를 i에 저장
	}
	printf(" ]\n");
}
void debugQ(QueueType *cQ)									//원형 큐와 그에 대한 정보를 가진 구조체의 주소를 가진 cQ를 이용하여 현재 원형 큐의 상태를 출력하는 함수 정의
{
	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {						//원형 큐로 사용되고 있는 크기가 MAX_QUEUE_SIZE인 1차원 배열의 원소를 출력하기 위한 for문
		if (i == cQ->front) {								//만약 i가 front의 위치를 가리킨다면
			printf("  [%d] = front\n", i);						//i가 가리키는 index가 front라는 것을 명시
			continue;								//현재 i에 대한 for문 실행을 관두고, 다음 i에 대한 for문 실행 (건너뜀)
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);					//i번째 index의 원소의 값을 출력
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);					//원형 큐의 front와 rear의 index번호를 출력
}
int freeQueue(Queue *cQ)									//원형 큐로 사용되고 있는 구조체 포인터의 메모리를 해제하기 위한 함수 정의
{
	if (cQ == NULL)										//만약 cQ의 주소가 NULL 즉, 할당받은 메모리가 없다면
		return 0;									//free함수를 호출하지 않고 0을 return
	free(cQ);										//cQ의 주소가 NULL 아님 즉, 동적 메모리를 할당받았다면
	return 1;										//1을 return
}
