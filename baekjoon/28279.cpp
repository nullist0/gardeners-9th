#include <cstdio>
#include <deque>

#define PUSH_FRONT 1
#define PUSH_BACK 2
#define POP_FRONT 3
#define POP_BACK 4
#define SIZE 5
#define EMPTY 6
#define FRONT 7
#define BACK 8

using namespace std;

int main(void) {
    int N;
    deque<int> d;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int op, val;

        scanf("%d", &op);

        switch (op) {
            case PUSH_FRONT:
                scanf("%d", &val);
                d.push_front(val);
                break;
            case PUSH_BACK:
                scanf("%d", &val);
                d.push_back(val);
                break;
            case POP_FRONT:
                if (d.empty()){
                    val = -1;
                } else {
                    val = d.front();
                    d.pop_front();
                }
                printf("%d\n", val);
                break;
            case POP_BACK:
                if (d.empty()) {
                    val = -1;
                } else {
                    val = d.back();
                    d.pop_back();
                }
                printf("%d\n", val);
                break;
            case SIZE:
                printf("%d\n", d.size());
                break;
            case EMPTY:
                printf("%d\n", d.empty());
                break;
            case FRONT:
                printf("%d\n", d.empty() ? -1 : d.front());
                break;
            case BACK:
                printf("%d\n", d.empty() ? -1 : d.back());
                break;
        }
    }
    return 0;
}