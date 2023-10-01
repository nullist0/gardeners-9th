#include <cstdio>
#include <deque>

using namespace std;

deque<pair<int, int>> d;

void move_right(int n) {
    pair<int, int> val;

    for (int i = 0; i < n; i++) {
        val = d.front();
        d.push_back(val);
        d.pop_front();
    }
}

void move_left(int n) {
    pair<int, int> val;

    for (int i = 0; i < n; i++) {
        val = d.back();
        d.push_front(val);
        d.pop_back();
    }
}

int main(void) {
    int N, ind, val;
    pair<int, int> indval;
    scanf("%d", &N);

    for (ind = 1; ind <= N; ind++) {
        scanf("%d", &val);
        d.push_back(make_pair(ind, val));
    }

    for (int i = 0; i < N; i++) {
        indval = d.front();
        d.pop_front();

        ind = indval.first;
        val = indval.second > 0 ? indval.second - 1 : indval.second;

        printf("%d ", ind);
        if (d.empty() || val == 0) continue;
        val > 0 
            ? move_right(val % d.size()) 
            : move_left((-val) % d.size());
    }
    printf("\n");
    return 0;
}