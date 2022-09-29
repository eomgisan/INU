def mergeSort(a, l, r):
    if(r>l) :
        m = int((l+r)/2)
        mergeSort(a, l, m)
        mergeSort(a, m+1, r)
        merge(a, l, m ,r)

def merge(a,l,m,r):
    i,j,k = l,m+1,l

# 왼쪽 또는 오른쪽 리스트중 첫번째 원소부터 비교하면서 작은거를 새로운 리스트에 추가
# 왼쪽 또는 오른쪽 리스트중 하나라도 모든 원소를 추가했으면 종료
    while i<=m and j <= r :
        if(a[i] < a[j]) :
            b[k] = a[i]
            i, k = i+1, k+1
        else :
            
            b[k] = a[j]
            j, k = j+1, k+1

# 왼쪽 리스트 원소를 모두 썼을때 오른쪽 리스트를 순서대로 가져온다
    if(i>m):
        for p in range(j,r+1):
            b[k] = a[p]
            k = k+1
# 오른쪽 리스트 원소를 모두 썼을때 왼쪽 리스트를 순서대로 가져온다
    else :
        for p in range(i,m+1):
            b[k] = a[p]
            k = k+1

# 새로운 리스트를 기존 리스트로 덮어쓰기
    for p in range(l,r+1):
        a[p] = b[p]
     




def checkSort(a, n):

    isSorted = True

    for i in range(1, n):

        if a[i] > a[i+1]:

            isSorted = False

        if not isSorted:

            break

    if isSorted:

        print("정렬 완료")

    else:

        print("정렬 오류 발생")



import random, time



N = 5000

a = []
b = []

a.append(None)
b.append(None)
for i in range(N):

    a.append(random.randint(1, N))


start_time = time.time()

mergeSort(a, 1, N)

end_time = time.time() - start_time

print("합병 정렬의 실행 시간 (N=%d) : %0.3f"%(N, end_time))

checkSort(a, N)
