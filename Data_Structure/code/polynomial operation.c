////////////////////////////////  ���׽��� ǥ��  ///////////////////////////////////
#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))  //  A�� B���� ũ�� A �ƴϸ� B ����
#define MAX_DEGREE 101
typedef struct { 			// ���׽� ����ü Ÿ�� ����
	int degree;			// ���׽��� ����
	float coef[MAX_DEGREE];	// ���׽��� ���
} polynomial;



//////////////////////////////// ���׽��� ���� /////////////////////////////////////

polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C;			// C = A+B ���⼭ A�� B�� ���׽��̴�.
	int Apos = 0, Bpos = 0, Cpos = 0;		// �迭 �ε��� ����
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);		// ��� ���׽� ����
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {		// A�� > B��
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {		// A�� == B��
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {				// B�� > A��
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void main() {
	polynomial a = { 5, {3, 6, 0, 0, 0, 10} };
	polynomial b = { 4, {7, 0, 5, 0, 1} };
	polynomial c;
	c = poly_add1(a, b);
}


/////////////////////////////////////// ���׽��� ǥ�� 2 ////////////////////////////

#define MAX_TERMS 101
struct {
	float coef;    // ���
	int expon;     // ����
} terms[MAX_TERMS] = { {8,3}, {7,1}, {1,0}, {10,3}, {3,2},{1,0} };
int avail = 6;

// �ΰ��� ������ ��
char compare(int a, int b) {
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

// ���ο� ���� ���׽Ŀ� �߰��Ѵ�.
void attach(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "���� ������ �ʹ� ����\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;           // �ְ� AVAIL �� �ϳ� ���� �ϴ°ǰ�??
}

//////////////////////////////// ���׽��� ����2 /////////////////////////////////////
// �����ϱ�//

poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {	// C = A + B
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {
		case '>': 	// A�� ���� > B�� ����
			attach(terms[As].coef, terms[As].expon);
			As++; break;
		case '=': 	// A�� ���� == B�� ����
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef) attach(tempcoef, terms[As].expon);
			As++; Bs++; break;
		case '<': 	// A�� ���� < B�� ����
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++; break;
		}
	// A�� ������ �׵��� �̵���
	for (;As <= Ae;As++) attach(terms[As].coef, terms[As].expon);
	// B�� ������ �׵��� �̵���
	for (;Bs <= Be;Bs++) attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}