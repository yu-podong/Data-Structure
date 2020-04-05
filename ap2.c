#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5];	  //int형 데이터를 5개 저장하는 배열
	int *plist[5];	//주소 5개를 저장하는 포인터 배열

	list[0] = 10;	  //list의 첫번째 요소에 10 저장
	list[1] = 11;	  //list의 두번째 요소에 11 저장

	plist[0] = (int *)malloc(sizeof(int));	//plist[0]에 malloc함수를 이용하여 int 크기만큼 할당한 메모리의 주소를 저장

	printf("list[0] \t= %d\n", list[0]);				      //list[0]에 들어있는 int형 value를 출력
	printf("address of list \t= %p\n", list);			    //배열의 이름은 배열의 시작 주소이므로 list[0]의 주소 출력
	printf("address of list[0] \t= %p\n", &list[0]);	//list[0]의 주소 출력 == list
	printf("address of list + 0 \t= %p\n", list + 0);	//list+0은 list에서 0만큼 떨어진 곳 즉, list를 뜻하므로 list[0]의 주소 출력(list == &list[0])
	printf("address of list + 1 \t= %p\n", list + 1);	//list+1은 list에서 1만큼 떨어진 곳 즉, list+1*sizeof(int)를 뜻하므로 list에서 int의 크기는 4byte를 더한 주소 출력(= list + 4)
	printf("address of list + 2 \t= %p\n", list + 2);	//list+2은 list에서 2만큼 떨어진 곳 즉, list+2*sizeof(int) == list+8의 결과인 주소 출력
	printf("address of list + 3 \t= %p\n", list + 3);	//list+3은 list에서 3만큼 떨어진 곳 즉, list+3*sizeof(int) == list+12의 결과인 주소 출력
	printf("address of list + 4 \t= %p\n", list + 4);	//list+4은 list에서 4만큼 떨어진 곳 즉, list+4*sizeof(int) == list+16의 결과인 주소 출력
	printf("address of list[4] \t= %p\n", &list[4]);	//list[4]의 주소 출력 == list + 4

	free(plist[0]);	//동적 할당으로 받은 메모리를 해제 because 해제하지 않으면 다른 변수가 더이상 사용하지 않는 그 메모리를 사용할 수 없기 때문에 즉, 메모리 누수 발생 방지
}
