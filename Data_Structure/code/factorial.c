// ���丮�� �ݺ� ����
int factorial_iter(int n)
{
    int k, v = 1;
    for (k = n; k > 0; k--)
        v = v * k;
    return(v);
}

// ���丮�� ��ȯ ����

int factorial(int n)
{
    if (n <= 1) return(1);
    else return (n * factorial(n - 1));
}
