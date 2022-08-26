/*
17_FAST SORT
hw_sort()를 사용하지 않는 version
*/
#define LM (1048576)
#define MASK (65535)
#define rint register int

const unsigned int F = 1 << 30;
const int CLM = 1 << 11;
const int MK = CLM - 1;  // mask

extern void hw_sort(short data[1024]);

void rSort(int lev, unsigned int*p, int n, int*cnt) {
    rint i, j, k;
    for (i = 0; i < CLM; ++i) cnt[i] = 0;
    for (i = 0; i < n; ++i) cnt[(p[i] >> lev) & MK] ++;
    for (i = 1; i < CLM; ++i) cnt[i] += cnt[i - 1];
    for (i = n - 1; i >= 0; --i) {
        if (p[i] & F) p[i] ^= F;
        else {
            for (j = --cnt[(p[i] >> lev) & MK]; ; j = --cnt[(p[i] >> lev) & MK]) {
                k = p[j];
                p[j] = p[i] | F;
                p[i] = k;
                if (i == j) break;
            }
        }
    }
    if (lev <= 0) return;
    for (i = j = 0; i < n; i = j) {
        int tg = (p[i] >> lev);
        for (; j < n && tg == (p[j] >> lev); ++j);
        rSort(0, p + i, j - i, cnt);
    }
}

void test(unsigned int data[LM]) {
    int origin[2050] = { 0 }, cnt[2050] = { 0 };
    unsigned int entry[65536] = { 0 }; // 종자수를 index로 표시하여 renumbering : 131072
    rint i, j, k, n = 0;
    // extract entry value
    for (i = 0; i < LM; ++i)
        entry[(data[i] >> 16) & MASK] = entry[data[i] & MASK] = 1;

    // descending order renumbering
    for (i = 65535; i >= 0; --i) if (entry[i]) {
        origin[n] = i;   // 16비트에 대하여 내림차순 정렬
        entry[i] = n++;  // 내림차순 정렬을 위하여 역순으로 renumberng
    }

    // 32bit --> 22bit compressing
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 16) & MASK;  // 상위 16비트
        k = data[i] & MASK;          // 하위 16비트
        data[i] = (entry[j] << 11) | entry[k];  // 22비트로 바꾸기
        cnt[entry[j]]++;// 상위 16비트를 renumbering 한 값에 대하여 개수세기
    }

    rSort(11, data, LM, cnt);

    // original value로 복원하기.
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 11) & MK, k = data[i] & MK;
        data[i] = ((unsigned int)origin[j] << 16) | origin[k];
    }
}
