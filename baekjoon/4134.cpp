// Online C++ compiler to run C++ program online
#include <cstdio>
#define N 70000

int is_not_primes[N + 1];

void init_primes() {
    is_not_primes[0] = is_not_primes[1] = 1;
    for(int n = 2; n <= N; n++) {
        if (is_not_primes[n]) continue;
        for(int k = 2; n * k <= N; k++) {
            is_not_primes[n * k] = 1;
        }
    }
}

int is_prime(long long m) {
    if (m <= N) return !is_not_primes[m];
    for(int n = 2; n <= N; n++) {
        if (!is_not_primes[n] && m % n == 0) return 0;
    }
    return 1;
}

long long next_prime(long long start) {
    for(long long m = start; ; m++) {
        if (is_prime(m)) return m;
    }
    return -1;
}

int main() {
    int T;
    long long m;
    
    init_primes();
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        scanf("%lld", &m);
        printf("%lld\n", next_prime(m));
    }
    return 0;
}