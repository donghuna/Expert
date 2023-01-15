#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
21_�ټ����_ver01
sqrt decomposition
*/
#include <cstdio>

const int LM = 100005;
const int MOD = 256;

int N, H[LM], T[LM]; // N: ��ü �����, H[] : Ű, T[]: �ӽù迭
int B[LM];           // B[] : block(����)�� �� �ڸ����� ��
int qrr[LM];         // qrr[i] : i��° ����� ������ �ٶ� ��, �ڽź��� �۰ų� ���� ������� ��
int ans[LM];         // ans[i] : i��° ����� Ű

void mergeSort(int* arr, int s, int e) {
    if (s >= e) return;
    int m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(arr, s, m);
    mergeSort(arr, m + 1, e);

    while (i <= m && j <= e) {
        if (arr[i] <= arr[j]) T[k++] = arr[i++];
        else T[k++] = arr[j++];
    }
    while (i <= m) T[k++] = arr[i++];
    while (j <= e) T[k++] = arr[j++];
    for (i = s; i <= e; ++i) arr[i] = T[i];
}

int query(int cnt) {  // cnt��° �ڸ� ã��
    int i = 0;
    for (; B[i / MOD] < cnt; i += MOD) cnt -= B[i / MOD];

    // ������ ���� �ڸ� ����ϱ�
    for (; cnt > 0; ++i) {
        if (H[i] > 0) cnt--;
        if (cnt == 0) return i;
    }
    return -1; // impossible
}

int main() {
#ifdef _WIN32
    freopen("21.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", H + i);
        B[i / MOD] ++;
    }
    for (int i = 0; i < N; ++i) scanf("%d", qrr + i);

    mergeSort(H, 0, N - 1);

    for (int i = N - 1; i >= 0; --i) {
        int ret = query(qrr[i] + 1);
        ans[i] = H[ret];  // get answer

        // update
        H[ret] = 0;
        B[ret / MOD] --;
    }
    for (int i = 0; i < N; ++i) printf("%d\n", ans[i]);
    return 0;
}