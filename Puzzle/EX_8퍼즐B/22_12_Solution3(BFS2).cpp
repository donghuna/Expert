/*
39_EX8∆€¡ÒB_user_BFS_ver02
shortest path version
*/
extern void move(int);
#define rint register int
const int LM = 181440 + 5;
const int MOD = 1 << 20;

int flag = 1, key = 12345678;
int deci[] = { 100'000'000, 10'000'000, 1'000'000, 100'000, 10'000, 1'000, 100, 10, 1 };
int adj[][5] = { {1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7} };
int dir[][5] = { {2,0},{3,2,0},{3,0},{1,2,0},{1,3,2,0},{1,3,0},{1,2},{1,3,2},{1,3} };
int faces[9][LM], zpos[9][LM], pathIdx[9][LM], pathDir[9][LM];

struct Hash {
    int np, st[MOD], link[LM];
    int probing(int type, int k) {
        rint hidx = k / 10 % MOD, i = st[hidx];
        for (; i && faces[type][i] != k; i = link[i]);
        if (i == 0)
            i = ++np, link[np] = st[hidx], st[hidx] = np;
        return i;
    }
}tab[9];

void BFS(int type, int src, Hash& htab) {
    faces[type][htab.probing(type, src)] = src;
    zpos[type][1] = type;
    rint fr = 1, re = 2;
    while (fr < re) {
        rint k = faces[type][fr], czp = zpos[type][fr], i = 0;
        do {
            rint nzp = adj[czp][i];
            rint d = dir[czp][i++];
            rint val = k / deci[nzp] % 10;
            rint n = k - val * deci[nzp] + val * deci[czp];
            rint idx = htab.probing(type, n);
            if (idx >= re) {
                faces[type][re] = n;
                zpos[type][re] = nzp;
                pathIdx[type][re] = fr;
                pathDir[type][re] = d;
                re++;
            }
        } while (adj[czp][i]);
        fr++;
    }
}

//struct Data {
//  Data() {
//      rint i, t;
//      for (i = 0; i < 9; ++i) {
//          BFS(i, key, tab[i]);
//          if (i < 8) {
//              t = key / deci[i + 1] % 10;
//              key += t * deci[i] - t * deci[i + 1];
//          }
//      }
//  }
//}obj;

void test(const int puzzle[][3], const int target[][3])
{
    rint i, code = 0, tg[10] = { 0 }, type = 0;
    if (flag) {
        flag = 0;
        for (i = 0; i < 9; ++i) {
            BFS(i, key, tab[i]);
            if (i < 8) {
                rint t = key / deci[i + 1] % 10;
                key += t * deci[i] - t * deci[i + 1];
            }
        }
    }

    for (i = 0; i < 9; ++i) {
        if (target[i / 3][i % 3] == 0) type = i;
    }
    for (i = 0; i < 9; ++i) {
        tg[target[i / 3][i % 3]] = i <= type ? i < type ? i + 1 : 0 : i;
    }

    for (i = 0; i < 9; ++i) {
        code = code * 10 + tg[puzzle[i / 3][i % 3]];
    }

    i = tab[type].probing(type, code);
    while (i > 1) {
        move(pathDir[type][i]);
        i = pathIdx[type][i];
    }
}