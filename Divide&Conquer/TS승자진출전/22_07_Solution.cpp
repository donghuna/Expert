// *** user.cpp ***
extern void swapOrder(int indexA, int indexB);
const int LM = 1 << 17;
int A[LM + 5] = {1}, pos[LM + 5];

void modify(int N, int order[]) {
    // 1. build model sequence
    for (int i = 1; i < N; i *= 2) {
        for (int j = i - 1; j >= 0; --j) {
            A[j * 2] = A[j];
            A[j * 2 + 1] = A[j] + i;
        }
    }

    // 2. order[i]가 어디에 위치하는가? 
    for (int i = 0; i < N; ++i)
        pos[order[i]] = i;

    // 3. 공정한 대진표로 바꾸기
    for (int i = 0; i < N; ++i) {
        if (order[i] != A[i]) {
            int j = pos[A[i]];
            swapOrder(i, j);
            int t = order[i];
            order[i] = order[j];
            order[j] = t;

            pos[order[i]] = i;
            pos[order[j]] = j;
        }
    }
}
