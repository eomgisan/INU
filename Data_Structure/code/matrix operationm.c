
//////////////////////////////////// 행렬.///////////////////////////////////////

////////////////// 이경우에는 행렬안에 0 값이 많을경우 자원낭비 심함 .........
#define ROWS 3
#define COLS 3
// 희소 행렬 덧셈 함수, C=A+B
void sparse_matrix_add1(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS]) {
	int r, c;
	for (r = 0;r < ROWS;r++)
		for (c = 0;c < COLS;c++)
			C[r][c] = A[r][c] + B[r][c];
}


/////////////////////// 희소행렬 즉 0값이 많을경우 자원낭비 하지 않기위한 프로그래밍..
typedef struct {
	int row, col, value;
} element;
typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;	// 행의 개수
	int cols;	// 열의 개수
	int terms; 	// 항의 개수
} SparseMatrix;

// 희소 행렬 덧셈 함수, c = a + b
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0; 	// 각 배열의 항목을 가리키는 인덱스
	// 배열 a와 배열 b의 크기가 같은지를 확인
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "희소행렬 크기에러\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms) {
		// 각 항목의 순차적인 번호를 계산한다.
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if (inda < indb) {		// a 배열 항목이 앞에 있으면
			c.data[cc++] = a.data[ca++];
		}
		else if (inda == indb) {		// a와 b가 같은 위치
			c.data[cc].row = a.data[ca].row;
			c.data[cc].col = a.data[ca].col;
			c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
		}
		else 			// b 배열 항목이 앞에 있음
			c.data[cc++] = b.data[cb++];
	}

	// 배열 a와 b에 남아 있는 항들을 배열 c로 옮긴다.
	for (; ca < a.terms; ca++) c.data[cc++] = a.data[ca++];
	for (; cb < b.terms; cb++) c.data[cc++] = b.data[cb++];
	c.terms = cc;
	return c;
}