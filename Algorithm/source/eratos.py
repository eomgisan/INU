def eratos(a,n):
    a[1] = 0
    i =2
    while (i<=n/2):
        j =2
        while (i*j <=n):
            a[i*j] = 0
            j = j+1
        i = i+1
    return a

N = int(input('숫자입력 : '))
A = list(range(N+1))
res = eratos(A,N)
print('자연수 N까지의 소수들 = ', end ='')
for i in range(len(A)):
    if(res[i]) :
        print(res[i], end =' ')
