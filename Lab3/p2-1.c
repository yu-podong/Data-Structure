#include <stdio.h>
#define MAX_SIZE 100	//기호 상수를 사용하여 100을 MAX_SIZE로 사용

float sum(float [], int);		//float형 배열과 int형 변수를 매개변수로 사용하고 반환값은 float형인 함수 sum 원형
float input[MAX_SIZE], answer;	//MAX_SIZE개의 float형 데이터를 저장하는 배열과 float형 변수를 전역 변수로 선언
int i;	//int형 변수를 전역 변수로 선언

void main(void)
{
	for(i = 0; i < MAX_SIZE; i++)	//0부터 MAX_SIZE-1번째 배열의 원소에 value를 저장하기 위한 for문
		input[i] = i;	//input의 i번째 원소에 i를 저장

	//for checking call by reference
	printf("address of input = %p\n", input);	//배열의 이름은 배열의 시작주소 즉, 배열의 첫번째 원소의 주소이므로 list[0]의 주소 출력

	answer = sum(input, MAX_SIZE);				//input의 주소와 MAX_SIZE를 받아서 함수 sum을 호출해 input의 원소들의 합을 구한 후 float형으로 반환한 값을 answer에 저장
	printf("The sum is :%f\n", answer);			//input의 원소들의 합인 answer의 값 출력
}
float sum(float list[], int n)	//인수를 각각 매개 변수 float형 배열과 int형 변수로 받아서 input의 각 원소들의 합을 구하는 함수 sum
{
	printf("value of list = %p\n", list);			//list의 값 출력 즉, 인수인 input(= &input[0]) <-배열의 이름 == 배열의 시작주소 == &input[0]
	printf("address of list = %p\n\n", &list);		//매개변수는 메모리에 할당되기 때문에 list가 위치한 메모리 주소 출력 != input becuase list는 input(= &input[0])을 받는 변수이기 때

	int i;	//지역 변수 i 선언 <- 같은 이름의 지역 변수가 선언되면 지역 변수를 우선으로 생각 즉, 전역 변수 i와 다름
	float tempsum = 0;			//float형의 변수 선언 후 0으로 초기화
	for(i = 0; i < n; i++)		//0부터 n-1(=MAX_SIZE-1)번째 원소의 합을 구하기 위한 for문
		tempsum += list[i];		//list[i]의 값을 float형 변수 tempsum에 저장
	return tempsum;				//tempsum의 값을 반환
}