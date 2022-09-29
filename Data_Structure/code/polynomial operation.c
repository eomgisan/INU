////////////////////////////////  다항식의 표현  ///////////////////////////////////
#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))  //  A가 B보다 크면 A 아니며 B 리턴
#define MAX_DEGREE 101
typedef struct { 			// 다항식 구조체 타입 선언
	int degree;			// 다항식의 차수
	float coef[MAX_DEGREE];	// 다항식의 계수
} polynomial;



//////////////////////////////// 다항식의 덧셈 /////////////////////////////////////

polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C;			// C = A+B 여기서 A와 B는 다항식이다.
	int Apos = 0, Bpos = 0, Cpos = 0;		// 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);		// 결과 다항식 차수
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {		// A항 > B항
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {		// A항 == B항
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {				// B항 > A항
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


/////////////////////////////////////// 다항식의 표현 2 ////////////////////////////

#define MAX_TERMS 101
struct {
	float coef;    // 계수
	int expon;     // 차수
} terms[MAX_TERMS] = { {8,3}, {7,1}, {1,0}, {10,3}, {3,2},{1,0} };
int avail = 6;

// 두개의 정수를 비교
char compare(int a, int b) {
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

// 새로운 항을 다항식에 추가한다.
void attach(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;           // 넣고 AVAIL 이 하나 증가 하는건가??
}

//////////////////////////////// 다항식의 덧셈2 /////////////////////////////////////
// 공부하기//

poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {	// C = A + B
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {
		case '>': 	// A의 차수 > B의 차수
			attach(terms[As].coef, terms[As].expon);
			As++; break;
		case '=': 	// A의 차수 == B의 차수
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef) attach(tempcoef, terms[As].expon);
			As++; Bs++; break;
		case '<': 	// A의 차수 < B의 차수
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++; break;
		}
	// A의 나머지 항들을 이동함
	for (;As <= Ae;As++) attach(terms[As].coef, terms[As].expon);
	// B의 나머지 항들을 이동함
	for (;Bs <= Be;Bs++) attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}