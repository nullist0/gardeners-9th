#include <cstdio>

int gcd(int a, int b) {
    if (b % a == 0) return a;
    return gcd(b % a, a);
}

int main(void) {
    int T, A, B;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        scanf("%d %d", &A, &B);
        if (A == B) {
            printf("%d\n", A);
        } else if (A < B) {
            printf("%d\n", A * (B / gcd(A, B)));
        } else {
            printf("%d\n", A * (B / gcd(B, A)));
        }
    }
    return 0;
}