def isperfect(a) :
    s = 0
    i = 1
    while (i <= a/2 ) :
        if ( a%i == 0 ) :
            s = s+i
        i = i+1
    if (s == a ) :
        return True
    else :
        return False
A = int(input('a = ' ))

print (A,'는 완전수인가?? = ',isperfect(A))
