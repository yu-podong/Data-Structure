#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col);										 //입력한 행과 열을 이용하여 2차원 배열로 동적 할당 후 할당한 주소를 반환하는 함수 create_matrix 원형
int fill_data(int **matrix, int row, int col);									 //해당 행렬을 0~19 중 하나의 숫자로 배열의 원소를 채우는 함수 Fill_data 원형
void print_matrix(int **matrix, int row, int col);								 //해당 행렬을 출력하는 함수 print_matrix 원형
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);			 //matrix_a와 matrix_b 행렬의 합의 결과를 matrix_sum 행렬에 저장하는 함수 addition_matrix 원형
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);			 //matrix_a와 matrix_b 행렬의 챠의 결과를 matrix_sub 행렬에 저장하는 함수 subtraction_matrix 원형
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);						 //해당 행렬의 전치행렬을 구해 matrix_t 행렬에 저장하는 함수 transpose_matrix 원형
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col);		 	 //matrix_a와 matrix_t 행렬의 곱의 결과를 matrix_axt 행렬에 저장하는 함수 multiply_matrix 원형
int free_matrix(int **matrix, int row, int col);								 //해당 행렬에 동적으로 할당되었던 메모리를 해제하는 함수 free_matrix 원형

int main()
{
	int row = 0, col = 0;											 //행과 열의 개수를 저장할 변수 선언 및 0으로 초기화
	int **matrix_a = NULL, **matrix_b = NULL;								 //2차원 배열로 사용할 이중 포인터를 선언 및 NULL로 초기화
	int **matrix_sum = NULL, **matrix_sub = NULL, **matrix_t = NULL, **matrix_axt = NULL;			 //행렬 연산 결과를 저장할 2차원 배열로 사용할 이중 포인터를 선언 및 NULL로 초기화

	printf("[------[유현진] [2019038006]------]\n");
	scanf("%d %d", &row, &col);										 //입력한 행과 열의 개수를 row와 col에 저장
	matrix_a = create_matrix(row, col);									 //이중 포인터 matrix_a를 create_matrix 함수를 이용하여 2차원 배열로 동적 할당
	matrix_b = create_matrix(row, col);									 //이중 포인터 matrix_b를 create_matrix 함수를 이용하여 2차원 배열로 동적 할당
	matrix_sum = create_matrix(row, col);									 //이중 포인터 matrix_sum을 create_matrix 함수를 이용하여 2차원 배열로 동적 할당
	matrix_sub = create_matrix(row, col);									 //이중 포인터 matrix_sub를 create_matrix 함수를 이용하여 2차원 배열로 동적 할당
	matrix_t = create_matrix(col, row);									 //이중 포인터 matrix_t를 create_matrix 함수를 이용하여 2차원 배열로 동적 할당
	matrix_axt = create_matrix(row, row);									 //이중 포인터 matrix_axt를 create_matrix 함수를 이용하여 2차원 배열로 동적 할당

	srand((unsigned)time(NULL));										 //seed값을 시간으로 정해 random value를 생성할 수 있게끔 하는 srand 함수 호출
	fill_data(matrix_a, row, col);										 //matrix_a 행렬의 각 원소를 fill_data 함수를 호출하여 0~19 중 하나의 random value로 채움
	fill_data(matrix_b, row, col);										 //matrix_b 행렬의 각 원소를 fill_data 함수를 호출하여 0~19 중 하나의 random value로 채움

	print_matrix(matrix_a, row, col);									 //matrix_a 행렬을 출력하는 print_matrix 함수 호출
	print_matrix(matrix_b, row, col);									 //matrix_b 행렬을 출력하는 print_matrix 함수 호출

	addition_matrix(matrix_a, matrix_b, matrix_sum, row, col);						 //matrix_a와 matrix_b 행렬의 합을 matrix_sum 행렬에 저장하는 addition_matrix 함수 호출
	print_matrix(matrix_sum, row, col);									 //matrix_a와 matrix_b 행렬의 합의 결과인 matrix_sum 행렬을 출력하는 print_matrix 함수 호출

	subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);					 	 //matrix_a와 matrix_b 행렬의 차를 matrix_sub 행렬에 저장하는 subtraction_matrix 함수 호출
	print_matrix(matrix_sub, row, col);									 //matrix_a와 matrix_b 행렬의 차의 결과인 matrix_sub 행렬을 출력하는 print_matrix 함수 호출

	transpose_matrix(matrix_a, matrix_t, row, col);								 //matrix_a 행렬의 전치행렬을 matrix_t 행렬에 저장하는 transpose_matrix 함수 호출
	print_matrix(matrix_t, col, row);									 //matrix_a 행렬의 전치행렬의 결과인 matrix_t 행렬을 출력하는 print_matrix 함수 호출

	multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);						 //matrix_a와 matrix_t 행렬의 곱을 matrix_axt 행렬에 저장하는 multiply_matrix 함수 호출
	print_matrix(matrix_axt, row, row);									 //matrix_a와 matrix_t 행렬의 곱의 결과인 matrix_axt 행렬을 출력하는 print_matrix 함수 호출
 
	free_matrix(matrix_a, row, col);									 //matrix_a에 동적 할당되었던 메모리를 해제하는 free_matrix 함수 호출
	free_matrix(matrix_b, row, col);									 //matrix_b에 동적 할당되었던 메모리를 해제하는 free_matrix 함수 호출
	free_matrix(matrix_sum, row, col);								 	 //matrix_sum에 동적 할당되었던 메모리를 해제하는 free_matrix 함수 호출
	free_matrix(matrix_sub, row, col);								 	 //matrix_sub에 동적 할당되었던 메모리를 해제하는 free_matrix 함수 호출
	free_matrix(matrix_t, col, row);									 //matrix_t에 동적 할당되었던 메모리를 해제하는 free_matrix 함수 호출
	free_matrix(matrix_axt, row, row);									 //matrix_axt에 동적 할당되었던 메모리를 해제하는 free_matrix 함수 호출

	return 0;
}
int** create_matrix(int row, int col)										 //행렬의 크기를 결정할 행과 열의 개수를 나타내는 int형 변수 2개를 매개 변수로 하고 동적 할당한 결과값을 반환하기 위해 int형 이중 포인터를 사용하는 create_matrix 함수 정의
{
	int **matrix = NULL;											 //2차원 배열로 동적 할당한 결과값 즉, 할당한 메모리의 주소를 저장하는 이중 포인터 선언 및 NULL로 초기화
	if(row <= 0 || col <= 0) {										 //만약 행렬의 행 또는 열의 크기가 0 이하 즉, 행렬을 구성할 수 없는 크기이면
		printf("행 또는 열의 개수를 0 이하로 입력했는지 확인하세요.\n");					 //해당 문제의 내용을 출력해주는 error 메세지 출력
		return NULL;											 //비정상적인 입력이 들어왔으므로 비정상 종료를 의미하는 NULL을 return
	}
	matrix = (int**)malloc(row * sizeof(int *));								 //malloc 함수를 이용하여 행의 크기 row개의 포인터를 할당한 메모리의 주소를 이중 포인터에 저장
	for(int i = 0;i < row;i++)										 //각 행에 해당하는 i번째 포인터에 접근하기 위한 for문
		matrix[i] = (int*)malloc(col * sizeof(int));							 //i번째 행에 속하는 포인터가 열의 개수만큼의 원소를 갖는 1차원 배열을 할당한 메모리의 주소를 저장

	return matrix;												 //정상적인 종료를 의미하므로 2차원 배열로 동적 할당이 완료된 행렬의 주소값을 return
}
int free_matrix(int **matrix, int row, int col)									 //행렬로 사용되는 이중 포인터 1개와 행과 열을 나타낼 int형 변수 2개를 매개변수로 하고 종료된 상태를 나타내기 위해 반환값이 int형인 free_matrix 함수 정의
{
	if(matrix == NULL){											 //만약 해당 행렬이 NULL 즉, 할당된 메모리가 없다면 (해제할 메모리 존재 X)
		printf("해당 행렬은 이미 할당된 메모리가 없습니다.\n");						 //해당 문제의 내용을 출력해주는 error 메세지 출력
		return -1;											 //비정상적인 입력이 들어왔으므로 비정상 종료를 의미하는 -1을 return
	}
	for(int i = 0; i< row; i++)										 //행렬의 각 행을 구성했던 포인터들의 메모리를 해제하기 위해 행의 크기만큼 for문 실행
		free(matrix[i]);										 //i번재 행을 구성했던 포인터의 메모리를 free 함수를 호출하여 해제
	free(matrix);												 //각 행을 구성했던 포인터의 집합을 가리켰던 이중 포인터의 메모리를 free 함수를 호출하여 해제
	return 0;												 //정상적인 종료를 의미하는 1을 return
}
void print_matrix(int **matrix, int row, int col)								 //행렬로 사용되는 이중 포인터 1개와 행과 열을 나타낼 int형 변수 2개를 매개변수로 하고 반환값이 없는 print_matrix 함수 정의
{
	if(matrix == NULL)											 //만약 해당 행렬이 NULL 즉, 동적 할당이 제대로 되지 않은 행렬이라면
		printf("해당 행렬의 동적 할당을 제대로 하였는지 확인하세요.\n");				         //해당 문제의 내용을 출력해주는 error 메세지 출력
	else {													 //해당 행렬이 정상적으로 동적 할당이 되었다면
		for(int i = 0; i < row; i++) {									 //matrix의 행의 크기가 row이므로 0~row-1번째 행에 접근하기 위한 for문
			for(int j = 0; j < col; j++)								 //matrix의 열의 크기가 col이므로 0~col-1번째 열에 접근하기 위한 for문
				printf("%3d ",matrix[i][j]);							 //matrix[i][j]에 저장된 값을 출력
			printf("\n");
		}
		printf("\n");
	}
}
int fill_data(int **matrix, int row, int col)									 //행렬로 사용되는 이중 포인터 1개와 행과 열을 나타낼 int형 변수 2개를 매개변수로 하고 종료된 상태를 나타내기 위해 반환값이 int형인 fill_matrix 함수 정의
{
	if(matrix == NULL) {											 //만약 해당 행렬이 NULL 즉, 동적 할당이 제대로 되지 않은 행렬이라면
		printf("해당 행렬의 동적 할당을 제대로 하였는지 확인하세요.\n");				         //해당 문제의 내용을 출력해주는 error 메세지 출력
		return -1;										         //비정상적인 입력이 들어왔으므로 비정상 종료를 의미하는 -1을 return
	}
	for(int i = 0; i < row; i++)										 //matrix의 행의 크기가 row이므로 0~row-1번째 행에 접근하기 위한 for문
		for(int j = 0; j < col; j++)									 //matrix의 열의 크기가 col이므로 0~col-1번째 열에 접근하기 위한 for문
			matrix[i][j] = rand() % 20;								 //matrix[i][j]의 값을 0~19 중 하나의 random value 저장
	return 1;											         //정상적인 종료를 의미하는 1을 return
}
int transpose_matrix(int **matrix, int **matrix_t, int row, int col)						 //행렬로 사용되는 이중 포인터 2개와 행과 열을 나타낼 int형 변수 2개를 매개변수로 하고 종료된 상태를 나타내기 위해 반환값이 int형인 transpose_matrix 함수 정의
{
	if(matrix == NULL || matrix_t == NULL){									 //만약 2개의 행렬 중 NULL 즉, 동적 할당이 제대로 되지 않은 행렬이 존재한다면
		printf("matrix, matrix_t 중 동적 할당이 제대로 되지 않은 행렬이 존재합니다.\n");			 //해당 문제의 내용을 출력해주는 error 메세지 출력
		return -1;											 //비정상적인 입력이 들어왔으므로 비정상 종료를 의미하는 -1을 return
	}
	for(int i = 0; i < row; i++)										 //matrix의 행의 크기가 row이므로 0~row-1번째 행에 접근하기 위한 for문
		for(int j = 0; j < col; j++)									 //matrix의 열의 크기가 col이므로 0~col-1번째 열에 접근하기 위한 for문
			matrix_t[j][i] = matrix[i][j];								 //전치행렬은 matrix의 행이 열로 바뀐 행렬이므로 matrix[i][j]의 값을 matrix_t[j][i]에 저장
	return 1;												 //정상적인 종료를 의미하는 1을 return
}
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col)				 //행렬로 사용되는 이중 포인터 3개와 행과 열을 나타낼 int형 변수 2개를 매개변수로 하고 종료된 상태를 나타내기 위해 반환값이 int형인 addition_matrix 함수 정의
{
	if(matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL){						 //만약 3개의 행렬 중 NULL 즉, 동적 할당이 제대로 되지 않은 행렬이 존재한다면
		printf("matrix_a, matrix_b, matrix_sum 중 동적 할당이 제대로 되지 않은 행렬이 존재합니다.\n");	 //해당 문제의 내용을 출력해주는 error 메세지 출력
		return -1;											 //비정상적인 입력이 들어왔으므로 비정상 종료를 의미하는 -1을 return
	}
	for(int i = 0; i < row; i++)										 //두 행렬의 크기가 같으므로 0~row-1번째 행에 접급하기 위한 for문
		for(int j = 0; j < col; j++)									 //두 행렬의 크기가 같으므로 0~col-1번째 열에 접급하기 위한 for문
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];					 //matrix_a[i][j] + matrix_b[i][j]의 결과값을 matrix_sum[i][j]에 저장
	return 1;												 //정상적인 종료를 의미하는 1을 return
}
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)			 //행렬로 사용되는 이중 포인터 3개와 행과 열을 나타낼 int형 변수 2개를 매개변수로 하고 종료된 상태를 나타내기 위해 반환값이 int형인 subtraction_matrix 함수 정의
{
	if(matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL){						 //만약 3개의 행렬 중 NULL 즉, 동적 할당이 제대로 되지 않은 행렬이 존재한다면
		printf("matrix_a, matrix_b, matrix_sub 중 동적 할당이 제대로 되지 않은 행렬이 존재합니다.\n");	 //해당 문제의 내용을 출력해주는 error 메세지 출력
		return -1;											 //비정상적인 입력이 들어왔으므로 비정상 종료를 의미하는 -1을 return
	}
	for(int i = 0; i < row; i++)										 //두 행렬의 크기가 같으므로 0~row-1번째 행에 접급하기 위한 for문
		for(int j = 0; j < col; j++)									 //두 행렬의 크기가 같으므로 0~col-1번째 열에 접급하기 위한 for문
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];					 //matrix_a[i][j] - matrix_b[i][j]의 결과값을 matrix_sub[i][j]에 저장
	return 1;												 //정상적인 종료를 의미하는 1을 return
}
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col)				 //행렬로 사용되는 이중 포인터 3개와 행과 열을 나타낼 int형 변수 2개를 매개변수로 하고 종료된 상태를 나타내기 위해 반환값이 int형인 multiply_matrix 함수 정의
{	
	int temp = 0;												 //두 행렬의 원소의 곱의 합을 저장해 matrix_axt 행렬의 원소를 구성할 temp 선언 및 0으로 초기화
	if(matrix_a == NULL || matrix_t == NULL || matrix_axt == NULL){						 //만약 3개의 행렬 중 NULL 즉, 동적 할당이 제대로 되지 않은 행렬이 존재한다면
		printf("matrix_a, matrix_t, matrix_axt 중 동적 할당이 제대로 되지 않은 행렬이 존재합니다.\n");	 //해당 문제의 내용을 출력해주는 error 메세지 출력
		return -1;											 //비정상적인 입력이 들어왔으므로 비정상 종료를 의미하는 -1을 return
	}
	for(int k = 0; k < row; k++)										 //행렬의 곱일 경우 matrix_axt 행렬의 행의 크기는 matrix_a의 행의 크기와 같으므로 row-1번 돌게 함
		for(int i = 0; i < row; i++){									 //행렬의 곱일 경우 matrix_axt 행렬의 열의 크기는 matrix_t의 열의 크기와 같으므로 row-1번 돌게 함
			for(int j = 0; j < col; j++)								 //matrix_a의 k번째 행의 각 원소와 matrix_t의 i번째 열의 각 원소에 접근하기 위해 col-1번 돌게 함
				temp += (matrix_a[k][j] * matrix_t[j][i]);				   	 //matrix_a의 k번째 행과 matrix_t의 i번째 열의 각 원소의 곱의 합을 temp에 저장
			matrix_axt[k][i] = temp;								 //temp에 저장된 값을 matrix_axt[k][i]에 저장
			temp = 0;										 //temp가 이전의 원소의 값을 계속 저장되는 것을 방지하기 위해 0을 저장
		}
	return 1;												 //정상적인 종료를 의미하는 1을 return
}
