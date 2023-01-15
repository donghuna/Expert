/*
39_EX8����B_user_BFS_ver01
custom queue + custom hash
srcPuz[][] => basePuz[][] => destPuz[][]
*/
extern void move(int mode);

#define rint register int

const int LM = 181440 + 5;
const int MOD = 1 << 20;
struct Data {
    int face, zp, pathIdx, pathDir;
}que[LM], t;
int fr, re;

struct Hash {
    int st[MOD], link[LM];
    int probing(int face) {
        int hidx = face % MOD, i = st[hidx];
        for (; i && que[i].face != face; i = link[i]);
        return i;
    }
    void insert(int face, int np) {
        int hidx = face % MOD;
        link[np] = st[hidx], st[hidx] = np;
    }
}hmap;

int decimal[] = { 100'000'000,10'000'000,1'000'000,100'000,10'000,1'000,100, 10, 1 };
int adj[][5] = { {1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7} };
int dir[][5] = { {3,1},{2,3,1},{2,1},{0,3,1},{0,2,3,1},{0,2,1},{0,3},{0,2,3},{0,2} };

void BFS() {
    fr = re = 1;
    que[re++] = { 123456780, 8, 0, 0 };
    hmap.insert(123456780, 1);
    while (fr < re) {
        t = que[fr];
        rint face = t.face;            // current face
        rint czp = t.zp;               // current zero pos
        rint i = 0;                    // adj index
        do {
            rint nzp = adj[czp][i];    // next zero pos
            rint val = face / decimal[nzp] % 10;  // target value
            rint newFace = face - val * decimal[nzp] + val * decimal[czp];
            if (hmap.probing(newFace) == 0) {
                hmap.insert(newFace, re);
                que[re++] = { newFace, nzp, fr, dir[czp][i] ^ 1 };
            }
            i++;
        } while (adj[czp][i]);
        ++fr;
    }
}


void test(const int srcPuz[][3], const int destPuz[][3])
{
    // If you modify the puzzle const data by bypassing it, you will be disqualified.
    if (re == 0)  // 10000���� TC�߿� ó�� 1���� ����
        BFS();
    rint i, j, face = 0;

    /// 1. srcPuz[][]�� �⺻ ������� �ϱ� : EX����A�� ����.
    for (i = 0; i < 3; ++i) for (j = 0; j < 3; ++j)
        face = face * 10 + srcPuz[i][j];

    i = hmap.probing(face);
    while (i > 1) {
        move(que[i].pathDir);
        i = que[i].pathIdx;
    }

    /// 2. �⺻ ����� destPuz[][]�� �ϱ� : �߰��� �κ�
    rint res[35] = { 0 };  // ������ �������� ����� ������ �ϹǷ� ������ �迭�� �ʿ��ϴ�.
    face = 0;              // ���� face�����ϱ�
    for (i = 0; i < 3; ++i) for (j = 0; j < 3; ++j)
        face = face * 10 + destPuz[i][j];

    i = hmap.probing(face), j = 0;
    while (i > 1) {        // ����face�κ��� �⺻ face(123456780)���� ��� ���ϱ�
        res[++j] = que[i].pathDir ^ 1;
        i = que[i].pathIdx;
    }

    while (j)              // �⺻ face(123456780)�κ��� ���� face���� ��� ������
        move(res[j--]);
    /////////////////////////////////
}