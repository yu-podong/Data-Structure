#include <stdio.h>

void print1(int *ptr, int rows);			//int형을 가리키는 포인터 변수와 int형 변수를 매개변수로 하고 반환값은 없는 함수 print1의 원형

int main()
{
	int one[] = {0, 1, 2, 3, 4};			//5개의 int형 value를 갖는 배열 one을 선언하고 각각의 원소를 0,1,2,3,4로 초기화

	printf("one     = %p\n", one);			//배열의 이름은 배열의 시작주소이기 때문에 one[0]의 주소 출력
	printf("&one     = %p\n", &one);		//one의 위치는 one[0]와 동일하기 때문에 one[0]의 주소와 같은 주소 출력
	printf("&one[0]     = %p\n", &one[0]);		//one[0]의 주소 출력 == one == &one
	printf("\n");					//한 줄 개행

	print1(&one[0], 5);				//인수 one[0]의 주소와 5를 매개변수로 받아서 print함수를 이용해 각 원소의 주소와 값을 출력하는 print1 함수 호출
	return 0;
}
void print1(int *ptr, int rows)					//인수를 각각 포인터 변수 ptr과 int형 변수 rows인 매개 변수로 받고 반환값은 없는 함수 print1의 정의
{
	int i;							//int형 value를 저장하는 변수 선언
	printf("Address \t Contents\n");			//"Address Contents" 문구 출력
	for(i = 0;i < rows; i++)				//for문을 rows번 돌면서 ptr+i와 해당 주소에 들어있는 값을 출력
		printf("%p \t %5d\n", ptr + i, *(ptr + i));	//ptr이 int형을 가리키기 때문에 주소인 ptr+i*sizeof(int)와 ptr+i*sizeof(int)에 들어있는 값을 출력
	printf("\n");						//한 줄 개행
}
