///===== user.cpp =====
extern int orderCheck(int left, int right);
#define rint register int
const int LM = 100005;

int A[LM], T[LM];

void mergeSort(int s, int e) {
    // 1. base condition
    if (s >= e) return;
    // 2. devide & conquer
    rint m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(s, m), mergeSort(m + 1, e);
    // 3. merge
    while (i <= m && j <= e) {
        if (orderCheck(A[i], A[j])) T[k++] = A[i++];
        else T[k++] = A[j++];
    }
    while (i <= m) T[k++] = A[i++];
    while (j <= e) T[k++] = A[j++];

    // 4. copy
    for (i = s; i <= e; ++i) A[i] = T[i];
}

void array_restore(int arrCount, int dat[]) {
    // implement here
    for (rint i = 0; i < arrCount; ++i) A[i] = i; // 학생번호를 저장
    mergeSort(0, arrCount - 1);                  // 학생번호를 정렬
    for (rint i = 0; i < arrCount; ++i) dat[A[i]] = i + 1;  // 카드번호는 1_base
}
