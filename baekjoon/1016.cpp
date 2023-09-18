#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#define N 1000000
#define M 1000000
#define INF 10000

using namespace std;

int isprime[N + 1];
int isnotsq[M + 1];

int main() {
    long long min, max;
    vector<int> primes;
    
    for (int n = 0; n < N; n++) {
        isprime[n] = INF;
        isnotsq[n] = INF;
    }
    scanf("%lld %lld", &min, &max);
    for (int n = 2; n < N; n++) {
        if (isprime[n] == INF) {
            isprime[n] = 1;
            for (int k = 2; k * n < N; k++) {
                isprime[k * n] = 0;
            }
            primes.push_back(n);
        }
    }
    
    int count = 0;
    for (int m = 0; m <= max - min; m++) {
        if (isnotsq[m] != INF) continue;
        isnotsq[m] = 1;
        for (int i = 0; i < primes.size(); i++) {
            long long n = primes[i];
            if (n * n > min + m) break;
            if (((min + m) % (n * n)) == 0) {
                isnotsq[m] = 0;
                break;
            }
        }
        if (isnotsq[m]) {
            count += 1;
            continue;
        }
        for (int k = 2; k * (min + m) <= max; k++) {
            isnotsq[k * (min + m) - min] = isnotsq[m];
        }
    }
    printf("%d\n", count);
    return 0;
}