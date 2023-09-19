#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int map[501][501];
int M, N;

int search() {
    int count[501][501];
    queue<pair<int, int>> q;

    memset(count, 0, sizeof(count));
    q.push(make_pair(0, 0));

    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;

        count[y][x] += 1;
        q.pop();

        for(int i = 0; i < 4; i++) {
            int ny = y + dirs[i][0];
            int nx = x + dirs[i][1];

            if(ny < 0 || ny >= M || nx < 0 || nx >= N) continue;
            q.push(make_pair(ny, nx));
        }
    }

    return count[M-1][N-1];
}

int main(void) {
    scanf("%d %d", &M, &N);

    for(int y = 0; y < M; y++) {
        for(int x = 0; x < N; x++) {
            scanf("%d", &map[y][x]);
        }
    }
    return 0;
}