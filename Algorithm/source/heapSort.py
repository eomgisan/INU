def heapify(a,h,m):
    v, j = a[h], h
    while j <= m:
        # 왼쪽 오른쪽 자식중에서 큰거 선택
        if ( j<m and j < j+1 ) :
            print(1)
            print(a)
            j += 1
        # 위에서 선택한 큰거랑 a[h] 비교
        if v > a[j] :
            print(2)
            print(a)
            break
        else :
            print(3)
            print(a)
            a[int(j/2)] = a[j]
        j *= 2
    a[int(j/2)] = v
    print(4)
    print(a)

a = [0,4,5,3,2,6,7,8]
heapify(a,1,7)
        
