#include <cstdio>

long long gcd(long long a, long long b) {
    if (b % a == 0) return a;
    return gcd(b % a, a);
}

int main(void) {
    long long n, m, g;

    scanf("%lld %lld", &n, &m);
    if(n < m) g = gcd(n, m);
    else g = gcd(m, n);

    printf("%lld\n", a * (b / g));
    return 0;
}