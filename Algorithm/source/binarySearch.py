def binarySearch(a,key,left,right):

    if(left <= right) :
        mid = (left+right)//2
        
        if(key == a[mid]) :
            print('Key = ',key,'mid = ',mid)
            return mid
        elif(key <a[mid]) :
            print('Key = ',key,'mid = ',mid,'left = ',left,'right = ',mid-1)
            return binarySearch(a,key,left,mid-1)
        elif(key >a[mid]) :
            print('Key = ',key,'mid = ',mid,'left = ',mid+1,'right = ',right)
            return binarySearch(a,key,mid+1,right)
    else : return -1

a = list(range(101))


Key = int(input('Key = '))

print(binarySearch(a,Key,1,100))
