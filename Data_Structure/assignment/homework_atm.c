#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                   @      ����� ������ ���� ����         @                                   *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ���� ���� ����
int T_Wait_Time = 0;			// �� ���ð�
int OutCount = 0;				// ���࿡�� ���� �ο�
int DoneCount = 0;				// ������ �Ϸ��ϰ� ���࿡�� ���� �ο�

// ��� ����
typedef struct node{
	struct node* pre;					// �� ����� �ڷ� �ּ�
	struct node* next;					// �� ����� �ڷ� �ּ�

	int enter_hour;				// ���� ���� �ð��� ��
	int enter_min;				// ���� ���� �ð��� ��
	int work_time;				// atm��� ���� ���� �ҿ� �ð�( 2~10�� ���̰� )
}node;

// ť ATM ����
typedef struct atm{		
	struct node* front, * rear;

	int nextHour;				// atm ����ڰ� �ٲ�� �ð��� ��
	int nextMin;				// atm ����ڰ� �ٲ�� �ð��� ��
	int length;					// atm ��⿭�� ����
}atm;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                           @       �ʱ�ȭ �Լ�        @                                       *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ��� �ʱ�ȭ �Լ� ( ���� �ο��� ���� �ð��� ���� �ҿ� �ð� �Է� )
void init_node(node* temp, int H, int M) {
	temp->next = NULL;
	temp->pre = NULL;

	temp->enter_hour = H;
	temp->enter_min = M;
	temp->work_time = (rand() % 9) + 2;
}

