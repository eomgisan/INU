#include <stdio.h>
#include <stdlib.h>
#include <time.h> 



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                  알고있을만한 사람 선택 전략                                  //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////
 
// 그저 다음 보낼 인원을 랜덤하게 설정해주면 
// 어느정도 효율은 떨어지지만 무한 루프에 빠질 가능성은 없다.
// 우선 현재 이메일 보내려 하는 사람과 연결되어있는 인원을 확인하고
// 그 인원들 중에서 rand 함수를 통해 선정한다.
// 그후 도달할때 까지 반복한다.

#define MAX_VERTICES 11               // 최대 정점의 갯수 설정 문제상 11개의 정점이 있음


// 사람이름을 숫자(행렬 인덱스)로 변환해주는 함수
int trans_name(char name)
{
	if (name == 'a' || name == 'A')
		return 0;
	else if (name == 'b' || name == 'B')
		return 1;
	else if (name == 'c' || name == 'C')
		return 2;
	else if (name == 'd' || name == 'D')
		return 3;
	else if (name == 'e' || name == 'E')
		return 4;
	else if (name == 'f' || name == 'F')
		return 5;
	else if (name == 'g' || name == 'G')
		return 6;
	else if (name == 'h' || name == 'H')
		return 7;
	else if (name == 'i' || name == 'I')
		return 8;
	else if (name == 'j' || name == 'J')
		return 9;
	else if (name == 'k' || name == 'K')
		return 10;
	else
	{
		printf("사람 이름을 정확히 입력하세요\n");
		return -1;
	}
}

// 행렬의 인덱스를 사람 이름으로 변환해주는 함수
char trans_num(int name)
{
	switch (name) 
	{
		case 0:
			return'A';
			break;
		case 1:
			return'B';
			break;
		case 2:
			return'C';
			break;
		case 3:
			return'D';
			break;
		case 4:
			return'E';
			break;
		case 5:
			return'F';
			break;
		case 6:
			return'G';
			break;
		case 7:
			return'H';
			break;
		case 8:
			return'I';
			break;
		case 9:
			return'J';
			break;
		case 10:
			return'K';
			break;
		default:
			printf("정확한 행렬의 인덱스를 입력하세요\n");
			return 'z';
			break;
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                     행렬을 통한 그래프 구현                                   //
//                                          PPT 내용 참고                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
	int weight_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
	{
		for (c = 0; c < MAX_VERTICES; c++)
		{
			g->adj_mat[r][c] = 0;
			g->weight_mat[r][c] = 0;
		}
	}			
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	g->n++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, char s, char e, int weight)
{
	int start = trans_name(s);
	int end = trans_name(e);
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
	g->weight_mat[start][end] = weight;
	g->weight_mat[end][start] = weight;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                    이메일 전송 시간 계산 함수                                 //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////



// 간선 한번 지날때 소요 시간 반환
float send_time(GraphType* g, int before, int now) 
{
	// before 변수는 이전 이메일을 보낸 사람을 받는다.
	// now 변수는 현재 이메일을 보내는 사람을 받는다.
	// 만약 처음 이메일 보내기 시작 할 경우에는 before와 now가 같다.
	int W = 0;
	float result= 0;

	if (before == now) {
		return 0;
	}
	else {
		W = g->weight_mat[before][now];
		result = (float)1/W;
		return result;
	}
}

float total_send_time(GraphType* g, char start, char end)
{
	// start 변수는 시작할 이메일 전송 시작 사람을 받는다.
	// end 변수는 최종적으로 이메일 받을 사람을 받는다.
	int S = trans_name(start);
	int E = trans_name(end);

	int before = S; // 이전에 이메일을 보낸 사람
	int now = S;    // 현재 이메일을 보내려 하는 사람
	int next = -1;      // 현재 이메일을 받을 사람
	float time = 0;     // return할 소요시간


	int i = 0;

	if (g->adj_mat[S][E] == 1)
		return 0;
	else
	{
		// 직접 연결이 안되어있을 경우
		while ((now == E)<1) // 도달할때 까지 반복
		{
			next = find_next(g, now, E); // 다음 이메일을 받을사람에게 이메일 전송
			i++;

			time += send_time(g, before, now); // 전송에 소요된 시간 계산
			before = now; // 변수 수정
			now = next; // 변수 수정		
		}
	}
	return time;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                   이메일 전송할 사람 선택 함수                                //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////
int find_next(GraphType* g, int now, int end) {
	int next = -1;
	int count = 0;
	int i = 0;
	int index = 0;
	int pRute[MAX_VERTICES] = { 0, };
	

	if (g->adj_mat[now][end] == 1)
		next = end;
	else {
		for (count = 0; count < MAX_VERTICES; count++) {
			if (g->adj_mat[now][count] == 1) {
				pRute[i] = count;
				i++;
			}
		}
		index = rand()%i;
		next = pRute[index];
	}

	return next;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                           메인 함수                                           //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

int main() 
{
	clock_t start, finish;
	double duration;

	start = clock();
	srand(time(NULL));
// 문제 상황 구현
	float total_time = 0;
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0;i < MAX_VERTICES;i++)
	{
		insert_vertex(g, i);
	}
	insert_edge(g, 'a', 'b', 19);	insert_edge(g, 'a', 'c', 3);	insert_edge(g, 'a', 'd', 11);
	insert_edge(g, 'a', 'e', 13);	insert_edge(g, 'b', 'c', 4);	insert_edge(g, 'b', 'd', 5);
	insert_edge(g, 'c', 'd', 8);	insert_edge(g, 'c', 'e', 21);	insert_edge(g, 'd', 'f', 7);
	insert_edge(g, 'd', 'g', 5);	insert_edge(g, 'd', 'i', 14);	insert_edge(g, 'd', 'k', 15);
	insert_edge(g, 'e', 'f', 24);	insert_edge(g, 'e', 'j', 6);	insert_edge(g, 'f', 'g', 17);
	insert_edge(g, 'f', 'h', 8);	insert_edge(g, 'f', 'i', 3);	insert_edge(g, 'g', 'i', 15);
	insert_edge(g, 'g', 'k', 12);	insert_edge(g, 'h', 'i', 11);	insert_edge(g, 'h', 'j', 7);


	for (int i = 0;i < MAX_VERTICES;i++)
	{
		char start = trans_num(i);

		printf("\n@@@@@@@@@@@@@  %c가 이메일 전송함  @@@@@@@@@@@@@\n\n", start);
		for (int j = 0; j < MAX_VERTICES;j++) 
		{
			if (g->adj_mat[i][j] == 0 && i != j)
			{
				//연결 안되어있는 인원에게 이메일 전송한다.
				
				char end = trans_num(j);
				float time = total_send_time(g, start, end);
				printf("%c가 %c에게 이메일을 전송함.. 소요시간 = %f\n", start, end, time);
				total_time += time;
			}
		}
	}
	
	printf("\n모든 인원이 이메일 전송을 완료함.. 소요시간 = %f\n", total_time);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n프로그램 수행 시간 = %f\n", duration);
	printf("\n201600282 엄기산\n");

	free(g);

	return 0;
}