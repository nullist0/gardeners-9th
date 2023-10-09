#include <cstdio>

int gcd(int a, int b) {
    if (b % a == 0) return a;
    return gcd(b % a, a);
}

int main(void) {
    int p[2];
    int q[2];

    scanf("%d %d", p, p + 1);
    scanf("%d %d", q, q + 1);

    int g = gcd(p[1], q[1]);
    int n = (q[1] / g) * p[0] + (p[1] / g) * q[0];
    int m = p[1] * (q[1] / g);

    int G = gcd(n, m);

    printf("%d %d\n", n / G, m / G);

    return 0;
}