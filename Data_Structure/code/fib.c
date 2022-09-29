// �Ǻ���ġ ���� ��ȯ ����
int fib(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return (fib(n - 1) + fib(n - 2));
}

// �Ǻ���ġ ���� �ݺ� ����
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