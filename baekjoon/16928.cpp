#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

int map[101];

int search() {
    queue<pair<int, int>> q;
    int visited[101];

    memset(visited, 0, sizeof(int) * 101);

    q.push(make_pair(1, 0));

    while(!q.empty()) {
        int position = q.front().first;
        int step = q.front().second;

        q.pop();
        for(int dice = 1; dice <= 6; dice++) {
            if (position + dice > 100) continue;
            
            int nextPosition = map[position + dice] ? map[position + dice] : position + dice;
            int nextStep = step + 1;
            
            if (visited[nextPosition]) continue;
            if (nextPosition == 100) return nextStep;
            visited[nextPosition] = 1;
            q.push(make_pair(nextPosition, nextStep));
        }
    }
    return -1;
}

int main(void) {
    int N, M;
    int x, y, u, v;
    memset(map, 0, sizeof(int) * 101);

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &x, &y);
        map[x] = y;
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &u, &v);
        map[u] = v;
    }

    printf("%d\n", search());

    return 0;
}