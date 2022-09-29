// 피보나치 수열 순환 구현
int fib(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return (fib(n - 1) + fib(n - 2));
}

// 피보나치 수열 반복 구현
int fib_iter(int n) {
    if (n < 2) return n;
    else {
        int i, tmp, current = 1, last = 0;
        for (i = 2;i <= n;i++) {
            tmp = current;
            current += last;
            last = tmp;
        }
        return current;
    }
}