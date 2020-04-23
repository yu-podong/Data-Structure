#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10				//10이라는 수를 MAX_STACK_SIZE라는 기호 상수로 선언
#define MAX_EXPRESSION_SIZE 20				//20이라는 수를 MAX_EXPRESSION_SIZE라는 기호 상수로 선언

//stack 내에서 우선순위, lparen = 0 가장 낮음
typedef enum {			//각 operater와 operand의 우선순위를 표현한 데이터를 열거한 열거형(enum) 정의
	lparen = 0,		// ( 왼쪽 괄호
	rparen = 9,		// ) 오른쪽 괄호
	times = 7,		// * 곱셈
	divide = 6,		// / 나눗
	plus = 5,		// + 덧셈
	minus = 4,		// - 뺄셈
	operand = 1		// 피연산자
} precedence;			//해당 열거형을 precedence라는 이름으로 정의


char infixExp[MAX_EXPRESSION_SIZE];   	//infix expression을 저장하는 배열
char postfixExp[MAX_EXPRESSION_SIZE];	//postfix로 변경된 문자열을 저장하는 배열
char postfixStack[MAX_STACK_SIZE];	//postfix로 변환을 위해 필요한 스택
int evalStack[MAX_STACK_SIZE];		//계산을 위해 필요한 스택

int postfixStackTop = -1;		//postfixStack용 top
int evalStackTop = -1;			//evalStack용 top
int evalResult = 0;			//계산 결과를 저장
int div_0 = 0;				//수식 계산 중 0으로 나누는 경우를 판별하기 위함

