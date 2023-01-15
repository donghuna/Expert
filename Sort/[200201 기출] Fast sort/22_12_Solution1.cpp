/*
19_FAST_SORT_user_ver01
 hw_sort()를 사용하지 않는 version
 score : 2**
1. 문제 요약:
    (1) 16bit(0~65535)수 2048개의 수를 랜덤 추출(일부 같은수 포함)
    (2) 2048개의 수를 이용하여 32bit(상위16bit, 하위 16bit)정수 1048576개를 생성
    (3) 사용자는 1M 한도의 지역메모리를 이용하여 정렬해야 함.
        사용자는 main.cpp 의 hw_sort(short data[1024])함수를 사용할 수 있음.
        [hw_sort]
        ① hw_sort()사용시간은 점수에 반영되지 않는다.
        ② hw_sort()는 signed_short를 정렬한다.
        ③ hw_sort()는 정확히 1024개만 정렬한다.
        ④ hw_sort()는 오름차순으로만 정렬한다.
2. 문제 분석:
  (1) 데이터 생성은 2048개의 16bit정수를 이용하여 만들어진다.
        따라서 16비트 단위로 보면 많아야 2048개의 서로다른 정수가 있다.
    (2) test()함수로 주어지는 데이터는 unsigned int 타입이지만
        hw_sort()로 정렬할 수 있는 정수는 short 타입이다.
    (3) 1M범위의 지역메모리만을 허용하므로 메모리 공간 사용을 최적화할 필요가 있다.
    (4) 점수는 정렬 시간을 통하여 체크되므로 가능한 빠른속도로 정렬해야 한다.
    (5) 어떤 정렬을 사용할수 있을까?
3. solution sketch
   : 다양한 해법이 있겠지만 hw_sort()를 사용하지 않는 방법을 생각해본다.
  (1) 약 2048개의 정수를 골라 이를 이용하여 32bit정수를 22bit정수로 바꿀수 있다.
        advanced_hash로 볼수 있다.
    (2) 22bit 정수에서 상위 11bit로 counting sort 한다.
    (3) 상위 11bit구간별 하위 11bit로 counting sort 한다.
    (4) 11bit정수를 원래의 32bit정수로 바꾼다.
    (5) 공간복잡도 : 65536 * 2 + 2048 * 4 + 2048 * 4 = 131072 + 16384 = 147456
        시간복잡도 : 두번의 counting sort를 진행하므로 O(1048576)
*/
#define LM (1048576)
#define MASK (65535)
#define rint register int

const unsigned int MSB = 1 << 31;
const int CLM = 1 << 11;
const int MK = CLM - 1;  // mask

extern void hw_sort(short data[1024]);

// 재귀버전 self radix sort(right_bit_shift_size, 구간 시작 포인터, 구간 크기, 개수를 셀 배열)
void rSort(int lev, unsigned int* p, int n, int* cnt) {
    rint i, j, k;
    for (i = 0; i < CLM; ++i) cnt[i] = 0;
    for (i = 0; i < n; ++i) cnt[(p[i] >> lev) & MK] ++;
    for (i = 1; i < CLM; ++i) cnt[i] += cnt[i - 1];
    for (i = n - 1; i >= 0; --i) {
        if (p[i] & MSB) p[i] ^= MSB;   // 이미정렬된 경우라면 MSB를 지우기
        else {
            for (j = --cnt[(p[i] >> lev) & MK]; i != j; j = --cnt[(p[i] >> lev) & MK]) {
                k = p[j];
                p[j] = p[i] | MSB;
                p[i] = k;
            }
        }
    }
    if (lev <= 0) return;
    for (i = j = 0; i < n; i = j) {  // 상위 11bit가 같은 구간에 대하여 하위 11bit 정렬하기
        int tg = (p[i] >> lev);      // 구간 식별자 : 상위 11bit
        for (; j < n && tg == (p[j] >> lev); ++j); // i: 구간 시작위치, j:구간 끝
        rSort(0, p + i, j - i, cnt);  // rSort(right_bit_shift_size, 구간 시작 포인터, 구간 크기, 개수를 셀 배열)
    }
}

void test(unsigned int data[LM]) {
    int origin[2050] = { 0 }, cnt[2050] = { 0 };
    unsigned int entry[65536] = { 0 }; // 종자수를 index로 표시하여 renumbering
    rint i, j, k, n = 0;
    // extract entry value
    for (i = 0; i < LM; ++i)  // O(1048576): 등장한 16bit수 표시하기
        entry[(data[i] >> 16) & MASK] = entry[data[i] & MASK] = 1;

    // descending order renumbering
    for (i = 65535; i >= 0; --i) if (entry[i]) {
        origin[n] = i;   // 16비트에 대하여 내림차순 정렬
        entry[i] = n++;  // 내림차순 정렬을 위하여 역순으로 renumberng
    }

    // 32bit --> 22bit compressing
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 16) & MASK;  // 상위 16비트 뽑기
        k = data[i] & MASK;          // 하위 16비트 뽑기
        data[i] = (entry[j] << 11) | entry[k];  // 22비트로 바꾸기
    }

    rSort(11, data, LM, cnt);

    // original value로 복원하기.
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 11) & MK, k = data[i] & MK;
        data[i] = ((unsigned int)origin[j] << 16) | origin[k];
    }
}