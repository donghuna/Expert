/*
25_EX최단경로_user_naiveTest01_STL
*/
#include <cstdio>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

int dr[] = { 1, 0, -1, 0 }; // 하, 우, 상, 좌
int dc[] = { 0, 1, 0, -1 };
struct Data {
    int r, c, u, lev;  // 위치(r, c), 값(u), 방문한 셀의 수(lev)
};
queue<Data> que;

int maxQueSize;

char(*map)[40000];

int push(int r, int c, int u, int lev) {
    if (r < 0 || r > 39999 || c < 0 || c > 39999 || map[r][c] > 3) return 0;
    int v = map[r][c];
    if (abs(u - v) > 1) return 0;
    if (r == 39999 && c == 39999) return lev;
    que.push({ r, c, v, lev });
    map[r][c] = 4;
    return 0;
}

int test(char map[40000][40000]) {
    ::map = map;
    que.push({ 0, 0, map[0][0], 1 });
    map[0][0] = 4;
    while (!que.empty()) {
        maxQueSize = max(maxQueSize, (int)que.size());
        Data t = que.front();
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int lev = push(t.r + dr[i], t.c + dc[i], t.u, t.lev + 1);
            if (lev) {
                printf("maxQueSize : %d\n", maxQueSize);
                return lev;
            }
        }
    }
    return 0;
}