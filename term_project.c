/*무방향 graph*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 20	/* you can change value 20 */

typedef struct Vertex {
	int num;				 //노드 번호
	struct Vertex* link;	 //해당 노드의 인접 노드를 가리키는 링크
} Vertex;
typedef struct VertexHead {
	Vertex* head;			 //모든 인접 노드들의 연결리스트
} VertexHead;
typedef struct Graph {
	VertexHead* vlist;		 //모든 노드의 리스트
} Graph;
typedef struct {
	int queue[MAX_VERTEX];			//원형 큐로 사용할 크기 MAX_VERTEX인 int형 배열 queue 선언
	int front, rear;				//원소 삭제 위치 : front, 새로운 원소 삽입 부분 : rear
}QueueType;

int createGraph(Graph**);			//빈 그래프 생성하는 함수
int destroyGraph(Graph**);			//그래프에서 사용된 모든 동적 메모리 해제하는 함수
int insertVertex(Graph*, int);		//노드 삽입하는 함수
int deleteVertex(Graph*, int);		//노드 삭제하는 함수
int insertEdge(Graph*, int, int);	//그래프의 간선 추가하는 함수
int deleteEdge(Graph*, int, int);	//추가된 간선을 삭제하는 함수
void depthFS(Graph*, int);			//깊이 우선 탐색을 실행하는 함수 (stack 사용)
void breadthFS(Graph*, int);		//너비 우선 탐색을 실행하는 함수 (queue 사용)
void printGraph(Graph*);			//현재 그래프의 상태를 보여주는 함수

Vertex* checkVertex(VertexHead*, int);	//해당 번호를 가진 노드가 존재하는지 판별하는 함수
int chechCommonError(Graph*, int, int);	//중복되는 예외처리를 모아둔 함수
int isEmpty();		//queue가 비어있는지 확인하는 함수
int isFull();		//queue가 꽉 차있는지 확인하는 함수
void enQueue(int);	//queue에 item을 삽입하는 함수
int deQueue();		//queue의 front에 있는 원소를 삭제하는 함수

void push(int);		//stack에 int형 원소를 삽입하는 함수
int pop();			//stack에 맨 위에 있는 원소를 삭제하는 함수

int visiting[MAX_VERTEX];	//노드의 방문 여부를 저장하는 int형 배열
int stack[MAX_VERTEX];		//깊이 우선 탐색을 워한 stack으로 사용할 배열
int top = -1;				//stack의 마지막 삽입된 원소의 위치를 가리키는 top
QueueType breathQ;			//너비 우선 탐색에서 사용할 queue