// ť �ʱ�ȭ �Լ�
void init_atm(atm* q) {
	q->front = NULL;
	q->rear = NULL;

	q->nextHour = 0;				
	q->nextMin = 0;
	q->length = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                        @       ���� ��� �Լ�        @                                       *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �ο� atm ��� ��� ���۽� ���� ��� �Լ�
void print_string(node* now, int H, int M, int atm_num) {
	// �����ϴ� �ο��� ������, ���� �ð�, atm ��� ��ȣ�� �Է� ����
	printf("\n%d�� %d�� - %d�� ��(%d�� �ҿ�)�� %d�� ATM���� ���� ������\n",
		H, M, now->enter_min, now->work_time, atm_num);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                     @       ��� ���� ���� �Լ�        @                                     *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �����ϴ� �ο��� ATM ��� ������� �����ִ� �Լ�

int lineupATM(atm* atm1, atm* atm2, atm* atm3)
{	
	int num = 0;

	int a = atm1->length;
	int b = atm2->length;
	int c = atm3->length;

	if ((a < b) & (a < c)) {			// atm1 �� ���� ª�����
		num = 0;
	}
	else if ((b < a) & (b < c)) {		// atm2 �� ���� ª�����
		num = 1;
	}
	else if ((c < a) & (c < b)) {		// atm3 �� ���� ª�����
		num = 2;
	}
	else if ((a == b) & (a < c)) {		// atm1�� atm2�� ���� ª�����
		num = (rand() % 2);
	}
	else if ((a == c) & (a < b)) {		// atm1�� atm3�� ���� ª�����
		num = (rand() % 2) * 2;
	}
	else if ((b == c) & (b < a)) {		// atm2�� atm3�� ���� ª�����
		num = (rand() % 2) + 1;
	}
	else if ((a == b) & (b == c)) {			// ��⿭�� ���̰� ��� ���� ���
		num = (rand() % 3);
	}
	return num;
}

// atm�� ����ִ��� Ȯ��	���������� 1�� ����
int is_empty(atm* q) {
	if ((q->front == NULL) || (q->rear == NULL) || (q->length == 0)) {	
		return 1;
	}
	else
		return 0;
}

// vip���� Ȯ�����ִ� �Լ�	���ϰ��� 0�ϰ�츸 vip
int is_vip() {
	int i = 0;
	i = rand() % 10;
	return i;
}

// ť ���� �Լ�
void enAtm(atm* q, int H, int M, int atm_num) {

	int vip = 0;	
	vip = is_vip();			// ���� �ο��� vip���� Ȯ���Ѵ�.
	
	node* new = (node*)malloc(sizeof(node));		// ���ο� ��� ����
	init_node(new, H, M);							// ��� ������ �ʱ�ȭ ( �����ο��� ���� �ð�, �����ҿ�ð� ä���ֱ� )

	if (is_empty(q) == 1) {			// atm�� ������� ���
		new->next = NULL;				// new ��忡 ������ �Է�
		new->pre = NULL;				// new ��忡 ������ �Է�
		
		
		q->front = new;
		q->rear = new;
		q->length += 1;					// ��⿭ ���� ����

		q->nextHour = H;				// atm ����ڰ� �ٲ�� �ð��� ����ð� + ������� ���� �ҿ�ð�
		q->nextMin = M + new->work_time;// atm ����ڰ� �ٲ�� �ð��� ����ð� + ������� ���� �ҿ�ð�

		if (q->nextMin >= 60) {			// nextMin ���� 60 �̻��ϰ�� nextHour �� 1 ���� nextMin�� 60 ����
			q->nextHour += 1;
			q->nextMin -= 60;
		}

		print_string(q->front, H, M, atm_num);		// ȭ�鿡 atm��� ������ ���� ���
	}		
	else if ((q->length>1) && (vip == 0)) {			// atm������� �ְ� ���� �ο��� vip�� ���
		new->pre = q->front;			// new ��忡 ������ �Է�
		new->next = q->front->next;		// new ��忡 ������ �Է�
		
		q->front->next->pre = new;		// �ٲ� ������� ���� front->next�� pre�� ����
		q->front->next = new;			// �ٲ� ������� front�� next�� ����	
	}
	else {							// �Ϲ����� ���
		new->pre = q->rear;				// new ��忡 ������ �Է�
		new->next = NULL;				// new ��忡 ������ �Է�

		q->rear->next = new;			// �ٲ� ������� ���� q�� rear->next �� ����

		q->rear = new;					// ������ ����� ����
		q->length += 1;					// ��⿭ ����  ����
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                     @       ��� ���� ���� �Լ�        @                                     *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �ο� ���� ��ġ�� ������ �Լ�
void deAtm(atm*q, int H, int M, int atm_num) {
	if ((q->length>1)&&(q->nextHour == H) && (q->nextMin == M))		// atm ��� ����� ����ð��� �ɰ�� ����
	{
		int wait_min = 0;								// ������� ����Ҷ����� ���ð�
		node* out;										// ���� ���

		out = q->front;									// ���� ��� ����
		q->front = out->next;							// atm ��� ����� ����
		q->front->pre = NULL;							

		wait_min = (H - q->front->enter_hour) * 60 + (M - q->front->enter_min);		// atm ��� �������ϴ� �ο��� ���ð� ���
		T_Wait_Time += wait_min;						// ��ü ���ð��� �߰�

		q->nextHour = H;				// atm ����ڰ� �ٲ�� �ð��� ����ð� + ������� ���� �ҿ�ð�
		q->nextMin = M + q->front->work_time;// atm ����ڰ� �ٲ�� �ð��� ����ð� + ������� ���� �ҿ�ð�

		if (q->nextMin >= 60) {			// nextMin ���� 60 �̻��ϰ�� nextHour �� 1 ���� nextMin�� 60 ����
			q->nextHour += 1;
			q->nextMin -= 60;
		}

		print_string(q->front, H, M, atm_num);		// ȭ�鿡 atm��� ������ ���� ���

		OutCount += 1;					// ���࿡�� ���� �ο� 1 ����
		DoneCount += 1;					// ���� �Ϸ��� �ο� 1 ����
		q->length -= 1;					// ��⿭ ���� ����

		free(out);
	}
}

// �Ҽ����� �ƴ��� Ȯ�����ִ� �Լ� ���ϰ��� 1�ϰ�� �Ҽ� 0 �ϰ�� �Ҽ��� �ƴ�
int is_prime(int a)
{		
	int i;
	int count = 0;
	for (i = 1; i <= a; i++) {
		if (a % i == 0) {
			count++;
		}
	}
	if (count == 2) {
		return 1;
	}
	else {
		return 0;
	}
}

// 10�� ���� ������ �����ȣ �Ҽ��ο� ���� �Լ�
void deAtm_prime(atm* q, int H, int M) {
	if (q->length > 1) {	// ����ο��� ������쿡�� ����
		int wait_min=0;
		int i=0;
		node* check;					// üũ�� �ο�

		check = q->front->next;			// ����ο��� �� �պ��� Ȯ��

		for (i = 0;i < q->length - 2;i++) {	// üũ�ο��� rear�� �ƴҶ����� ����
			if (is_prime(check->enter_min) == 1) {	// üũ �ο��� �����ȣ�� �Ҽ��ϰ�� ����
				node* out;
				node* behind;					// üũ�� �ο��� ��
				node* front;					// üũ�� �ο��� ��

				behind = check->next;
				front = check->pre;
				out = check;

				front->next = behind;		// ��⿭ ���� ä���
				behind->pre = front;		// ��⿭ ���� ä���

				wait_min = (H - out->enter_hour) * 60 + (M - out->enter_min);		// ������ �ο��� ���ð� ���
				T_Wait_Time += wait_min;						// ��ü ���ð��� �߰�

				q->length -= 1;						// ��⿭ 1 ����
				OutCount += 1;
				check = check->next;				// üũ�� ��� �������� �̵�
				free(out);
			}
		}

		//üũ�ο��� rear�϶�
		if (is_prime(check->enter_min) == 1) {
			node* out;
			out = check;
			check->pre->next = NULL;
			q->rear = check->pre;

			wait_min = (H - out->enter_hour) * 60 + (M - out->enter_min);		// ������ �ο��� ���ð� ���
			T_Wait_Time += wait_min;						// ��ü ���ð��� �߰�

			q->length -= 1;						// ��⿭ 1 ����
			OutCount += 1;
			free(out);
		}
	}
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                           @       �����Լ�       @                                           *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int hour = 0;
	int min = 0;
	int line_num = 0;						// lineupATM�Լ��� ����� ���� ( ATM�迭�� ���� )
	int atm_num = 0;						// ȭ�鿡 ����� atm ��ȣ
	int i = 0;

	srand(time(NULL));

	atm* ATM = (atm*)malloc(sizeof(atm) * 3);				// 3���� ATM ����ü ����
	for (i = 0;i < 3;i++) {
		init_atm(&ATM[i]);							// ATM�� ����ü �ʱ�ȭ
	}

	for (hour = 9;hour < 11;hour++)
	{
		for (min = 0;min < 60;min++)
		{
			if ((hour == 9) && (min == 0)) {	// 9�ÿ��� ��� ���� ���ϹǷ� min ����
				min++;
			}

			line_num = lineupATM(&ATM[0],&ATM[1],&ATM[2]);	// atm ��� ����
			atm_num = line_num + 1;


			// ��� atm ��⿡ �ټ���
			enAtm(&ATM[line_num], hour, min, atm_num);

			if (min % 10 == 0) {
				// 10�и��� ����ο��� �����ȣ �Ҽ��� �ο� ����
				for (i = 0;i < 3;i++) {
					deAtm_prime(&ATM[i], hour, min);
				}
			}


			// �Ϸ� �ο� ����
			for (i = 0;i < 3;i++) {
				deAtm(&ATM[i], hour, min, i + 1);
			}
		}
	}

	printf("\n 1. ���� �Ϸ��� �ο� = %d\n", DoneCount);
	printf("\n 2. ��� ��� �ð� = %d��\n", (T_Wait_Time / OutCount));
	printf("\n 3. ���� �� ��� �ο� = %d\n", (ATM[0].length + ATM[1].length + ATM[2].length - 3));

	free(ATM);
	return 0;
}