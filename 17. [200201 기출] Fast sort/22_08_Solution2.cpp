/*
17_FAST SORT_ :
hw_sort()를 이용하기
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
    int entry[65538] = { 0 };
    unsigned short A[2050], trr[2050];
    rint i, j, k, n = 0, m;

    // extract entry value
    for (i = 0; i < LM; ++i) {
        int a = (data[i] >> 16) & MASK, b = data[i] & MASK;
        if (entry[a] == 0) entry[a] = 1, trr[n++] = a ^ 32768;
        if (entry[b] == 0) entry[b] = 1, trr[n++] = b ^ 32768;
    }
    hw_sort((short*)trr), hw_sort((short*)(trr + n - 1024));

    for (i = 0; i < n; ++i) trr[i] ^= 32768;

    m = n - 1024, i = 0, j = m, k = 0;
    while (i < m && j < n) {
        if (trr[i] < trr[j]) A[k++] = trr[i++];
        else A[k++] = trr[j++];
    }
    while (i < m) A[k++] = trr[i++];
    while (j < n) A[k++] = trr[j++];

    // desc renumbering
    for (i = n - 1, j = 0; i >= 0; --i) {
        origin[j] = A[i], entry[A[i]] = j++;
    }

    // 32bit --> 22bit
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 16) & MASK, k = data[i] & MASK;
        data[i] = ((unsigned int)entry[j] << 11) | entry[k];
    }

    rSort(11, data, LM, cnt);

    // original value로 복원하기.
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 11) & MK, k = data[i] & MK;
        data[i] = ((unsigned int)origin[j] << 16) | origin[k];
    }
}
