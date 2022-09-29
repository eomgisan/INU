// °ÅµìÁ¦°ö ¹Ýº¹ ±¸Çö
double slow_power(double x, int n)
{
    int i;
    double r = 1.0;
    for (i = 0; i < n; i++)
        r = r * x;
    return(r);
}

// °ÅµìÁ¦°ö ¼øÈ¯ ±¸Çö
double power(double x, int n)
{
    if (n == 0) return 1;
    else if ((n % 2) == 0)
        return power(x * x, n / 2);
    else return x * power(x * x, (n - 1) / 2);
}