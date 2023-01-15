/*
19_FASTSort_user_ver02
self counting sort + hw_sort
SCORE : 1**

[hw_sort를 적극 이용하기]
1. hw_sort()사용시간은 점수에 반영되지 않는다.
2. hw_sort()는 signed_short를 정렬한다.
3. hw_sort()는 정확히 1024개만 정렬한다.
4. hw_sort()는 오름차순으로만 정렬한다.
*/
extern void hw_sort(short data[1024]);

#define LM (1048576)
#define MASK (65535)
#define rint register int

using UI = unsigned int;
const unsigned int MSB = 1 << 31;
const int CLM = 1 << 11; // 2048
const int MK = CLM - 1;  // 2047 : bitmask

// ***** 상위 11비트에 대하여 오름차순 정렬하기(상위 11bit로 그룹짓기) *****
void selfCountingSort(int lev, unsigned int* p, int n, int* cnt) {
    rint i, j, k;
    for (i = 0; i < CLM; ++i) cnt[i] = 0;
    for (i = 0; i < n; ++i) cnt[(p[i] >> lev) & MK] ++;  // 개수 세기
    for (i = 1; i < CLM; ++i) cnt[i] += cnt[i - 1];      // 누적합 구하기
    for (i = n - 1; i >= 0; --i) {
        if (p[i] & MSB) p[i] ^= MSB;  // MSB로 표시된 수는 이미 자기 자리 찾은 수이므로 MSB만 제거하기
        else {  // 안정정렬을 무시하고 정렬된 수에 MSB로 표시하면서 자체 배열로 정렬하기
            for (j = --cnt[(p[i] >> lev) & MK]; i != j; j = --cnt[(p[i] >> lev) & MK]) {
                // 위치를 교환하기
                k = p[j];
                p[j] = p[i] | MSB;   // 자기 자리 찾은 수는 MSB로 표시하기
                p[i] = k;
            }
        }
    }
}

void test(unsigned int data[LM]) {
    int origin[2050] = { 0 }, cnt[2050] = { 0 };
    int entry[65538] = { 0 }; // 등장한 수들 표시
    unsigned short A[2050], trr[2050];
    rint i, j, k, n = 0, m, t;

    // extract entry value
    for (i = 0; i < LM; ++i) {
        // a: 상위 16bit정수, b: 하위 16bit정수
        int a = (data[i] >> 16) & MASK, b = data[i] & MASK;

        // 처음 등장한 수라면 부호 bit를 반전시켜(hw_sort는 signed short만 정렬가능함) trr에 저장
        if (entry[a] == 0) entry[a] = 1, trr[n++] = a ^ 32768;
        if (entry[b] == 0) entry[b] = 1, trr[n++] = b ^ 32768;
    }

    // 최대 2048개가 될 수 있으므로 2로 나누어 정렬(hw_sort는 정확히 1024개만 정렬가능함)
    hw_sort((short*)trr), hw_sort((short*)(trr + n - 1024));

    for (i = 0; i < n; ++i) trr[i] ^= 32768;      // 부호 bit를 원래대로 복원

    // 둘로 나누어 정렬된 trr배열을 merge시키기 : O(n)
    m = n - 1024, i = 0, j = m, k = 0;
    while (i < m && j < n) {
        if (trr[i] < trr[j]) A[k++] = trr[i++];
        else A[k++] = trr[j++];
    }
    while (i < m) A[k++] = trr[i++];
    while (j < n) A[k++] = trr[j++];

    // desc renumbering
    for (i = n - 1, j = 0; i >= 0; --i) { // 역순으로 번호매기기(hw_sort()는 오름차순으로만 정렬한다.)
        origin[j] = A[i];   // 원래의 수 백업
        entry[A[i]] = j++;  // 원래의 수에 renumbering id부여하기 (16bit수에 11bit번호가 부여된다)
    }

    // 32bit --> 22bit로 변경하기
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 16) & MASK, k = data[i] & MASK;
        data[i] = ((unsigned int)entry[j] << 11) | entry[k];
    }

    selfCountingSort(11, data, LM, cnt);  // 상위 11비트에 대하여 계수정렬(상위11비트로 그룹짓기)

    // 상위 11bit로 그룹지어 모여있는 하위 11bit를 그룹내에서 정렬하기
    for (i = 0; i < LM; i = j) {
        // 그룹의 구간찾기
        t = (data[i] >> 11) & MASK;                    // 구간 식별자(상위 11bit)            
        j = i;                                         // i: 구간의 시작
        for (; j < LM && (data[j] >> 11) == t; ++j);   // j: 구간의 끝
        n = j - i;                                     // n: 구간의 크기
        if (n < 1025) {                                // 구간 크기가 1024이하인 경우
            for (k = 0; k < n; ++k) A[k] = data[i + k] & MK;  // 임시로 A[]에 백업
            for (; k < 1024; ++k) A[k] = 2050;         // 1024미만이라면 나머지 공간을 큰값으로 채우기
            hw_sort((short*)A);
            for (k = 0; k < n; ++k) data[i + k] = (t << 11) | A[k]; // 원래 배열로 복원
        }
        else if (n < 2049) {                           // 구간 크기가 1025 ~ 2048인 경우
            for (k = 0; k < n; ++k) trr[k] = data[i + k] & MK;  // 임시로 A[]에 백업

            hw_sort((short*)trr), hw_sort((short*)(trr + n - 1024));
            {
                // 둘로 나누어 정렬된 trr배열을 merge시키기 : O(n)
                rint m = n - 1024, i = 0, j = m, k = 0;
                while (i < m && j < n) {
                    if (trr[i] < trr[j]) A[k++] = trr[i++];
                    else A[k++] = trr[j++];
                }
                while (i < m) A[k++] = trr[i++];
                while (j < n) A[k++] = trr[j++];
            }

            for (k = 0; k < n; ++k) data[i + k] = (t << 11) | A[k];  // 원래 배열로 복원
        }
        else    // 구간의 크기가 2048을 초과하는 경우 : 이경우는 거의(강사는 아직 못봄) 나오지 않는다.
            selfCountingSort(0, data + i, n, cnt);     // 하위 11비트에 대하여 계수정렬하기
    }

    // original value로 복원하기.
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 11) & MK;                      // 상위 11bit정수
        k = data[i] & MK;                              // 하위 11bit정수
        data[i] = ((unsigned int)origin[j] << 16) | origin[k];
    }
}