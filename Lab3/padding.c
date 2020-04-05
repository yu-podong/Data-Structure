#include <stdio.h>

struct student{			//struct 키워드를 이용하여 여러 변수들을 그룹화하는 새로운 자료형 student 정의
	char lastName[13];	//char형 배열lastName 선언, 13*sizeof(char) =  13 byte
	int studentId;		//int형 변수 student 선언, sizeof(int) = 4 byte
	short grade;		//shor형 변수 grade 선언, sizeof(short) = 2 byte
};

int main()
{
	struct student pst;						//struct student형 즉, 구조체인 pst 변수를 선언

	printf("size of student = %ld\n", sizeof(struct student));	//struct student형은 이 자료형 안에 선언된 멤버 변수의 크기의 총 합
									//but padding 발생 -> 4byte씩 메모리 경계 -> 13byte인 경우 빈 공간인 3byte 채움, short형일 경우 빈 공간인 2byte 채움
	printf("size of int = %ld\n", sizeof(int));			//int형의 크기 출력 = 4byte
	printf("size of short = %ld\n", sizeof(short));			//short형의 크기 출력 = 2byte

	return 0;
}
