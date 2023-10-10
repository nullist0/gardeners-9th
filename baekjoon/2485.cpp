#include <cstdio>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b) {
    if (b % a == 0) return a;
    return gcd(b % a, a);
}

int main(void) {
    int N;
    long long _min = 1e10, _max = 0;
    long long a, b, dist, g = 0;

    scanf("%d", &N);

    scanf("%lld", &a);
    _min = _max = a;
    for(int i = 1; i < N; i++) {
        scanf("%lld", &b);
        dist = abs(a - b);
        _min = min(b, _min);
        _max = max(b, _max);
        
        a = b;
        if (g == 0) {
            g = dist;
            continue;
        }
        if (g < dist) {
            g = gcd(g, dist);
        } else {
            g = gcd(dist, g);
        }
    }

    printf("%lld\n", (_max - _min) / g - N + 1);

    return 0;
}