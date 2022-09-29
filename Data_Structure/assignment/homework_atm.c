#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                   @      사용할 변수들 선언 구역         @                                   *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 전역 변수 선언
int T_Wait_Time = 0;			// 총 대기시간
int OutCount = 0;				// 은행에서 나간 인원
int DoneCount = 0;				// 업무를 완료하고 은행에서 나간 인원

// 노드 선언
typedef struct node{
	struct node* pre;					// 앞 사람의 자료 주소
	struct node* next;					// 뒷 사람의 자료 주소

	int enter_hour;				// 은행 입장 시간의 시
	int enter_min;				// 은행 입장 시간의 분
	int work_time;				// atm기기 업무 수행 소요 시간( 2~10분 사이값 )
}node;

// 큐 ATM 구현
typedef struct atm{		
	struct node* front, * rear;

	int nextHour;				// atm 사용자가 바뀌는 시간의 시
	int nextMin;				// atm 사용자가 바뀌는 시간의 분
	int length;					// atm 대기열의 길이
}atm;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                           @       초기화 함수        @                                       *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 노드 초기화 함수 ( 입장 인원의 입장 시간과 업무 소요 시간 입력 )
void init_node(node* temp, int H, int M) {
	temp->next = NULL;
	temp->pre = NULL;

	temp->enter_hour = H;
	temp->enter_min = M;
	temp->work_time = (rand() % 9) + 2;
}

