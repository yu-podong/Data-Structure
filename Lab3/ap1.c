#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5];			//int형 데이터를 저장하는 배열
	int *plist[5] = {NULL,};	//주소를 저장하는 포인터 배열 선언 및 NULL로 초기화

	plist[0] = (int *)malloc(sizeof(int));	//plist[0]에 malloc함수를 이용해 int의 크기만큼 할당한 메모리의 주소를 저장

	list[0] = 1;		//list[0]에 1을 저장
	list[1] = 100;		//list[1]에 100을 저장

	*plist[0] = 200;	//plist[0]이 가리키는 주소에 200을 저장

	printf("-----------유현진  2019038006-----------\n");
	printf("value of list[0] = %d\n", list[0]);		//list[0]에 저장된 값을 출력
	printf("address of list[0]      = %p\n", &list[0]);	//list[0]의 주소를 출력
	printf("value of list           = %p\n", list);		//list의 주소(= &list[0]) 출력 -> 배열의 이름은 배열의 시작주소를 가리킴
	printf("address of list (&list) = %p\n", &list);	//&list == list == &list[0]

	printf("----------------------------------------\n\n");
	printf("value of list[1]   = %d\n", list[1]);		//list[1]의 값 출력
	printf("address of list[1] = %p\n", &list[1]);		//list[1]의 주소 출력 == list + 1(=sizeof(int))
	printf("value of *(list+1) = %d\n", *(list+1));		// *(list + 1)의 값 출력 == list[1]
	printf("address of list+1  = %p\n", list+1);		//list + 1의 주소 출력 == &list[1]

	printf("----------------------------------------\n\n");
	printf("value of *plist[0] = %d\n", *plist[0]);		// *plist[0] == plist[0]이 가리키는 주소에 있는 값을 출력
	printf("&plist[0]          = %p\n", &plist[0]);		//plist[0]의 주소 출력
	printf("&plist             = %p\n", &plist);		//&plist == plist == &plist[0]
	printf("plist              = %p\n", plist);		//plist == &plist[0] <- 배열의 이름은 배열의 시작주소를 가리킴
	printf("plist[0]           = %p\n", plist[0]);		//pplist[0]에 저장된 주소 출력 <- 메모리 내에서 200을 가지고 있는 주소 출력
	printf("plist[1]           = %p\n", plist[1]);		//plist[1]에 저장된 주소 출력 <- 초기화 이후 주소받은 적이 없기 때문에 nil 출력
	printf("plist[2]           = %p\n", plist[2]);		//plist[2]에 저장된 주소 출력 <- 초기화 이후 주소받은 적이 없기 때문에 nil 출력
	printf("plist[3]           = %p\n", plist[3]);		//plist[3]에 저장된 주소 출력 <- 초기화 이후 주소받은 적이 없기 때문에 nil 출력
	printf("plist[4]           = %p\n", plist[4]);		//plist[4]에 저장된 주소 출력 <- 초기화 이후 주소받은 적이 없기 때문에 nil 출력

	free(plist[0]);	//malloc을 이용하여 메모리를 할당했을 경우 메모리 누수를 방지하기 위해 해제시켜야함 = 해당 메모리를 다른 변수가 사용할 수 있도록 하기 위해
}