int main() {
	Graph *graph = NULL;
	int nodeNum = 0, edgeNum = 0;
	char command;

	//Queue의 기본 설정
	breathQ.front = 0; breathQ.rear = 0;

	printf("[----- [유현진] [2019038006] -----]");
	do {
		printf("\n----------------------------------------------------------------\n");
		printf("                           Graph                                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Create Graph      = c       Destroy Graph      = y\n");
		printf(" Insert Vertex     = i       Delete Vertex      = v\n");
		printf(" Insert Edge       = e       Delete Edge        = g \n");
		printf(" DepthFs           = d       Print Graph        = p \n");
		printf(" breadthFS         = b       Quit               = q \n");
		printf("----------------------------------------------------------------\n");

		//원하는 메뉴 입력하는 곳
		printf("Command = ");
		scanf(" %c", &command);

		//입력한 메뉴 문자를 비교하여 해당하는 case문 실행
		switch (command) {
		case 'c': case 'C':
			//graph를 형성하는 함수 호출
			createGraph(&graph);	
			break;
		case 'y': case 'Y':
			//생성된 graph를 삭제하는 함수 호출
			destroyGraph(&graph);
			break;
		case 'i': case 'I':
			printf("Enter the node number you want to insert : ");
			//삽입노드의 번호 입력
			scanf("%d", &nodeNum);
			//입력한 노드를 삽입하는 함수 호출
			insertVertex(graph, nodeNum);
			break;
		case 'v': case 'V':
			printf("Enter Vertex num that deletes  : ");
			//삭제하길 원하는 노드 번호 입력
			scanf("%d", &nodeNum);		
			//입력한 노드를 삭제하는 함수 호출
			deleteVertex(graph, nodeNum);	
			break;
		case 'e': case 'E':
			printf("Enter two node num that make up the edge : ");
			//간선을 생성할 두 노드를 입력
			scanf("%d %d", &nodeNum, &edgeNum);	
			//해당 간선을 생성하는 함수 
			insertEdge(graph, nodeNum, edgeNum);
			//무방향 graph이기 때문에 edgeNum 노드의 인접 노드의 list에서 nodeNum를 삽입하기 위한 함수 호출
			insertEdge(graph, edgeNum, nodeNum);
			break;
		case 'g': case 'G':
			printf("Enter two node num that delete the edge : ");
			//삭제할 간선을 입력
			scanf("%d %d", &nodeNum, &edgeNum);	
			//입력한 간선을 삭제하는 함수 호출
			deleteEdge(graph, nodeNum, edgeNum);
			//무방향 graph이기 때문에 edgeNum 노드의 인접 노드의 list에서 nodeNum를 삭제하기 위한 함수 호출
			deleteEdge(graph, edgeNum, nodeNum);
			break;
		case 'd': case 'D':
			//탐색을 시작할 노드의 번호를 입력
			printf("Enter the Search Start node : ");
			scanf("%d", &nodeNum);
			//깊이 우선 탐색 진행
			depthFS(graph->vlist, nodeNum);
			//visiting 배열 초기화( 방문 여부 초기화 )
			for (int i = 0; i < MAX_VERTEX; i++)
				visiting[i] = 0;
			break;
		case 'b': case 'B':
			//탐색을 시작할 노드의 번호를 입력
			printf("Enter the Search Start node : ");
			scanf("%d", &nodeNum);
			//너비 우선 탐색 진행
			breadthFS(graph->vlist, nodeNum);
			//visiting 배열 초기화( 방문 여부 초기화 )
			for (int i = 0; i < MAX_VERTEX; i++)
				visiting[i] = 0;
			break;
		case 'p': case 'P':
			//현재의 graph 상태를 출력하는 함수 호출
			printGraph(graph);
			break;
		default:
			//잘못 입력했음을 알려주는 메세지
			printf(">>> Menu Selection Error <<<\n");
			break;
		}

	} while (command != 'q' && command != 'Q');		//Quit메뉴를 선택 시 프로그램 종료

	return 0;
}
int createGraph(Graph** graph) {
	//graph가 이미 생성되어 있는 경우
	if (*graph != NULL) {		
		//이미 생성된 graph를 삭제하는 함수 호출
		destroyGraph(*graph);	
	}

	//새로운 graph를 만들 메모리 공간을 할당
	*graph = (Graph*)malloc(sizeof(Graph));		
	//그래프의 각 노드에 대한 list 생성
	(*graph)->vlist = (VertexHead *)malloc(sizeof(VertexHead) * MAX_VERTEX);
	//MAX_VERTEX개의 노드에 대해
	for (int i = 0; i < MAX_VERTEX; i++)
		//[i+1] 노드의 link를 NULL로 설정(가리키는 것 없음)
		(*graph)->vlist[i].head = NULL;

	return 0;
}
int destroyGraph(Graph** graph) {
	//공통으로 처리되는 예외 중에 해당사항이 있으면 함수 종료(nodeNum, edgeNum은 임의 지정, graph 존재 여부 판단)
	if (chechCommonError(*graph, 1, 2) == -1)
		return -1;

	//MAX_VERTEX개의 노드에 대해
	for (int i = 1; i <= MAX_VERTEX; i++) {	
		//삽입되지 않았던 노드의 삭제 함수 실행은 건너뜀
		if ((*graph)->vlist[i - 1].head == NULL)
			continue;
		//[i]노드를 삭제하는 함수 호출
		deleteVertex(*graph, i);
	}
	//vertex list의 메모리 공간 해제
	free((*graph)->vlist);
	//생성했었던 graph의 메모리 공간 해제
	free(*graph);				
	//vlist에 NULL을 대입 -> '아무것도 없음'을 나타냄
	(*graph)->vlist = NULL;	
	//graph에 NULL을 대입 -> '아무것도 없음'을 나타냄
	(*graph) = NULL;		

	return 0;
}
int insertVertex(Graph* graph, int nodeNum) {
	//새로운 노드의 메모리 공간 할당
	Vertex* node = (Vertex*)malloc(sizeof(Vertex));

	//새로운 노드에 nodeNum 삽입
	node->num = nodeNum;
	//새로 삽입된 노드이므로 연결되는 노드는 존재X -> link = NULL
	node->link = NULL;

	//graph 존재 여부, nodeNum 범위, nodeNum노드 존재 여부 판단(edgeNum은 임의 지정)
	if (chechCommonError(graph, nodeNum, 1) == -1)
		return -1;

	//graph의 노드들의 list를 넘겨받음
	VertexHead* vlist = graph->vlist;

	//nodeNum 노드가 들어갈 자리에 이미 해당 노드가 연결되있는 경우
	if (vlist[nodeNum-1].head != NULL) {
		printf(">>> This node is already inserted <<<\n");
		return -1;
	}
	//해당 자리에 아직 노드가 삽입되지 않았다면
	//vlist의 nodeNum 노드 위치의 head에 삽입노드를 연결
	vlist[nodeNum - 1].head = node;	
	printf("Insert %d node\n", nodeNum);
	return 0;
}
void printGraph(Graph* graph) {
	Vertex* node = NULL;

	//graph 존재 여부 판단(nodeNum, edgeNum은 임의 지정)
	if (chechCommonError(graph, 1, 2) == -1)
		return -1;

	//graph의 노드들의 list를 넘겨받음
	VertexHead* vlist = graph->vlist;

	//MAX_VERTEX개의 노드에 대해
	for (int i = 0; i < MAX_VERTEX; i++) {
		//(i+1)번 노드가 삽입되어 있는 경우
		if (vlist[i].head != NULL) {
			//(i+1)번 노드를 출력
			printf("[ %d ] ", i + 1);

			//(i+1)번 노드의 간선들을 출력하기 위해 link를 node에 저장
			//(i+1)번 노드의 마지막 간선까지 접근
			for (node = vlist[i].head->link; node != NULL; node = node->link) {
				//해당 노드의 간선들을 list에 연결된 순서대로 출력
				printf("--> [ %d ] ", node->num);
			}
			printf("\n");
		}
		//(i+1)번 노드가 삽입되어 있지 않은 경우
		else
			//해당 노드의 출력을 건너뜀
			printf("\n");
	}
}
int deleteEdge(Graph* graph, int nodeNum, int edgeNum) {
	Vertex* node = NULL;
	Vertex* previous = NULL;

	//graph 존재 여부, nodeNum 범위, edgeNum 범위, 노드 존재 여부 판단(return이 0이 아니라면 함수 종료)
	if (chechCommonError(graph, nodeNum, edgeNum))
		return -1;

	//graph의 노드들의 list를 넘겨받음
	VertexHead* vlist = graph->vlist;
	//nodeNum노드가 들어갈 메모리 주소를 저장
	node = vlist[nodeNum - 1].head;

	//nodeNum노드에 edgeNum와 연결된 간선을 삭제하기 위한 for문
	for (previous = node, node = node->link; node != NULL; previous = node, node = node->link) {
		//edgeNum와 연결된 간선이 존재한다면
		if (node->num == edgeNum) {	
			//nodeNum와 연결된 edgeNum노드를 삭제했을 때, 연결리스트의 끊김을 방지하기 위해 edgeNum 전의 인접 노드와 다음 인접 노드를 연결
			previous->link = node->link;	
			//연결된 간선에 해당하는 노드 삭제
			free(node);						

			return 0;
		}
	}
	//for문이 끝나도 삭제된 간선이 없는 경우, 해당 간선은 존재하지 않다는 것이므로, error 메세지 출력
	printf(">>> This [%d]----[%d] edge doesn't exist <<<\n", nodeNum, edgeNum);
	return -1;
}
int insertEdge(Graph* graph, int nodeNum, int edgeNum) {
	Vertex* node = NULL, *previous = NULL;
	//삽입할 간선에 해당하는 인접 노드의 메모리 할당
	Vertex* insert = (Vertex*)malloc(sizeof(Vertex));	

	//삽입할 간선의 인접 노드의 번호 저장
	insert->num = edgeNum;	
	//삽입 인접 노드는 연결리스트의 마지막에 위치할 것이므로, 해당 노드 다음에 연결될 것은 없으므로 NULL
	insert->link = NULL;	

	//graph 존재 여부, nodeNum 범위, edgeNum 범위, 노드 존재 여부 판단(return이 0이 아니라면 함수 종료)
	if (chechCommonError(graph, nodeNum, edgeNum))
		return -1;

	//graph의 노드들의 list를 넘겨받음
	VertexHead* vlist = graph->vlist;
	//nodeNum번 노드 위치를 저장
	node = vlist[nodeNum - 1].head;
		
	//nodeNum노드의 마지막 인접노드에 다다를때까지
	for (; node != NULL; previous = node, node = node->link) {
		//이미 해당 간선을 생성하는 인접 노드가 있을 경우
		if (node->num == edgeNum) {		
			printf(">>> Already insert [%d]----[%d] Edge <<<\n", nodeNum, edgeNum);
			return -1;
		}
	}
	//for문이 끝날 때까지 인접노드 edgeNum을 찾지 못했다면 이전에 추가된 적이 없다는 것, 즉 새로 추가해야 함
	//새로 추가할 인접 노드의 정보를 가진 노드를 node의 마지막 인접 노드 다음에 연결
	previous->link = insert;
	//연결되었음을 알리는 메세지
	printf("Insert [%d]----[%d] Edge\n", nodeNum, edgeNum);	

	return 0;
}
int deleteVertex(Graph* graph, int nodeNum) {
	Vertex* node = NULL;
	//삭제할 인접 노드 및 헤드 노드 저장
	Vertex* deleteV = NULL;	

	//graph 존재 여부, nodeNum 범위, nodeNum노드 존재 여부 판단(edgeNum은 임의 지정)
	if (chechCommonError(graph, nodeNum, 2) == -1)
		return -1;

	//graph의 노드들의 list를 넘겨받음
	VertexHead* vlist = graph->vlist;
	//nodeNum 노드가 들어가있어야하는 자리에 NULL 즉, 해당 노드가 없다면
	if (vlist[nodeNum - 1].head == NULL) {
		//이전에 이미 삭제되었다는 메세지 출력
		printf(">>> [ %d ]node already deletes <<<\n", nodeNum);
		return -1;
	}
	
	//nodeNum노드를 인접 노드로 가지고 있는 노드들을 찾아 해당 노드에서 인접 노드 nodeNum를 삭제하는 과정
	//MAX_VERTEX개의 대해
	for (int i = 1; i <= MAX_VERTEX; i++)
		//(i+1)번 노드의 인접 노드 nodeNum를 삭제하는 함수 호출(nodeNum을 인접노드로 가지고 있는지는 해당 함수에서 check)
		deleteEdge(graph, i, nodeNum);
	//nodeNum노드를 deleteV에 저장
	deleteV = vlist[nodeNum - 1].head;
	//nodeNum노드가 저장되있던 공간을 NULL로 바꿈 즉, vlist에서 nodeNum노드 삭제
	vlist[nodeNum - 1].head = NULL;

	//해당 노드를 지우려면 연결되있던 인접노드들을 삭제 필수
	while (deleteV != NULL) {
		//nodeNum노드의 마지막 인접 노드에 다다를때까지
		node = deleteV->link;
		//다음 인접 노드의 접근하기 위해 node에 임시로 저장
		deleteV->link = NULL;
		//현재 삭제해야할 노드의 연결을 끊음
		free(deleteV);			
		//deleteV에 저장된 인접 노드를 삭제 (처음에는 nodeNum 삭제)
		//node에 저장했던 다음 인접 노드로 이동
		deleteV = node;			
	}
}
void depthFS(Graph* graph, int nodeNum) {
	Vertex* adVertex;

	//graph 존재 여부, nodeNum 범위, nodeNum노드 존재 여부 판단(edgeNum은 임의 지정)
	if (chechCommonError(graph, nodeNum, 1) == -1)
		return -1;
	//graph의 노드들의 list를 넘겨받음
	VertexHead* vlist = &graph->vlist;

	//nodeNum 노드가 없는 노드라면
	if (vlist[nodeNum - 1].head == NULL) {
		printf(">>> This node isn't existed <<<\n");
		return -1;
	}
	;
	//탐색 시작 노드의 방문 여부를 1(True)로 설정
	visiting[nodeNum - 1] = 1;
	//탐색 시작 노드를 stack에 삽입
	push(nodeNum);					
	//해당 노드 출력
	printf("[ %d ]  ", nodeNum);		

	//stack이 빌 때까지 loop
	while (top != -1) {			
		//stack의 top 위치에 있는 노드 번호를 vertex에 저장
		nodeNum = stack[top];	

		//방문하지 않은 인접 노드를 찾기 위한 for문, 더이상 접근할 인접 노드가 없을 경우 for문 종료
		for (adVertex = vlist[nodeNum - 1].head->link; adVertex; adVertex = adVertex->link) {
			//만약 adVertex에 저장된 노드가 아직 방문하지 않은 인접노드일 경우
			if (!visiting[(adVertex->num) - 1]) {
				//해당 노드를 stack에 삽입 -> 다음에 해당 원소에 접근할 때 탐색 노드로 활용
				push(adVertex->num);				 
				//삽입한 노드 번호를 출력 (탐색 완료)
				printf("[ %d ]  ", adVertex->num);	 
				//해당 인접 노드의 방문 여부를 1(True)로 변경
				visiting[(adVertex->num) - 1] = 1;	 
				break;
			}
		}
		//더이상 vertex에 대한 접근할 인접 노드가 없을 경우
		if (adVertex == NULL)
			//top의 위치에 있는 노드를 삭제 -> 삭제된 노드는 더이상 탐색X
			pop();	
	}
	printf("\n");
}
void breadthFS(Graph* graph, int nodeNum) {
	//인접 노드 저장
	Vertex* adVertex;

	//graph 존재 여부, nodeNum 범위, nodeNum노드 존재 여부 판단(edgeNum은 임의 지정)
	if (chechCommonError(graph, nodeNum, 1) == -1)
		return -1;

	//graph의 노드들의 list를 넘겨받음
	VertexHead* vlist = &graph->vlist;

	//nodeNum 노드가 없는 노드라면
	if (vlist[nodeNum - 1].head == NULL) {
		printf(">>> This node isn't existed <<<\n");
		return -1;
	}
	//탐색 시작점인 vertex노드의 visiting 여부 1(True)로 변경
	visiting[nodeNum - 1] = 1;
	//veretex노드를 queue에 저장
	enQueue(nodeNum);		
	//해당 노드 출력
	printf("[ %d ]  ", nodeNum);

	//queue이 더이상 아무것도 들어있지 않은 경우
	while (isEmpty() != -1) {	
		//queue에 가장 앞에 있는 노드 반환 및 삭제
		nodeNum = deQueue();		

		//vertex에 저장된 노드의 인접 노드부터 시작하여, 마지막 인접노드에 접근할 때까지 for문 실행
		for(adVertex = vlist[nodeNum-1].head->link; adVertex; adVertex = adVertex->link)
			//adVertex에 저장된 인접 노드의 방문 여부가 0일 경우
			if (!visiting[(adVertex->num)-1]) {		
				//해당 인접 노드를 출력
				printf("[ %d ]  ", adVertex->num);	
				//해당 인접 노드를 queue에 삽입
				enQueue(adVertex->num);				
				//해당 인접 노드의 방문 여부를 1로 변경
				visiting[(adVertex->num) - 1] = 1;	
			}
	}
}
Vertex* checkVertex(VertexHead* vlist, int vertex) {
	Vertex* node = vlist[vertex - 1].head;	//vertex번 노드가 삽입되었을 head를 node에 저장

	//vertex번 노드가 삽입되지 않은 경우
	if (node == NULL)
		return NULL;
	//vertex번 노드가 삽입된 경우
	return node;
}
int chechCommonError(Graph* graph, int nodeNum, int edgeNum) {
	//edgeNum도 check를 해야되냐에 따라 return값을 다르게 하여 상황 구분
	//graph가 생성되지 않은 경우
	if (graph == NULL) {
		printf(">>> This graph isn't initialized <<<\n");
		return -1;
	}
	//삽입 가능한 노드의 범위를 넘어간 경우
	if ((nodeNum < 1 || nodeNum > MAX_VERTEX) || (edgeNum < 1 || edgeNum > MAX_VERTEX)) {
		printf(">>> This node is out of range, so can't insert <<<\n");
		return -1;
	}
	//자기자신과의 간선을 생성하는 경우
	if (nodeNum == edgeNum) {
		//printf(">>> Can't enter same number <<<\n");
		return -2;
	}
	//해당 노드들이 존재하는지 판단
	//둘 중 하나라도 존재하지 않는 노드가 있는 경우
	if ((!checkVertex(graph->vlist, nodeNum)) || (!checkVertex(graph->vlist, edgeNum))) {
		//printf(">>>There are nodes that do not exist <<<\n");
		return -2;
	}
	//해당되는 예외처리가 없다면
	return 0;
}
int isEmpty() {
	//만약 front의 index 번호가 rear의 index 번호와 같다면
	if (breathQ.front == breathQ.rear)		
		return -1;
	//원형 큐가 비어있지 않음
	return 0;
}
int isFull() {
	//현재 rear의 다음 위치와 front 위치가 같다면 즉, 삽입하고자 하는 위치가 front의 위치와 같다면
	if (breathQ.front == ((breathQ.rear + 1) % MAX_VERTEX))		
		return -1;
	//원형 큐에 삽입 가능 공간이 남음
	return 0;
}
void enQueue(int item) {
	//isFull 함수의 반환값이 1 즉, 원형 큐가 꽉 차있다면
	if (isFull() == -1) {									
		printf("Can't insert %d\n", item);
	}
	//isFull 함수의 반환값이 1이 아니면 즉, 원형 큐가 꽉 차있지 않다면
	else {													
		//현재 rear 위치를 다음 index로 이동(만약 rear+1이 최대 index를 벗어나면 rear의 위치를 0으로)
		breathQ.rear = (breathQ.rear + 1) % MAX_VERTEX;		
		//원형 큐에서 이동한 rear의 위치에 데이터 삽입
		breathQ.queue[breathQ.rear] = item;					
	}
}
int deQueue() {
	int item;

	//isEmpty 함수의 반환값이 1 즉, 원형 큐가 비어있다면
	if (isEmpty() == 1) {									
		printf("No more data to delete\n");
	}
	//isEmpty 함수의 반환값이 1이 아니면 즉, 원형 큐가 비어있지 않다면
	else {													
		//현재 front 위치를 다음 index로 이동(만약 front+1이 최대 index를 벗어나면 front의 위치를 0으로)
		breathQ.front = (breathQ.front + 1) % MAX_VERTEX;	
		//front의 위치에 들어있는 데이터를 item이 가리키는 메모리의 값 즉, data에 저장
		item = breathQ.queue[breathQ.front];				
		//현재 front의 위치에 들어있는 데이터를 삭제했음으로 해당 값을 ' '로 저장(데이터가 없는 상태)
		breathQ.queue[breathQ.front] = ' ';				    

		return item;
	}
}	
void push(int item) {	
	//stack의 가장 위에 item을 삽입 (++하기 전 top은 마지막에 들어온 원소 위치 가리킴)
	stack[++top] = item;	
}
int pop() {
	int item = 0;
	//현재 top위치에 있는 원소를 item에 저장하고 top의 위치를 1 감소
	item = stack[top--];
	return item;
}