// 큐 초기화 함수
void init_atm(atm* q) {
	q->front = NULL;
	q->rear = NULL;

	q->nextHour = 0;				
	q->nextMin = 0;
	q->length = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                        @       문장 출력 함수        @                                       *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 인원 atm 기기 사용 시작시 문장 출력 함수
void print_string(node* now, int H, int M, int atm_num) {
	// 시작하는 인원의 데이터, 현재 시간, atm 기기 번호를 입력 받음
	printf("\n%d시 %d분 - %d번 고객(%d분 소요)이 %d번 ATM에서 서비스 시작함\n",
		H, M, now->enter_min, now->work_time, atm_num);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                     @       노드 삽입 관련 함수        @                                     *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 입장하는 인원이 ATM 몇번 사용할지 정해주는 함수

int lineupATM(atm* atm1, atm* atm2, atm* atm3)
{	
	int num = 0;

	int a = atm1->length;
	int b = atm2->length;
	int c = atm3->length;

	if ((a < b) & (a < c)) {			// atm1 이 가장 짧을경우
		num = 0;
	}
	else if ((b < a) & (b < c)) {		// atm2 가 가장 짧을경우
		num = 1;
	}
	else if ((c < a) & (c < b)) {		// atm3 이 가장 짧을경우
		num = 2;
	}
	else if ((a == b) & (a < c)) {		// atm1과 atm2가 가장 짧을경우
		num = (rand() % 2);
	}
	else if ((a == c) & (a < b)) {		// atm1과 atm3가 가장 짧을경우
		num = (rand() % 2) * 2;
	}
	else if ((b == c) & (b < a)) {		// atm2와 atm3이 가장 짧을경우
		num = (rand() % 2) + 1;
	}
	else if ((a == b) & (b == c)) {			// 대기열의 길이가 모두 같을 경우
		num = (rand() % 3);
	}
	return num;
}

// atm이 비어있는지 확인	비어있을경우 1을 리턴
int is_empty(atm* q) {
	if ((q->front == NULL) || (q->rear == NULL) || (q->length == 0)) {	
		return 1;
	}
	else
		return 0;
}

// vip인지 확인해주는 함수	리턴값이 0일경우만 vip
int is_vip() {
	int i = 0;
	i = rand() % 10;
	return i;
}

// 큐 삽입 함수
void enAtm(atm* q, int H, int M, int atm_num) {

	int vip = 0;	
	vip = is_vip();			// 입장 인원이 vip인지 확인한다.
	
	node* new = (node*)malloc(sizeof(node));		// 새로운 노드 생성
	init_node(new, H, M);							// 노드 데이터 초기화 ( 입장인원의 입장 시간, 업무소요시간 채워주기 )

	if (is_empty(q) == 1) {			// atm이 비어있을 경우
		new->next = NULL;				// new 노드에 데이터 입력
		new->pre = NULL;				// new 노드에 데이터 입력
		
		
		q->front = new;
		q->rear = new;
		q->length += 1;					// 대기열 길이 증가

		q->nextHour = H;				// atm 사용자가 바뀌는 시간은 현재시간 + 사용자의 업무 소요시간
		q->nextMin = M + new->work_time;// atm 사용자가 바뀌는 시간은 현재시간 + 사용자의 업무 소요시간

		if (q->nextMin >= 60) {			// nextMin 값이 60 이상일경우 nextHour 값 1 증가 nextMin값 60 감소
			q->nextHour += 1;
			q->nextMin -= 60;
		}

		print_string(q->front, H, M, atm_num);		// 화면에 atm기기 사용시작 문장 출력
	}		
	else if ((q->length>1) && (vip == 0)) {			// atm대기줄이 있고 입장 인원이 vip일 경우
		new->pre = q->front;			// new 노드에 데이터 입력
		new->next = q->front->next;		// new 노드에 데이터 입력
		
		q->front->next->pre = new;		// 바뀐 순서대로 기존 front->next의 pre값 변경
		q->front->next = new;			// 바뀐 순서대로 front의 next값 변경	
	}
	else {							// 일반적인 경우
		new->pre = q->rear;				// new 노드에 데이터 입력
		new->next = NULL;				// new 노드에 데이터 입력

		q->rear->next = new;			// 바뀐 순서대로 기존 q의 rear->next 값 변경

		q->rear = new;					// 마지막 사람이 변경
		q->length += 1;					// 대기열 길이  증가
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                     @       노드 삭제 관련 함수        @                                     *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 인원 업무 마치고 나가는 함수
void deAtm(atm*q, int H, int M, int atm_num) {
	if ((q->length>1)&&(q->nextHour == H) && (q->nextMin == M))		// atm 기기 사용자 변경시간이 될경우 수행
	{
		int wait_min = 0;								// 입장부터 사용할때까지 대기시간
		node* out;										// 나갈 사람

		out = q->front;									// 나갈 사람 선정
		q->front = out->next;							// atm 기기 사용자 변경
		q->front->pre = NULL;							

		wait_min = (H - q->front->enter_hour) * 60 + (M - q->front->enter_min);		// atm 기기 사용시작하는 인원의 대기시간 계산
		T_Wait_Time += wait_min;						// 전체 대기시간에 추가

		q->nextHour = H;				// atm 사용자가 바뀌는 시간은 현재시간 + 사용자의 업무 소요시간
		q->nextMin = M + q->front->work_time;// atm 사용자가 바뀌는 시간은 현재시간 + 사용자의 업무 소요시간

		if (q->nextMin >= 60) {			// nextMin 값이 60 이상일경우 nextHour 값 1 증가 nextMin값 60 감소
			q->nextHour += 1;
			q->nextMin -= 60;
		}

		print_string(q->front, H, M, atm_num);		// 화면에 atm기기 사용시작 문장 출력

		OutCount += 1;					// 은행에서 나간 인원 1 증가
		DoneCount += 1;					// 업무 완료한 인원 1 증가
		q->length -= 1;					// 대기열 길이 감소

		free(out);
	}
}

// 소수인지 아닌지 확인해주는 함수 리턴값이 1일경우 소수 0 일경우 소수가 아님
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

// 10분 마다 수행할 입장번호 소수인원 퇴장 함수
void deAtm_prime(atm* q, int H, int M) {
	if (q->length > 1) {	// 대기인원이 있을경우에만 수행
		int wait_min=0;
		int i=0;
		node* check;					// 체크할 인원

		check = q->front->next;			// 대기인원의 맨 앞부터 확인

		for (i = 0;i < q->length - 2;i++) {	// 체크인원이 rear가 아닐때까지 수행
			if (is_prime(check->enter_min) == 1) {	// 체크 인원의 입장번호가 소수일경우 수행
				node* out;
				node* behind;					// 체크할 인원의 뒤
				node* front;					// 체크할 인원의 앞

				behind = check->next;
				front = check->pre;
				out = check;

				front->next = behind;		// 대기열 공백 채우기
				behind->pre = front;		// 대기열 공백 채우기

				wait_min = (H - out->enter_hour) * 60 + (M - out->enter_min);		// 나가는 인원의 대기시간 계산
				T_Wait_Time += wait_min;						// 전체 대기시간에 추가

				q->length -= 1;						// 대기열 1 감소
				OutCount += 1;
				check = check->next;				// 체크할 사람 다음으로 이동
				free(out);
			}
		}

		//체크인원이 rear일때
		if (is_prime(check->enter_min) == 1) {
			node* out;
			out = check;
			check->pre->next = NULL;
			q->rear = check->pre;

			wait_min = (H - out->enter_hour) * 60 + (M - out->enter_min);		// 나가는 인원의 대기시간 계산
			T_Wait_Time += wait_min;						// 전체 대기시간에 추가

			q->length -= 1;						// 대기열 1 감소
			OutCount += 1;
			free(out);
		}
	}
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*                                           @       메인함수       @                                           *//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int hour = 0;
	int min = 0;
	int line_num = 0;						// lineupATM함수의 결과값 저장 ( ATM배열의 순번 )
	int atm_num = 0;						// 화면에 출력할 atm 번호
	int i = 0;

	srand(time(NULL));

	atm* ATM = (atm*)malloc(sizeof(atm) * 3);				// 3대의 ATM 구조체 선언
	for (i = 0;i < 3;i++) {
		init_atm(&ATM[i]);							// ATM의 구조체 초기화
	}

	for (hour = 9;hour < 11;hour++)
	{
		for (min = 0;min < 60;min++)
		{
			if ((hour == 9) && (min == 0)) {	// 9시에는 사람 입장 안하므로 min 증가
				min++;
			}

			line_num = lineupATM(&ATM[0],&ATM[1],&ATM[2]);	// atm 기기 선택
			atm_num = line_num + 1;


			// 사람 atm 기기에 줄서기
			enAtm(&ATM[line_num], hour, min, atm_num);

			if (min % 10 == 0) {
				// 10분마다 대기인원중 입장번호 소수인 인원 퇴장
				for (i = 0;i < 3;i++) {
					deAtm_prime(&ATM[i], hour, min);
				}
			}


			// 완료 인원 퇴장
			for (i = 0;i < 3;i++) {
				deAtm(&ATM[i], hour, min, i + 1);
			}
		}
	}

	printf("\n 1. 업무 완료한 인원 = %d\n", DoneCount);
	printf("\n 2. 평균 대기 시간 = %d분\n", (T_Wait_Time / OutCount));
	printf("\n 3. 현재 총 대기 인원 = %d\n", (ATM[0].length + ATM[1].length + ATM[2].length - 3));

	free(ATM);
	return 0;
}