#include <cstdio>
#include <cmath>

#define MAX 1000000

int is_not_prime[MAX+1];

int main(void) {
    int sq = sqrt(MAX);
    for (int n = 2; n < sq; n++) {
        if (is_not_prime[n] == 1) continue;
        for (int k = 2; k * n <= MAX; k++) is_not_prime[k * n] = 1;
    }

    int T, N, count;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        count = 0;
        scanf("%d", &N);

        for (int n = 2; n <= N / 2; n++) {
            if (!is_not_prime[n] && !is_not_prime[N - n]) count++;
        }
        printf("%d\n", count);
    }

    return 0;
}