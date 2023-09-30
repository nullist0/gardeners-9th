#include <cstdio>
#include <stack>

#define ADD 1
#define POP 2
#define LEN 3
#define EMP 4
#define TOP 5

using namespace std;

int main(void) {
    int N;
    stack<int> s;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int op, val;

        scanf("%d", &op);
        switch (op) {
            case ADD:
                scanf("%d", &val);
                s.push(val);
                break;
            case POP:
                if (s.empty()) {
                    val = -1;
                } else {
                    val = s.top();
                    s.pop();
                }
                printf("%d\n", val);
                break;
            case LEN:
                printf("%d\n", s.size());
                break;
            case EMP:
                printf("%d\n", s.empty());
                break;
            case TOP:
                printf("%d\n", s.empty() ? -1 : s.top());
                break;
        }
    }
    return 0;
}