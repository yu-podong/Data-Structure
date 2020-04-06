#include <stdio.h>
#include <stdlib.h>

void main()
{
	int **x;	//주소를 가리키는 변수의 주소를 가리키는 포인터 변수 즉, 이중 포인터 x 선언
	
	printf("-----------유현진  2019038006-----------\n");
	printf("sizeof(x) = %lu\n", sizeof(x));			//64bit 운영 체제에서 주소는 8byte으로 주소를 저장하는 x의 크기는 8byte와 같음
	printf("sizeof(*x) = %lu\n", sizeof(*x));		// *x = x가 가리키는 주소에 들어있는 값 즉, 또 다른 주소를 가지고 있는 메모리의 주소이므로 *x의 크기는 8byte와 같음
	printf("sizeof(**x) = %lu\n", sizeof(**x));		// **x = *x가 가리키고 있는 주소에 들어있는 값 즉, int형 value이므로 int의 크기인 4byte와 같음
}
