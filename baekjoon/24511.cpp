#include <cstdio>
#include <queue>
#include <stack>

#define LEN 100000
#define QUEUE 0
#define STACK 1

using namespace std;


int main(void) {
    int N, A[LEN];
    int M, x, tmp;
    stack<int> s;
    queue<int> q;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", A + i);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &tmp);
        if (A[i] == QUEUE) {
            s.push(tmp);
        }
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        scanf("%d", &x);
        q.push(x);
        x = q.front();
        q.pop();
        printf("%d ", x);
    }
    printf("\n");

    return 0;
}