void postfixPush(char x)					//postfixStack에 top에 위치한 연산자보다 높은 우선순위를 가지고 있는 연산자를 다음 위치에 삽입하는 함수 정의
{
	postfixStack[++postfixStackTop] = x;			//현재 top의 위치를 1 증가시킨 자리에 x에 저장된 연산자를 스택에 삽입
}
char postfixPop()						//postfixStack에 top 위치의 연산자보다 낮은 우선순위의 연산자일 경우 top에 위치한 연산자를 출력하는 함수 정의
{
	char x;							//top에 위치한 연산자를 저장할 문자형 변수 선언
	if (postfixStackTop == -1)				//만약 스택의 모든 원소를 출력했을 경우
		return '\0';					//수식이 끝났다는 문자인 '\0' 반환
	else {							//스택에 아직 남아있는(출력하지 못한) 연산자가 있을 경우
		x = postfixStack[postfixStackTop--];		//현재 top위치에 있는 연산자를 x에 저장하고 top의 위치를 1 감소
	}
	return x;						//x에 저장된 연산자 반환
}
int evalPop()							//evalStack에 저장된 operand를 꺼내는 함수 정의
{
	if (evalStackTop == -1)					//만약 top의 위치가 -1일 경우 즉, 꺼낼 operand가 없다면
		return -1;					//비정상적인 실행임을 나타내는 -1 반환
	else							//만약 top이 evalStack에 남아있는 operand를 가리키고 있다면
		return evalStack[evalStackTop--];		//top에 있는 operand를 반환한 후 top의 위치를 1 감소
}
void evalPush(int x)						//token이 operand일 경우 evalStack에 token을 삽입할 함수 정의
{
	evalStack[++evalStackTop] = x;				//현재 top의 위치를 1 증가시킨 자리에 x에 저장된 operand를 스택에 삽입
}
void getInfix()							//사용자가 원하는 infix expression을 입력하는 함수 정의
{
	printf("Type the expression >>> ");			//수식을 입력하라는 message 출력
	scanf("%s", infixExp);					//계산하고픈 infix방식의 expression을 입력한 후 infixExp에 저장
}
precedence getToken(char symbol)				//인자로 받은 문자를 문자형 변수로 받아 우선순위를 알려주는 함수 정의
{
	switch (symbol) {					//symbol의 값에 따라 case를 비교하여 해당하는 case의 문장을 실행
	case '(': return lparen;				//symbol이 '('이면 lparen 출력
	case ')': return rparen;				//symbol이 ')'이면 rparen 출력
	case '+': return plus;					//symbol이 '+'이면 plus 출력
	case '-': return minus;					//symbol이 '-'이면 minus 출력
	case '/': return divide;				//symbol이 '/'이면 divide 출력
	case '*': return times;					//symbol이 '*'이면 times 출력
	default: return operand;				//symbol이 위의 경우 이외의 문자 즉, 피연산자이면 operand 값을 출력
	}
}
precedence getPriority(char x)					//인자의 우선순위를 반환하는 함수 정의
{
	return getToken(x);					//getToken 함수를 호출하여 인자의 우선순위를 알아냄
}
void charCat(char* c)						//infixExp의 문자 하나를 postfixExp 뒤쪽에 연결시켜주는 함수 정의
{
	if (postfixExp == '\0')					//postfixExp가 비어있는 상태라면
		strncpy(postfixExp, c, 1);			//인자로 받은 문자를 postfixExp 뒤에 이어붙임
	else							//만약 postfixExp가 infixExp를 변환하고 있는 중이라면
		strncat(postfixExp, c, 1);			//인자로 받은 문자를 postfixExp 뒤에 이어붙임
}
void toPostfix()											//infixExp를 postfix방식 exprsstion으로
{
	char *exp = infixExp;										//infixExp의 주소를 받아 해당 배열의 문자열을 사용할 포인터 변수 선언
	precedence prio;										//각 수식의 token의 우선순위를 저장한 변수 선언
	char temp;											//문자하나를 저장하기 위한 변수 선언

	while (*exp != '\0') {										//*exp가 '\0'이 아닐 경우 즉, infixExp에 들어있는 수식의 끝이 아닐 경우, while문 실행
		prio = getPriority(*exp);								//수식의 각 operator나 operand의 우선순위를 getPriority 함수를 호출하여 구한 후 prio에 저장

		if (prio == operand)									//prio가 operand의 값을 가진 경우
			charCat(exp);									//charCat 함수를 호출하여 수식 exp 중 하나의 문자를 postfixExp에 복사
		else if (prio == lparen)								//prio가 lparen의 값을 가진 경우
			postfixPush(*exp);								//postfixPush 함수를 호출하여 수식의 토큰을 postfixStack에 삽입
		else if (prio == rparen) {								//prio가 rparen의 값을 가진 경우
			for (; postfixStack[postfixStackTop] != '('; ) {				//top의 위치를 옮겨 '('를 만날 떄까지 스택에 들어있는 원소를 pop하기 위한 for문
				temp = postfixPop();							//postfixPop 함수를 호출하여 postsfixStack 마지막 원소를 temp에 저장
				charCat(&temp);								//charCat 함수를 이용하여 temp을 postfixExp 뒤에 이어붙임
				postfixStack[postfixStackTop + 1] = '\0';				//temp에 들어있던 원소의 위치에 아직 temp이 남아있기 때문에 pop을 구현하기 위해 해당 위치에 '\0' 삽입
			}
			postfixStack[postfixStackTop--] = '\0';						//top의 위치에 있는 '('를 삭제하고 top의 위치를 1 감소
		}
		else if (prio == plus && getPriority(postfixStack[postfixStackTop]) == minus) {		//원래는 우선순위가 같지만 설정한 enum에 의해서 plus가 minus보다 우선순위가 커서 minus가 pop되지 않고 plus가 쌓이게 되는 현상을 막고자하는 조건
			temp = postfixPop();								//postfixPop 함수를 호출하여 postsfixStack 마지막 원소를 temp에 저장
			charCat(&temp);									//charCat 함수를 이용하여 temp을 postfixExp 뒤에 이어붙임
			postfixPush(*exp);								//postfixStack에 마지막 원소가 들어있던 자리에 *exp를 삽입
		}
		else if (prio == times && getPriority(postfixStack[postfixStackTop]) == divide) {	//원래는 우선순위가 같지만 설정한 enum에 의해서 times가 divide보다 우선순위가 커서 divide가 pop되지 않고 times가 쌓이게 되는 현상을 막고자하는 조건
			temp = postfixPop();								//postfixPop 함수를 호출하여 postsfixStack 마지막 원소를 temp에 저장
			charCat(&temp);									//charCat 함수를 이용하여 temp을 postfixExp 뒤에 이어붙임
			postfixPush(*exp);								//postfixStack에 마지막 원소가 들어있던 자리에 *exp를 삽입
		}
		else if (prio > getPriority(postfixStack[postfixStackTop]) || postfixStackTop == -1)	//prio가 현재 top의 우선순위보다 크거나 top의 위치가 -1일 경우
			postfixPush(*exp);								//postfixPush 함수를 호출하여 수식의 토큰을 postfixStack에 삽입
		else if (prio <= getPriority(postfixStack[postfixStackTop])) {				//prio가 현재 top의 우선순위보다 작거나 같은 경우
			for (; prio < postfixStack[postfixStackTop]; ) {				//top의 위치를 옮겨 prio가 top에 위치한 연산자의 우선순위보다 높아질 때까지 스택에 들어있는 원소를 pop하기 위한 for문
				temp = postfixPop();							//postfixPop 함수를 호출하여 postsfixStack 마지막 원소를 temp에 저장
				charCat(&temp);								//charCat 함수를 이용하여 temp을 postfixExp 뒤에 이어붙임
				postfixStack[postfixStackTop + 1] = '\0';				//temp에 들어있던 원소의 위치에 아직 temp이 남아있기 때문에 pop을 구현하기 위해 해당 위치에 '\0' 삽입
			}
			postfixPush(*exp);								//postfixStack에 마지막 원소가 들어있던 자리에 *exp를 삽입
		}
		exp++;											//exp를 증가시켜 수식의 다음 token을 가리킴
	}
	for (; postfixStackTop != -1; ) {								//postfixStack에 남아있는 연산자를 출력하기 위한 for문
		temp = postfixPop();									//postfixPop 함수를 호출하여 postsfixStack 마지막 원소를 temp에 저장
		charCat(&temp);										//charCat 함수를 이용하여 temp을 postfixExp 뒤에 이어붙임
	}
}
void debug()							//입력한 수식, postfix방식의 expression, 수식의 결과값과 postfixStack에 남아있는 원소를 출력해주는 함수 정의
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);			//사용자가 입력했던 수식 출력
	printf("postExp =  %s\n", postfixExp);			//사용자가 입력했던 수식을 postfix방식으로 변환한 expression 출력
	if(div_0 != -1)						//만약 수식 중 0으로 나누는 구간이 없는 경우
		printf("eval result = %d\n", evalResult);	//해당 수식의 결과값을 출력
	else							//수식 중에서 어떤 수를 0으로 나누는 구간이 있는 경우
		printf(">>> You can't divide by 0 <<<\n");	//ERROR message 출력

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)		//스택에 쌓여있던 연산자를 출력하기 위한 for문
		printf("%c  ", postfixStack[i]);		//스택의 i번째 위치에 존재하는 연산자 출력

	printf("\n");

}
void reset()							//모든 것을 처음 상태로 만들기 위한 함수 정의
{
	infixExp[0] = '\0';					//사용자가 입력한 수식을 저장하는 문자열 배열을 '\0'을 이용해 reset
	postfixExp[0] = '\0';					//사용자가 입력한 수식을 postfix expression으로 변환한 문자열 배열을 '\0'을 이용해 reset

	for (int i = 0; i < MAX_STACK_SIZE; i++)		//스택에 들어있던 원소들을 비우기 위한 for문
		postfixStack[i] = '\0';				//i번째에 해당하는 원소를 '\0'로 reset

	postfixStackTop = -1;					//postfixStack의 top의 위치를 -1로 초기화
	evalStackTop = -1;					//evalStack의 top의 위치를 -1로 초기화
	evalResult = 0;						//수식의 결과값을 저장하는 변수를 0으로 초기화
	div_0 = 0;						//수식 중 0으로 나누는 구간이 있는지 판별하기 위해 0으로 초기화
}
void evaluation()							//postfixExp를 기반으로 사용자가 입력한 수식을 계산하여 결과값을 알아내는 함수 정의
{
	precedence token;						//postfixExp의 한 문자가 operand인지 operator인지를 저장하는 변수 선언
	char *postexp = postfixExp;					//postfixExp의 주소를 저장하여 해당 문자열을 사용할 포인터 변수 선언
	int num1 = 0, num2 = 0;						//연산자는 두 개의 operand가 필요한 이항 연산자이므로 2개 operand를 저장할 변수 2개 선언 후 0으로 초기화

	while (*postexp != '\0')					//*postexp가 수식의 끝인 '\0'이 아니라면 즉, operand나 operator일 경우
	{
		token = getToken(*postexp);				//getToken 함수를 호출하여 현재 postexp가 operand인지 operator인지 알아내어 token에 저장

		if (token == operand)					//token이 operand 즉 , 피연산자일 경우
			evalPush((*postexp) - '0');			//현재 *postexp 즉, 문자형인 숫자를 '0'의 아스키 값을 빼 정수형 숫자로 변환한 뒤 evalPush 함수를 호출하여 evalStack에 저장
		else {							//token이 operator일 경우
			num2 = evalPop();				//evalPop 함수를 이용하여 evalStack의 마지막에 저장된 숫자를 num2에 저장
			evalStack[evalStackTop + 1] = 0;		//evalPop함수를 통해 반환된 값은 아직 evalStack에 남아있기 때문에 pop의 구현을 위해서 반환값이 있던 위치에 0를 삽입하여 원소 제거
			num1 = evalPop();				//evalPop 함수를 이용하여 evalStack의 마지막 원소 앞에 저장된 숫자를 num1에 저장
			evalStack[evalStackTop + 1] = 0;		//evalPop함수를 통해 반환된 값은 아직 evalStack에 남아있기 때문에 pop의 구현을 위해서 반환값이 있던 위치에 0를 삽입하여 원소 제거

			switch (token)					//token의 값을 case와 비교하여 해당하는 case문을 실행
			{
			case plus:					//token이 plus 연산자일 경우
				evalPush(num1 + num2);			//pop한 두 피연산자의 덧셈 결과를 evalStack에서 num1이 있던 위치에 저장
				break;					//switch문을 빠져나감
			case minus:					//token이 minus 연산자일 경우
				evalPush(num1 - num2);			//pop한 두 피연산자의 뺄셈 결과를 evalStack에서 num1이 있던 위치에 저장
				break;					//switch문을 빠져나감
			case times:					//token이 times 연산자일 경우
				evalPush(num1 * num2);			//pop한 두 피연산자의 곱셈 결과를 evalStack에서 num1이 있던 위치에 저장
				break;					//switch문을 빠져나감
			default:					//token이 divide 연산자일 경우
				if(num2 == 0)				//만약 두번째 피연사자가 0이라서 num1/0이 되는 경우
					div_0 = -1;			//0으로 나누는 경우가 있으므로 div_0을 -1로 저장
				else					//만약 두번째 피연사자가 0이 아닌 경우
					evalPush(num1 / num2);		//pop한 두 피연산자의 나눗셈 결과를 evalStack에서 num1이 있던 위치에 저장
				break;					//switch문을 빠져나감
		}
		if (div_0 != -1)					//수식 중 0으로 나누는 구간이 존재하지 않아 div_0의 값이 바뀌지 않은 경우
			postexp++;					//postexp의 주소를 증가시켜 다음 token을 가리키도록 함
		else							//수식 중 0으로 나누는 구간이 존재하여 div_0이 -1로 바뀐 경우
			break;						//더이상 수식을 계산할 수 없으므로 while문 탈출
	}
	if(div_0 != -1)							//수식 중 0으로 나누는 구간이 존재하지 않아 div_0의 값이 바뀌지 않은 경우
		evalResult = evalPop();					//evalPop 함수를 호출하여 evalSack의 유일하게 저장되어 있는 수식의 결과값을 반환하고 그 값을 evalResult에 저장
}

int main()
{
	char command;						//사용자가 입력한 메뉴 문자를 저장하는 문자형 변수 선언

	printf("[------[ 유현진 ] [2019038006]------]\n");
	do {							//do-while문을 조건문에 상관없이 무조건 한번 실행 후 조건문이 True일 때 do-while문 실행
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);				//사용자가 실행하고픈 메뉴에 해당하는 문자를 입력 및 command에 저장

		switch (command) {				//command의 값을 case별로 비교하고 해당하는 case의 문장 실행
		case 'i': case 'I':				//command가 i or I일 경우
			getInfix();				//사용자가 계산하고픈 수식을 입력하는 getInfix 함수 호출
			break;					//switch에서 빠져나감
		case 'p': case 'P':				//command가 p or P일 경우
			toPostfix();				//infixExp을 postfixExp로 바꾸는 toPostfix 함수 호출
			break;					//switch에서 빠져나감
		case 'e': case 'E':				//command가 e or E일 경우
			evaluation();				//수식의 값을 계산하는 evaluation 함수 호출
			break;					//switch에서 빠져나감
		case 'd': case 'D':				//command가 d or D일 경우
			debug();				//입력한 수식, postfix방식의 expression, 수식의 결과값과 postfixStack에 남아있는 원소를 출력해주는 debug 함수 정의
			break;					//switch에서 빠져나감
		case 'r': case 'R':				//command가 r or R일 경우
			reset();				//모든 수식, 스택과 top을 아무것도 안한 상태로 reset
			break;					//switch에서 빠져나감
		case 'q': case 'Q':				//command가 q or Q일 경우
			break;					//switch에서 빠져나감
		default:					//command가 위의 문자 이외의 값일 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");	//error message 출력
			break;					//switch에서 빠져나감
		}
	} while (command != 'q' && command != 'Q');		//command가 q or Q가 아닐 경우 do-while문 실행

	return 0;
}
