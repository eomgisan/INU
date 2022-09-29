#include <stdio.h>
#include <stdlib.h>
#include <time.h> 



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                  �˰��������� ��� ���� ����                                  //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////
 
// ���� ���� ���� �ο��� �����ϰ� �������ָ� 
// ������� ȿ���� ���������� ���� ������ ���� ���ɼ��� ����.
// �켱 ���� �̸��� ������ �ϴ� ����� ����Ǿ��ִ� �ο��� Ȯ���ϰ�
// �� �ο��� �߿��� rand �Լ��� ���� �����Ѵ�.
// ���� �����Ҷ� ���� �ݺ��Ѵ�.

#define MAX_VERTICES 11               // �ִ� ������ ���� ���� ������ 11���� ������ ����


// ����̸��� ����(��� �ε���)�� ��ȯ���ִ� �Լ�
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
		printf("��� �̸��� ��Ȯ�� �Է��ϼ���\n");
		return -1;
	}
}

// ����� �ε����� ��� �̸����� ��ȯ���ִ� �Լ�
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
			printf("��Ȯ�� ����� �ε����� �Է��ϼ���\n");
			return 'z';
			break;
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                     ����� ���� �׷��� ����                                   //
//                                          PPT ���� ����                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct GraphType {
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
	int weight_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
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

// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�\n");
		return;
	}
	g->n++;
}

// ���� ���� ����
void insert_edge(GraphType* g, char s, char e, int weight)
{
	int start = trans_name(s);
	int end = trans_name(e);
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����\n");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
	g->weight_mat[start][end] = weight;
	g->weight_mat[end][start] = weight;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                    �̸��� ���� �ð� ��� �Լ�                                 //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////



// ���� �ѹ� ������ �ҿ� �ð� ��ȯ
float send_time(GraphType* g, int before, int now) 
{
	// before ������ ���� �̸����� ���� ����� �޴´�.
	// now ������ ���� �̸����� ������ ����� �޴´�.
	// ���� ó�� �̸��� ������ ���� �� ��쿡�� before�� now�� ����.
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
	// start ������ ������ �̸��� ���� ���� ����� �޴´�.
	// end ������ ���������� �̸��� ���� ����� �޴´�.
	int S = trans_name(start);
	int E = trans_name(end);

	int before = S; // ������ �̸����� ���� ���
	int now = S;    // ���� �̸����� ������ �ϴ� ���
	int next = -1;      // ���� �̸����� ���� ���
	float time = 0;     // return�� �ҿ�ð�


	int i = 0;

	if (g->adj_mat[S][E] == 1)
		return 0;
	else
	{
		// ���� ������ �ȵǾ����� ���
		while ((now == E)<1) // �����Ҷ� ���� �ݺ�
		{
			next = find_next(g, now, E); // ���� �̸����� ����������� �̸��� ����
			i++;

			time += send_time(g, before, now); // ���ۿ� �ҿ�� �ð� ���
			before = now; // ���� ����
			now = next; // ���� ����		
		}
	}
	return time;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//                                   �̸��� ������ ��� ���� �Լ�                                //
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
//                                           ���� �Լ�                                           //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

int main() 
{
	clock_t start, finish;
	double duration;

	start = clock();
	srand(time(NULL));
// ���� ��Ȳ ����
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

		printf("\n@@@@@@@@@@@@@  %c�� �̸��� ������  @@@@@@@@@@@@@\n\n", start);
		for (int j = 0; j < MAX_VERTICES;j++) 
		{
			if (g->adj_mat[i][j] == 0 && i != j)
			{
				//���� �ȵǾ��ִ� �ο����� �̸��� �����Ѵ�.
				
				char end = trans_num(j);
				float time = total_send_time(g, start, end);
				printf("%c�� %c���� �̸����� ������.. �ҿ�ð� = %f\n", start, end, time);
				total_time += time;
			}
		}
	}
	
	printf("\n��� �ο��� �̸��� ������ �Ϸ���.. �ҿ�ð� = %f\n", total_time);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n���α׷� ���� �ð� = %f\n", duration);
	printf("\n201600282 �����\n");

	free(g);

	return 0;
}