
//////////////////////////////////// ���.///////////////////////////////////////

////////////////// �̰�쿡�� ��ľȿ� 0 ���� ������� �ڿ����� ���� .........
#define ROWS 3
#define COLS 3
// ��� ��� ���� �Լ�, C=A+B
void sparse_matrix_add1(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS]) {
	int r, c;
	for (r = 0;r < ROWS;r++)
		for (c = 0;c < COLS;c++)
			C[r][c] = A[r][c] + B[r][c];
}


/////////////////////// ������ �� 0���� ������� �ڿ����� ���� �ʱ����� ���α׷���..
typedef struct {
	int row, col, value;
} element;
typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;	// ���� ����
	int cols;	// ���� ����
	int terms; 	// ���� ����
} SparseMatrix;

// ��� ��� ���� �Լ�, c = a + b
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0; 	// �� �迭�� �׸��� ����Ű�� �ε���
	// �迭 a�� �迭 b�� ũ�Ⱑ �������� Ȯ��
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "������ ũ�⿡��\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms) {
		// �� �׸��� �������� ��ȣ�� ����Ѵ�.
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if (inda < indb) {		// a �迭 �׸��� �տ� ������
			c.data[cc++] = a.data[ca++];
		}
		else if (inda == indb) {		// a�� b�� ���� ��ġ
			c.data[cc].row = a.data[ca].row;
			c.data[cc].col = a.data[ca].col;
			c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
		}
		else 			// b �迭 �׸��� �տ� ����
			c.data[cc++] = b.data[cb++];
	}

	// �迭 a�� b�� ���� �ִ� �׵��� �迭 c�� �ű��.
	for (; ca < a.terms; ca++) c.data[cc++] = a.data[ca++];
	for (; cb < b.terms; cb++) c.data[cc++] = b.data[cb++];
	c.terms = cc;
	return c;
}