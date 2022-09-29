def isprime(a) :
    i =2
    while (i<=a/2) :
        if (a%i ==0) : return False
        i = i + 1
    return True

A = int(input('a = '))

print(A, '는 소수인가 ? = ',isprime(A))
