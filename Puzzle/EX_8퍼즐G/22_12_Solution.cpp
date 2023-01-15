/*
41_EX_8퍼즐G_user
A* algorithm(heap) + hash + bitCompressing
*/
extern void move(int mode);

#define rint register int
const int HLM = 19100;    // heap max size  : 19050
const int LM = 41500;     // keys maxsize   : 41416
const int MOD = 1 << 15;  // hash slot size : 32768

void test(const int puzzle[3][3])
{
    rint decimal[] = { 100'000'000, 10'000'000, 1'000'000, 100'000, 10'000, 1'000, 100, 10, 1 };
    rint adj[][5] = { {1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7} };                     // able index
    rint dir[][5] = { {3,1},{2,3,1},{2,1},{0,3,1},{0,2,3,1},{0,2,1},{0,3},{0,2,3},{0,2} };                     // movable direction
    rint penalty[][10] = { {0,1,2,1,2,3,2,3,4}, {1,0,1,2,1,2,3,2,3}, {2,1,0,3,2,1,4,3,2}, {1,2,3,0,1,2,1,2,3},
    {2,1,2,1,0,1,2,1,2}, {3,2,1,2,1,0,3,2,1}, {2,3,4,1,2,3,0,1,2}, {3,2,3,2,1,2,1,0,1}, {4,3,2,3,2,1,2,1,0} }; // move penalty

    rint i, num = 0, zeroPos = 8, hsc = 0, br;
    for (i = 0; i < 9; ++i) {
        br = puzzle[i / 3][i % 3];
        num = num * 10 + br;
        if (br == 0) zeroPos = i;
        if (i < 8)
            hsc += penalty[i][(br + 8) % 9];
    }

    if (hsc == 0)
        return;

    rint faces[LM] = { 0 }, path[LM] = { 0 };          // keyList, path[i]: parent(16), moveDir(2), zeropos(4)
    rint np = 1, st[MOD] = { 0 }, link[LM] = { 0 };  // chaining hash
    rint heap[HLM] = { 0 }, hn = 0;                  // heap[i]: gsc + hsc(6), gsc(5), keyIndex(16)

    rint gsc, hidx = num % MOD, face;
    faces[1] = num, path[1] = zeroPos;
    st[hidx] = 1;
    heap[++hn] = (hsc << 21) | 1;

    while (hn) {
        rint hTop = heap[1], nd = heap[hn--], c = 2;
        // pop_heap;
        for (; c <= hn && heap[c += (c < hn && heap[c + 1] < heap[c])] < nd; c *= 2)
            heap[c / 2] = heap[c];
        heap[c / 2] = nd;

        rint par = hTop & 65535;
        face = faces[par];
        gsc = (hTop >> 16) & 31;     // current g_score  : movec count
        hsc = (hTop >> 21) - gsc;    // current h_score  : 이동해야할 추정치
        rint czp = path[par] & 15;   // current zero pos
        path[par] >>= 4;             // parent(16), moveDir(2) 만 남기기(zeroPos는 지운다.)

        rint i = 0, j, hidx;
        do {
            rint nzp = adj[czp][i];  // new zero pos
            rint val = face / decimal[nzp] % 10;
            rint nface = face + val * decimal[czp] - val * decimal[nzp];

            // hash probing : find nface
            hidx = nface % MOD;
            for (j = st[hidx]; j && faces[j] != nface; j = link[j]);

            if (j == 0) { // if nface is new face
                rint nhsc = hsc + penalty[czp][(val + 8) % 9] - penalty[nzp][(val + 8) % 9];
                faces[++np] = nface, path[np] = (par << 6) | (dir[czp][i] << 4) | nzp;
                link[np] = st[hidx], st[hidx] = np;
                nd = ((nhsc + gsc + 1) << 21) | ((gsc + 1) << 16) | np;

                if (nface == 123456780) {
                    hn = 0;
                    break;
                }

                // push_heap
                for (c = ++hn; c > 1 && nd < heap[c / 2]; c >>= 1)
                    heap[c] = heap[c / 2];
                heap[c] = nd;
            }
            i++;
        } while (adj[czp][i]);
    }

    rint res[33] = { 0 }, len = 0, k = path[np] >> 4;
    while (k) {
        res[++len] = k & 3;
        k = path[k >> 2];
    }
    for (i = len; i > 0; --i)
        move(res[i]);
}