#include <stdio.h>

struct student1{	//struct 키워드를 이용하여 여러 변수를 그룹화하는 student1이라는 새로운 자료형 정의
	char lastName;	//문자 한 개를 저장하는 char형 멤버 변수
	int studentId;	//int형 value를 저장하는 int형 멤버 변수
	char grade;		  //문자 한 개를 저장하는 char형 멤버 변수
};

typedef struct{		//struct 키워드를 이용하여 여러 변수를 그룹화하는 새로운 자료형 정의
	char lastName;	//문자 한 개를 저장하는 char형 변수
	int studentId;	//int형 value를 저장하는 int형 변수
	char grade;		  //문자 한 개를 저장하는 char형 변수
} student2;			  //typedef를 이용하여 새로운 자료형을 student2라는 이름으로 사용 가능

int main()
{
	struct student1 st1 = {'A', 100, 'A'};			      //struct student1형 즉, 구조체인 st1 변수를 선언 후 각각의 멤버 변수을 'A', 100, 'A'로 초기화

	printf("st1.lastName = %c\n", st1.lastName);	    //st1의 멤버 변수 lastName의 값 출력 즉, A 출력
	printf("st1.studentId = %d\n", st1.studentId);   	//st1의 멤버 변수 studentId의 값 출력 즉, 100 출력
	printf("st1.grade = %c\n", st1.grade);			      //st1의 멤버 변수 grade의 값 출력 즉, A 출력

	student2 st2 = {'B', 100, 'B'};					          //student2형 즉, 구조체인 st2 변수를 선언 후 각각의 멤버 변수를 'B',100, 'B'로 초기화

	printf("\nst2.lastName = %c\n", st2.lastName);	  //st2의 멤버 변수 lastName의 값 출력 즉, B 출력
	printf("st2.studentId = %d\n", st2.studentId);	  //st2의 멤버 변수 studentId의 값 출력 즉, 100 출력
	printf("st2.grade = %c\n", st2.grade);			      //st2의 멤버 변수 grade의 값 출력 즉, B 출력

	student2 st3;									                    //student2형 즉, 구조체인 st3 변수를 선언

	printf("\nst3.lastName = %c\n", st3.lastName);  	//st3의 멤버 변수 lastName의 값 출력
	printf("st3.studentId = %d\n", st3.studentId);	  //st3의 멤버 변수 studentId의 값 출력
	printf("st3.grade = %c\n", st3.grade);			      //st3의 멤버 변수 grade의 값 출력

	//equality test <- 실제로 실행했을 시 error 발생, 밑의 코드의 주석은 그 코드가 의미하는 바를 적

	//if(st3 == st2)				                          //두 구조체의 전제 구조 동등성 검사 즉, 두 구조체의 각각의 변수가 같은 값을 갖는지 검사
	//    printf("equal\n);		                      	//만약, 두 구조체의 각각의 변수들이 서로 같은 값을 가진다면 equal 문구 출력
	//else							                              //두 구조체의 각각의 변수 중 하나라도 같은 값을 갖지 않는다면
	//    printf("not equal\n*);	                    //not equal 문구 출력

	return 0;
}
