#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE	13	/* prime number */
#define MAX_HASH_TABLE_SIZE  MAX_ARRAY_SIZE

int initialize(int **a);		//인자로 넘어온 포인터에 배열 공간을 할당받고 각 원소에 랜덤값을 저장하는 함수
int freeArray(int *a);			//포인터가 할당받았던 메모리 공간을 해제하는 함수 
void printArray(int *a);		//현재 배열의 상태 (인덱스와 그에 해당하는 원소)를 출력하는 함수
	
int selectionSort(int *a);		//정렬되지않은 리스트에서 첫번째 원소와 첫 원소를 제외한 나머지 리스트에서 최소값을 찾아 배열을 정렬하는 선택정렬 함수
int insertionSort(int *a);		//정렬되어있는 부분집합에 새로운 원소의 위치를 찾아 삽입하여 배열을 정렬하는 삽입정렬 함수
int bubbleSort(int *a);			//배열의 원소의 크기만큼의 단계를 수행하면 최대값을 배열의 마지막 위치로 보내며 정렬하는 버블정렬 함수
int shellSort(int *a);			//삽입정렬을 개선하여 각 원소를 일정 간격만큼 떨어진 원소와 비교하여 정렬하는 셸정렬 함수
/* recursive function으로 구현 */
int quickSort(int *a, int n);	//pivot을 설정하여 pivot보다 작은 원소를 왼쪽 서브 리스트에, 큰 원소를 오른쪽 서브 리스트에 모아놓고 각각의 서브 리스트를 계속 정렬하는 Quick Sort 함수

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);			//key를 제산 함수를 사용하여 홈 주소를 반반하는 해시 함수

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);	//배열 a에 들어있는 모든 원소를 홈 주소를 구해 hash table에 저장하는 함수
	
/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);	//key가 들어있는 버킷의 인덱스 번호를 반환하는 함수


int main()
{
	char command;				//선택한 메뉴의 문자를 저장하는 문자형 변수
	int *array = NULL;			//정렬을 할 때 사용할 배열의 메모리 주소를 저장할 포인터 변수
	int *hashtable = NULL;		//하나 이상의 버킷으로 이루어진 hash table을 동적 메모리를 받아서 생성
	int key = -1;				//사용자가 버킷의 인덱스 번호를 찾고픈 key을 입력받아 저장하는 변수
	int index = -1;				//key값이 들어있는 버킷의 인덱스를 저장하는 변수

	srand(time(NULL));			//seed 값을 time으로 설정하여 프로그램 실행마다 랜덤값이 고정되지 않도록 함

	do {
		//프로그램의 메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		//원하는 메뉴 문자 입력
		printf("Command = ");
		scanf(" %c", &command);

		//사용자가 선택한 메뉴에 해당하는 case문 실행
		switch (command) {
		case 'z': case 'Z':			//선택한 메뉴가 z or Z이면
			initialize(&array);		//포인터 array에 배열 공간을 할당하는 함수 호출
			break;
		case 'q': case 'Q':			//선택한 메뉴가 q or Q이면
			freeArray(array);		//array가 할당받았던 공간을 해제하는 함수 호출
			break;
		case 's': case 'S':			//선택한 메뉴가 s or S이면
			selectionSort(array);	//array에 저장된 원소들을 선택정렬 방식을 이용하여 오름차순으로 정렬하는 함수 호출
			break;
		case 'i': case 'I':			//선택한 메뉴가 i or I이면
			insertionSort(array);	//array에 저장된 원소들을 삽입정렬 방식을 이용하여 오름차순으로 정렬하는 함수 호출
			break;
		case 'b': case 'B':			//선택한 메뉴가 b or B이면
			bubbleSort(array);		//array에 저장된 원소들을 버블정렬 방식을 이용하여 오름차순으로 정렬하는 함수 호출
			break;
		case 'l': case 'L':			//선택한 메뉴가 l or L이면
			shellSort(array);		//array에 저장된 원소들을 셸정렬 방식을 이용하여 오름차순으로 정렬하는 함수 호출
			break;
		case 'k': case 'K':			//선택한 메뉴가 k or k이면
			printf("Quick Sort: \n");				//Quick Sort임을 알려줌
			printf("----------------------------------------------------------------\n");
			printArray(array);						//정렬 전 배열의 상태를 출력하는 함수 호출
			quickSort(array, MAX_ARRAY_SIZE);		//array에 저장된 원소들을 퀵정렬 방식을 이용하여 오름차순으로 정렬하는 함수 호출
			printf("----------------------------------------------------------------\n");
			printArray(array);						//정렬 후 배열의 상태를 출력하는 함수 호출

			break;

		case 'h': case 'H':			//선택한 메뉴가 h or H이면
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);				//현재 배열의 상태를 출력하는 함수 호출
			hashing(array, &hashtable);		//array의 원소들을 홈 주소를 구해 hash table에 저장하는 함수 호출
			printArray(hashtable);			//해싱을 마친 뒤 hash table의 상태를 (각 버킷의 인덱스와 그곳에 들어있는 key값) 출력
			break;

		case 'e': case 'E':			//선택한 메뉴가 e or E이면
			printf("Your Key = ");
			scanf("%d", &key);					//버킷의 인덱스 번호를 찾고픈 key값을 입력
			printArray(hashtable);				//현재 hash table의 상태를 출력하는 함수 호출
			index = search(hashtable, key);		//key이 저장된 버킷의 인덱스 번호를 반환하는 함수 호출 및 반환값을 index에 저장
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':			//선택한 메뉴가 p or P이면
			printArray(array);		//현재 배열의 상태 (인덱스 번호와 그에 해당하는 원소)를 출력하는 함수 호출
			break;
		default:			//이외의 메뉴를 선택하면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");	//ERROR 메세지 출력
			break;
		}

	} while (command != 'q' && command != 'Q');		//사용자가 q or Q를 입력하기 전까지 계속 loop

	return 1;
}

