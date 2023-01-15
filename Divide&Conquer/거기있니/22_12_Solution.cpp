/// *** user.cpp ***
extern int countSameNumber(int guess[]);

const int LM = 100000;
int used[LM + 5], guess[LM + 5];

void consistOf(int N, int K) {
    int i, j, bin = 1;  // bin: 한번에 처리할 갯수, bin의 최대값은 16
    while ((1 << (bin + 1)) - 1 <= K) bin++;
    for (i = 1; i <= N; i += bin) {
        int p = 0, x;
        for (j = 0; j < bin; ++j) {
            int len = 1 << j;  // 1, 2, 4, 8, 16, .., 32768
            for (x = 0; x < len; ++x) {
                guess[p++] = i + j;
            }
        }
        int ret = countSameNumber(guess);
        for (j = 0; j < bin; ++j) {
            used[i + j] = (ret >> j) & 1;
        }
    }
}

int isEntryNumber(int num) {
    return used[num];
}