def isPalindrome(s):
    i =0
    j = len(s)-1
    while (i<j):
        if(s[i] != s[j]) :
            return False
        i = i+1
        j = j-1
    return True

S = input('문자열 입력 = ')
print (S,'는 회문인가 ? = ',isPalindrome(S))
