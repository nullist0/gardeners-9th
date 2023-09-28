#include <cstdio>

int is_nice(int N, int *input) {
    int ip = 0;
    int stack[1000], sp = -1;

    for (int next = 1; next <= N; next++) {
        if (sp >= 0 && stack[sp] == next) {
            sp--;
            continue;
        }
        while (1) {
            if (ip == N) {
                break;
            }
            if (next == input[ip]) {
                ip++;
                break;
            } else {
                stack[++sp] = input[ip++];
            }
        }
    }
    return sp == -1;
}

int main(void) {
    int N;
    int input[1000], ip = -1;
    int stack[1000], sp = -1;

    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%d", input + i);
    }
    printf("%s\n", is_nice(N, input) ? "Nice": "Sad");

    return 0;
}