int initialize(int** a)		//이중 포인터로 인자를 받음으로써 인자가 가리키고 있는 주소를 변경하도록 함
{
	int *temp = NULL;		//동적 할당한 메모리를 배열로 사용하기 위한 int형 포인터 선언 및 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	/* array가 NULL이 아닌 경우 */
	else
		temp = *a;		//현재 a에 할당된 메모리를 그대로 사용

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)	//동적 할당한 배열의 크기가 MAX_ARRAY_SIZE이므로 MAX_ARRAY_SIZE개의 원소를 랜덤 값으로 채우기 위한 for문
		temp[i] = rand() % MAX_ARRAY_SIZE;		//0~ (MAX_ARRAY_SIZE-1) 즉, 0 ~ 13 사이의 수 중 하나로 i번째 원소에 저장

	return 0;
}

int freeArray(int *a)	
{
	//a에 할당한 메모리가 존재한다면
	if (a != NULL)		
		free(a);	//해당 메모리 공간 해제(포인터 a는 살아있음, 공간만 해제)
	return 0;
}

void printArray(int *a)
{
	//a에 할당된 메모리가 없다면
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	//a에 할당된 메모리가 있다면 즉, 배열 존재
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)	//배열의 크기 MAX_ARRAY_SIZE만큼 for문 실행하여 배열의 모든 인덱스 출력
		printf("a[%02d] ", i);					//해당 배열의 인덱스 번호 출력 (0번부터 시작)
	printf("\n");							
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)	//배열의 크기 MAX_ARRAY_SIZE만큼 for문 실행하여 배열의 모든 원소 출력
		printf("%5d ", a[i]);					//i번째 인덱스에 해당하는 원소를 일정한 간격에 맞춰 출력
	printf("\n");
}


