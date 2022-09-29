def bubbleSort(a, n):
    for i in range(n,0,-1) :
        for j in range(1,i):
            if a[j] > a[j+1] :
                a[j],a[j+1] = a[j+1],a[j]
    


def CocktailShakerSort(a, n):
    l=1
    r=n
    while (l<=r):
        if((r-l)%2==1):
            for i in range(l,r):
                if(a[i] > a[i+1]):
                    a[i],a[i+1] = a[i+1],a[i]
            r -= 1
        else:
            for i in range(r,l,-1):
                if(a[i] < a[i-1]):
                    a[i], a[i-1] = a[i-1], a[i]                
            l += 1



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



N = 10000

a = []

a.append(None)

for i in range(N):

    a.append(random.randint(1, N))

b = []
b = a.copy()


start_time = time.time()

bubbleSort(a, N)

end_time = time.time() - start_time

print("버블 정렬의 실행 시간 (N=%d) : %0.3f"%(N, end_time))

checkSort(a, N)

start_time = time.time()

CocktailShakerSort(b, N)

end_time = time.time() - start_time

print("칵테일 쉐이커 정렬의 실행 시간 (N=%d) : %0.3f"%(N, end_time))

checkSort(b, N)
