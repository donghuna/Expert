#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
40_EX_8퍼즐F_user
BFS
*/
extern void move(int);
#define rint register int
const int LM = 181440 + 5;
const int MOD = 1 << 20;

int flag = 1, entry[] = { 12345678, 102345678, 120345678, 123045678, 123405678, 123450678, 123456078, 123456708, 123456780,
                         21543876, 201543876, 210543876, 321054876, 321504876, 321540876, 321654087, 321654807, 321654870 };
int deci[] = { 100'000'000, 10'000'000, 1'000'000, 100'000, 10'000, 1'000, 100, 10, 1 };
int adj[][5] = { {1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7} };
int dir[][5] = { {2,0},{3,2,0},{3,0},{1,2,0},{1,3,2,0},{1,3,0},{1,2},{1,3,2},{1,3} };

struct Puzzle {
    int type, que[LM], pathIdx[LM], pathDir[LM], zpos[LM], step[LM];
    int np, st[MOD], link[LM];
    int hidx;
    int probing(int type, int k) {
        hidx = k / 10 % MOD;
        rint i = st[hidx];
        for (; i && que[i] != k; i = link[i]);
        return i;
    }
    void BFS(int type, int src) {
        hidx = src / 10 % MOD;
        link[++np] = st[hidx], st[hidx] = np;
        que[1] = src;
        zpos[1] = type % 9;
        rint fr = 1, re = 2;
        while (fr < re) {
            rint k = que[fr], i = zpos[fr], j = 0;
            do {
                rint a = adj[i][j], d = dir[i][j++];
                rint r = k / deci[a] % 10;
                rint n = k - r * deci[a] + r * deci[i];
                rint idx = probing(type, n);
                if (idx == 0) {
                    link[++np] = st[hidx], st[hidx] = np;
                    que[re] = n;
                    pathIdx[re] = fr;
                    pathDir[re] = d;
                    zpos[re] = a;
                    step[re] = step[fr] + 1;
                    re++;
                }
            } while (adj[i][j]);
            fr++;
        }
    }
    int getStep(int i) {
        int ret = step[i];
        while (i > 1) {
            move(pathDir[i]);
            i = pathIdx[i];
        }
        return ret;
    }
}puz[18];
//
//struct Data {
//  Data() {
//      for (rint i = 0; i < 18; ++i) {
//          puz[i].BFS(i, entry[i]);
//      }
//  }
//}obj;

int test(const int srcPuz[][3], const int destPuz[][3])
{
    // If you modify the puzzle const data by bypassing it, you will be disqualified
    rint i, j, k, code = 0, base[10] = { 0 }, renum[10] = { 0 }, type;
    if (flag) {
        flag = 0;
        for (i = 0; i < 18; ++i) {    // 유형별 전처리
            puz[i].BFS(i, entry[i]);
        }
    }

    rint trr[10] = { 0 }, invCnt = 0;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j)
            trr[i * 3 + j] = destPuz[i][j];
    }
    for (type = 0; type < 9 && trr[type]; ++type);

    for (i = 0; i < 8; ++i) {
        for (j = i + 1; j < 9; ++j)
            if (trr[j] && trr[i] > trr[j]) invCnt++;
    }

    if (invCnt % 2)
        type += 9;

    k = entry[type];
    for (i = 8; i >= 0; --i, k /= 10) base[i] = k % 10;

    for (i = 0; i < 9; ++i) {
        renum[trr[i]] = base[i];
    }

    for (i = 0; i < 9; ++i) {
        code = code * 10 + renum[srcPuz[i / 3][i % 3]];
    }

    i = puz[type].probing(type, code);
    if (i == 0)
        return -1;

    return puz[type].getStep(i);   // 최소 이동수 반환하기
}