int selectionSort(int *a)
{
	int min;		//정렬이 아직 안됀 원소 중에서 가장 작은 값을 저장
	int minindex;	//정렬이 아직 안된 원소 중에서 가장 작은 값을 가지고 있는 인덱스 저장
	int i, j;		//i는 기준 위치, j는 최소값이 있는 인덱스를 저장하는 변수

	//selection Sort임을 알림
	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");


	printArray(a);	//현재 배열의 상태를 출력하는 함수 호출

	for (i = 0; i < (MAX_ARRAY_SIZE-1); i++)	//배열의 처음부터 마지막 원소를 제외한 부분까지 for문을 돌며 (기준 위치)
	{
		minindex = i;		//정렬이 되지 않은 리스트 중 첫번째 원소 가리킴
		min = a[i];			//정렬되지 않은 리스트 중 첫번째 원소의 값을 최소값으로 설정
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)  //배열의 2번째부터 마지막 원소까지 for문을 돌며 기준 위치와 값 비교
		{
			if (min > a[j])  //j번째 원소가 min보다 작은 값이면
			{
				min = a[j];		//min값을 j번쨰 원소로 변경
				minindex = j;	//최소값이 저장된 인덱스의 번호를 j로 수정
			}
		}
		//정렬
		a[minindex] = a[i];		//최소값인 j번째 원소보다 큰 값을 갖는 i번째 원소를 j번째로 보냄
		a[i] = min;				//정렬되지 않은 리스트 중 가장 작은 값을 기준 위치 i번째로 보냄
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);			//정렬을 완료한 배열의 상태를 출력하는 함수 호출
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	//insertion Sort임을 알림
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//정렬 전 배열의 상태를 출력

	for (i = 1; i < MAX_ARRAY_SIZE; i++)	//0번째를 정렬되어있다고 간주하고 1번째부터 마지막 원소까지 for문 실행
	{
		t = a[i];	//정렬되지 않은 리스트 중 첫번째 원소의 값을 t에 저장
		j = i;		//정렬되지 않은 리스트 중 첫번째 원소의 인덱스를 j에 저장
		while (a[j - 1] > t && j > 0) //j의 인덱스가 0보다 크고 정렬된 리스트의 마지막 원소부터 비교하여 t값이 작다면
		{
			a[j] = a[j - 1]; //j번째 원소보다 j-1번째 원소가 더 크므로 j-1의 값을 한 칸 뒤로 이동
			j--;			 //j의 인덱스 번호를 한 칸 앞으로 이동 (정렬된 리스트를 뒤에서 앞으로 가면서 계속 비교)
		}
		a[j] = t;			//정렬이 필요한 원소 t가 올바른 인덱스 j에 저장 (정렬 완료)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬을 완료한 배열의 상태를 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	//Bubble Sort임을 알림
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//정렬 전 배열의 상태를 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)		//배열의 크기만큼 for문을 실행하여 매 단계마다 가장 큰 원소가 마지막 자리로 오도록 함
	{	
		for (j = 1; j < MAX_ARRAY_SIZE; j++)	//첫번째 원소부터 시작하여 이전 원소(인접 원소)를 계속 비교
		{
			if (a[j - 1] > a[j])	//j번째의 인접 원소가 j의 원소보다 크다면 (swap 필요)
			{
				t = a[j - 1];		//swap하기 전에 임시로 j-1번쨰 원소의 값 저장 (데이터 손실 예방)
				a[j - 1] = a[j];	//j-1번째에 둘 중 더 작은 값인 j번재 원소가 이전 인덱스에 저장
				a[j] = t;			//둘 중 더 큰 값인 j-1번째 원소를 j의 자리에 저장 ( 안쪽 for문이 끝나면 한 단계 정렬 완료)
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);		//정렬 후의 배열의 상태를 출력하는 함수 호출

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	//Shell Sort임을 알려줌
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//정렬 전의 배열의 상태를 출력
	
	//h = 1이면 insertion 적용
	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)		//간격 h는 배열의 크기의 1/2부터 시작하고 한 단계가 수행될 떄 마다 h의 값을 1/2로 감소시킴
	{
		for (i = 0; i < h; i++)		//첫번째 부분집합의 기준을 h으로 설정하고 0번째부터 h-1번째까지 for문
		{
			//i를 기준으로 어느 정도 정렬 실행
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)		//i번째에서 h만큼 떨어진 원소들과 비교
			{
				v = a[j];	//i에서 h만큼 떨어진 j번째 원소의 값을 v에 저장
				k = j;		//인덱스 j의 값을 k에 저장
				while (k > h - 1 && a[k - h] > v)	
				{   //k의 값이 두번째 부분집합의 첫번째 인덱스와 같거나 크고, i의 원소보다 h 간격만큼 떨어진 j의 원소가 작다면 (정렬 필요)
					a[k] = a[k - h];	//둘 중 더 큰 값을 뒤의 위치 즉, j번째 위치에 j 이전의 h만큼 떨어진 원소 저장
					k -= h;				//k가 i에서 h만큼 한 번 이상 떨어진 곳의 인덱스이므로 h만큼 빼줌으로써 이전의 h만큼 떨어진 인덱스로 이동
										//계속하다보면 k = i가 되는 순간 도달 or k-h가 k의 원소보다 작은 순간 도달
				}
				a[k] = v;				//j번째의 원소를 while문을 탈출했던 k번째에 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);		//정렬 후의 배열의 상태를 출력하는 함수 호출

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)			//서브 리스트의 원소가 2개 이상일 경우(즉, 서브 리스트의 원소가 하나일 경우에는 정렬 필요X)
	{
		v = a[n - 1];	//배열의 마지막 원소를 v에 저장
		i = -1;			//-1로 설정함으로서 배열의 첫번째 원소부터 접근할 수 있도록 함
		j = n - 1;		//배열의 마지막 인덱스 번호를 j에 저장
			
		while (1)		//무한 loop
		{
			//배열의 마지막 원소를 pivot으로 정하고 
			while (a[++i] < v);		//i번째 원소가 pivot보다 커질 때까지 i 증가
			while (a[--j] > v);		//i번째 원소가 pivot보다 작아질 때까지 i 증가

			if (i >= j) break;		//i번째 원소가 pivot보다 크고 j번째 원소가 pivot보다 작을 때 while 탈출 
									//즉, 해당 서브 리스트에 i이후에는 큰 값만, j이전에는 작은 값만 모임
			//i와 j가 접전이 없는데 i 원소는 pivot보다 크고 j 원소는 pivot보다 작으면 서로 swap해야함 (후에 양쪽 서브 리스트로 나누기 위해 필요)
			t = a[i];				//t에 임시로 i번째 원소 저장		
			a[i] = a[j];			//i번째에 j번째 원소 저장
			a[j] = t;				//j번째에 i번쨰 원소 저장
		}
		//i와 j가 서로를 크로스했을 때
		t = a[i];			//t에 i번째 원소를 임의로 저장
		a[i] = a[n - 1];	//i이전에는 pivot보다 작은 값이 있으므로 i번째에 pivot 저장
		a[n - 1] = t;		//pivot이 있던 배열의 마지막 위치에 t에 저장되었던 큰 값 저장

		//recursive하면서 pivot의 위치를 계속 지정하며 배열의 원소를 정렬해나감
		quickSort(a, i);					//pivot보다 작은 값이 모여있는 리스트를 Quick Sort로 정렬 (0번째부터 i-1번째 원소를 정렬)
		quickSort(a + i + 1, n - i - 1);	//pivot보다 큰 값이 모여있는 리스트를 Quick Sort로 정렬 (pivot 다음의 원소부터 마지막 원소까지 정렬)
	}

	return 0;
}

int hashCode(int key) {
	//해시 함수 중 제산 함수 사용
	return key % MAX_HASH_TABLE_SIZE;	//key을 hash table의 크기로 나눈 나머지를 return == key의 홈 주소
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;		//hash table을 생성할 포인터를 NULL로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)	//hash table의 모든 MAX_HASH_TABLE_SIZE개의 버킷에 값을 저장할 for문
		hashtable[i] = -1;	//i번째 버킷에 -1 저장

	/* 버킷에 값이 잘 들어갔는지 확인하는 code
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;			//hash table에 들어갈 key을 저장할 변수
	int hashcode = -1;		//key값의 처음으로 구한 홈 주소를 저장할 변수
	int index = -1;			//key의 새로운 홈 주소를 저장하는 변수 
		
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)	//배열 a에 저장된 원소들을 홈 주소를 구해 hash table에 저장하기 위한 for문
	{
		key = a[i];		//현재 배열에서 i번째 원소를 key에 저장
		hashcode = hashCode(key);	//제산 함수를 이용해 key의 홈 주소를 반환하는 함수를 호출하여 key의 홈 주소를 hashcode에 저장
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)	//만약 해당 주소의 버킷에 -1이 들어있다면 (hash table이 생성된 후 처음으로 key 삽입
		{
			hashtable[hashcode] = key;	//해당 버킷이 key값 저장
		}
		else {	//만약 해당 주소의 버킷이 -1이 아니라면 (hash table에 이미 다른 값이 들어가있다면(-1 말고))

			index = hashcode;	//제산 함수로 구했던 홈 주소를 index에 저장

			while (hashtable[index] != -1)	//index에 해당하는 버킷에 -1 이외의 값이 들어있다면(즉, 이미 버킷에 다른 key 저장)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;	//다음 버킷의 인덱스 번호(증가한 index가 마지막 인덱스를 넘어가면 0번째로)를 index에 저장
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;		//새로 구한 인덱스에 다른 key값이 들어있지 않다면 key값 저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);	//제산 함수를 이용하여 key의 홈 주소를 반환하는 함수 호출 후 반환값을 index에 저장

	if (ht[index] == key)		//만약 hash table의 index번째 버킷에 들어있는 값과 key가 동일하다면
		return index;			//index 반환
	//만약 hash table의 index번째 버킷에 들어있는 값과 key가 달라서
	while (ht[++index] != key)					//다음 버킷에 들어있는 값과 key이 동일하지 않다면
	{
		index = index % MAX_HASH_TABLE_SIZE;	//다시 배열의 크기로 나눠 새로운 홈 주소를 구해 index에 저장
	}
	return index;		//새로운 홈 주소의 버킷에 key과 동일한 값이 들어있다면 index 반환
}


