#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{
    char command;
    printf("[----- [김민재]  [2021041070] -----]\n");

	int row, col;
	srand(time(NULL));

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col); 
	int** matrix_b = create_matrix(row, col); // 행렬 A,B 생성
    int** matrix_a_t = create_matrix(col, row); // A의 전치행렬 생성

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} //행렬 생성 후 만들어진 행렬이 없다면 비정상 종료

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
        case 'a': case 'A':
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
        case 's': case 'S':
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
        case 't': case 'T':
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M':
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
        case 'q': case 'Q': 
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 그외 입력시
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); 
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);
	}
	//행렬의 열과 행을 위한 공간을 동적할당

	/* Check post conditions */
	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]); //행렬의 각 원소를 출력
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]); // 행렬의 모든 원소의 동적할당을 해제
	}

	free(matrix); // 행렬의 모든 원소의 동적할당을 해제
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20; //0~20의 값을 랜덤으로 행렬의 각 원소의 값으로 지정
	/* Check post conditions */
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col); // 합을 저장할 행렬 생성
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col]; // 같은 행,열의 원소끼리 더함
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col);
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); //차를 저장할 행렬 생성 
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col]; //같은 행,열의 원소끼리 뺌
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; //matrix_t 는 matrix의 행,열을 바꾸어 대입
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) { //행렬의 곱은 행렬A의 행과 행렬 B의 열의 대응하는 위치에 있는 원소를 차례로 곱하여 더함
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) { 
			int temp = 0; // 한 행의 연산이 끝나면 temp의 값을 초기화 
				for (int matrix_col = 0; matrix_col < col; matrix_col++) 
				{
					temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; //차례로 곱한 후 더한 값을 temp에 저장
				}
			matrix_axt[matrix_a_row][matrix_t_row] = temp; 
		}
	}
	
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);
	free_matrix(matrix_axt, row, col);
	return 1;
}

