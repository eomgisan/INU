def bubbleSort(a, n):
    for i in range(n,0,-1) :
        for j in range(1,i):
            if a[j] > a[j+1] :
                a[j],a[j+1] = a[j+1],a[j]

def selectionSort(a, n):
    for i in range(1,n):
        minimum = i
        for j in range(i,n+1):
            if a[minimum]>a[j] :
                minimum = j
        a[i], a[minimum] = a[minimum],a[i]

        
def exchangeSort(a, n):
    l=1
    while (l<=n):
        for i in range (l+1,n+1):
            if a[l] < a[i]:
                a[l], a[i] = a[i], a[l]
        l += 1   



def checkSort(a, n):

    isSorted = True

    for i in range(1, n):

        if a[i] > a[i+1]:

            isSorted = False

        if not isSorted:

            break

    if isSorted:

        print("오름차순 정렬 완료")

    else:

        print("정렬 오류 발생")

def checkSort2(a, n):

    isSorted = True

    for i in range(1, n):

        if a[i] < a[i+1]:

            isSorted = False

        if not isSorted:

            break

    if isSorted:

        print("내림차순 정렬 완료")

    else:

        print("정렬 오류 발생")




import random, time



N = 10000

a = []
b = []
c = []

a.append(None)

for i in range(N):

    a.append(random.randint(1, N))

b = a.copy()
c = a.copy()

start_time = time.time()

bubbleSort(a, N)

end_time = time.time() - start_time

print("버블 정렬의 실행 시간 (N=%d) : %0.3f"%(N, end_time))

checkSort(a, N)

start_time = time.time()

selectionSort(b, N)

end_time = time.time() - start_time

print("선택 정렬의 실행 시간 (N=%d) : %0.3f"%(N, end_time))

checkSort(b, N)

start_time = time.time()

exchangeSort(c, N)

end_time = time.time() - start_time

print("교환 정렬의 실행 시간 (N=%d) : %0.3f"%(N, end_time))

checkSort2(c, N)


